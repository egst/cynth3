#include "context/main.hpp"

#include "esl/containers.hpp"
#include "esl/lift.hpp"
#include "esl/string.hpp"
#include "esl/sugar.hpp"
#include "esl/tiny_vector.hpp"
#include "esl/zip.hpp"

#include "context/function.hpp"
#include "interface/compound.hpp"
#include "interface/nodes.hpp"
#include "interface/types.hpp"
#include "sem/translation.hpp"
#include "syn/nodes/common/decl_nodes.hpp"

// TMP
#include "debug.hpp"

namespace cynth::context {

    using namespace esl::sugar;
    namespace target = esl::target;
    using sem::CompleteValue;
    using sem::FunctionDefinition;
    using sem::ResolvedCapture;
    using sem::TypedName;
    using sem::Variable;

    void Main::insertStatement (std::string const & code) {
        if (code.empty()) return;
        statements.push_back(code);
    }

    void Main::mergeChild (Main const & child) {
        for (auto const & code: child.statements)
            statements.push_back(esl::indent(c::indentation(child.indent), c::newLine(), code));
    }

    namespace {

        esl::result<Variable> captureVariable (ResolvedCapture const & capture) {
            return [] (auto const & value) {
                return Variable{value};

            } || target::category{} <<= capture;
        }

    }

    esl::result<Global::FunctionId> Main::defineFunction (FunctionDefinition & def) {
        if (def.name && def.closureType) // Already defined.
            return Global::FunctionId{*def.name, *def.closureType};

        if (!def.name)
            def.name = c::functionName(c::id(nextId()));
        if (!def.closureType)
            def.name = c::closureType(c::id(nextId()));

        auto result = [&] (auto outSpecs, auto inTypes) {
            auto newLine = c::newLine();
            auto outType = global.instantiateType(tpl::Tuple{outSpecs});

            return [&] (FunctionDefinition::Implementation const & impl) -> esl::result<void> {
                // Direct implementation:

                // Note: The closure structure should already be defined (upon function definition).

                Function funCtx;
                auto funScope = makeFunctionChild(funCtx);

                // TODO: Generalize this. (It is also used in expressions/application.cpp)
                for (auto const & [name, capture]: impl.closure->values) {
                    auto varsResult = esl::unite_results <<= captureVariable || target::tiny_vector{} <<= capture;
                    if (!varsResult) return varsResult.error();
                    auto result = funScope.lookup.insertValue(name, *std::move(varsResult));
                    if (!result) return result.error();
                }
                for (auto const & [name, type]: impl.closure->types) {
                    funScope.lookup.insertType(name, {type});
                }

                auto paramDecls = [&] (auto decls) {
                    return syn::decl_nodes::declare(funScope, decls, true);
                } || target::result{} <<= interface::parameterDeclarations(impl.parameters, def.type.out);
                if (!paramDecls) return paramDecls.error();

                auto params       = function.parameters;
                auto funHead      = c::functionBegin(outType, *def.name, params);
                auto resultInit   = c::functionResultInit(outType);
                auto resultReturn = c::functionResultReturn();
                auto end          = c::end();
                auto newLine      = c::newLine();
                auto indent       = c::indentation();

                auto result = [&] (auto bodyResults) -> esl::result<void> {
                    auto const & outTypes = def.type.out;
                    if (bodyResults.size() > outTypes.size())
                        return esl::result_error{"Returning more values than specified in function signature."};
                    if (bodyResults.size() < outTypes.size())
                        return esl::result_error{"Returning less values than specified in function signature."};

                    esl::tiny_vector<std::string> stmts;
                    for (auto const & [i, type, result]: esl::enumerate(outTypes, bodyResults)) {
                        if (!(interface::sameTypes || target::category{} <<= args(result.type, type)))
                            return esl::result_error{"Returning a value of an incompatible type."};
                        stmts.push_back(c::returnValue(i, result.expression));
                    }
                    auto returned = c::join("", stmts);
                    auto body     = c::join("", funScope.statements);
                    auto funBody  =
                        resultInit + newLine +
                        body       + newLine +
                        returned   + newLine +
                        resultReturn;
                    auto funDef = funHead + newLine + esl::indent(funBody, indent, body) + end;

                    /***
                    struct cth_tup$<outType1>$<outType2>$... <sfun> (<inDecl0>, <inDecl2>...) {
                        struct cth_tup$<outType1>$<outType2>$... result;
                        <body>; // Potential helper statements for the <result> values.
                        result.e0 = <result0>;
                        result.e1 = <result1>;
                        ...
                        return result;
                    }
                    ***/
                    global.insertFunction(funDef);

                    return {};

                } || target::result{} <<= esl::unite_results || target::result{} <<=
                    interface::translateResolvedValue(funScope) ||
                    target::nested<target::result, target::tiny_vector>{} <<=
                    interface::processExpression(funScope) || target::category{} <<= *impl.body;

                if (!result) return result.error();
                return {};

            } | [&] (FunctionDefinition::Switch const & funs) -> esl::result<void> {
                // Switch implementation:
                esl::tiny_vector<std::string> names;
                esl::tiny_vector<std::string> closureTypes;
                for (auto & fun: funs) {
                    auto id = defineFunction(fun.definition);
                    if (!id) return id.error();
                    names.push_back(id->name);
                    names.push_back(id->closureType);
                }

                auto closureStructDef = c::structureDefinition(
                    c::declaration(c::integralType(), def::branchMember),
                    c::declaration(c::anonymousVariantUnionDefinition(closureTypes), def::closureDataMember)
                );

                /***
                struct <closureType> {
                    int branch;
                    union {
                        <closureType1> v0;
                        <closureType2> v1;
                        ...
                    } data;
                };
                ***/
                global.insertType(closureStructDef);

                auto params      = c::functionParameters(inTypes);
                auto args        = c::functionArguments(inTypes);
                auto closureArg  = c::closureArgumentName();
                auto closureDecl = c::declaration(*def.closureType, closureArg);
                auto funHead     = c::functionBegin(outType, *def.name, closureDecl, params);
                auto switchHead  = c::switchBegin(c::closureBranch(closureArg));
                auto end         = c::end();
                esl::tiny_vector<std::string> cases;
                for (std::size_t i = 0; i < args.size(); ++i) {
                    auto result = c::functionReturn(c::call("<name>", c::closureData(closureArg, i), args));
                    cases.push_back(c::switchCase(i, i == 0, false, result));
                }
                auto switchBody = c::join(newLine, cases);
                auto funBody    = switchHead + newLine + switchBody + newLine + end;
                auto funDef     = funHead + newLine + funBody + end;

                /***
                struct cth_tup$<outType1>$<outType2>$... <sfun> (
                    <closureType> closure,
                    <inType0> arg0, <inType1> arg1...
                ) {
                    switch (closure.branch) {
                    case 0: default:
                        return <name0>(closure.data.v0, arg0, arg1, ...);
                    case 1:
                        return <name1>(closure.data.v1, arg0, arg1, ...);
                    ...
                    }
                }
                ***/
                global.insertFunction(funDef);

                return {};

            } || target::variant{} <<= def.implementation;


        } || target::result{} <<= args(
            esl::unite_results <<= interface::translateTypeSpecifier ||
                target::nested<target::component_vector_tiny_result, target::category>{} <<= def.type.out,
            esl::unite_results <<= interface::translateType ||
                target::nested<target::component_vector_tiny_result, target::category>{} <<= def.type.in
        );
        if (result) return result.error();

        return Global::FunctionId{*def.name, *def.closureType};
    }

    std::string Main::assemble () const {
        auto local = c::join("", statements);

        // TODO...

        return local;
    }

}
