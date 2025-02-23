#include "context/main.hpp"

#include "esl/containers.hpp"
#include "esl/lift.hpp"
#include "esl/string.hpp"
#include "esl/sugar.hpp"
#include "esl/tiny_vector.hpp"
#include "esl/zip.hpp"

#include "config.hpp"
#include "context/function.hpp"
#include "interface/compound.hpp"
#include "interface/nodes.hpp"
#include "interface/types.hpp"
#include "sem/translation.hpp"
#include "syn/nodes/common/decl_nodes.hpp"

#include "esl/debug.hpp"

namespace cynth::context {

    using namespace esl::sugar;
    namespace target = esl::target;
    using sem::FunctionDefinition;
    using sem::ResolvedCapture;
    using sem::Variable;

    void Main::insertStatement (std::string const & code) {
        if (code.empty()) return;
        statements.push_back(code);
    }

    void Main::mergeChild (Main const & child) {
        for (auto const & code: child.statements) {
            statements.push_back(c::indented(code));
        }
    }

    namespace {

        esl::result<Variable> captureVariable (ResolvedCapture const & capture) {
            return [] (auto const & value) {
                return Variable{value};

            } || target::category{} <<= capture;
        }

#if 0
        esl::result<esl::tiny_vector<std::optional<tpl::TypeSpecifier>>> translateTypeSpecifiers (
            esl::component_vector<CompleteType> types
        ) {
            esl::tiny_vector<std::optional<tpl::TypeSpecifier>> specs;
            for (auto const & type: types) {
                auto result = [&] (sem::type::Function const &) -> esl::result<void> {
                    specs.push_back(std::nullopt);
                    return {};

                } | [&] (auto const & type) -> esl::result<void> {
                    auto result = interface::translateTypeSpecifier(type);
                    if (!result) return result.error();
                    specs.emplace_back(*std::move(result));
                    return {};

                } || target::category{} <<= type;
                if (!result) return result.error();
            }
            return specs;
        }

        esl::result<esl::tiny_vector<TypedExpression>> translateBody (
            context::Main & ctx,
            esl::tiny_vector<ResolvedValue> const & body
        ) {
            return esl::unite_results <<= [&] (CompleteValue const & body) {
                return [] (sem::value::Function const & body) -> esl::result<TypedExpression> {

                } | [&] (auto const & body) -> esl::result<TypedExpression> {
                    return interface::translateValue(ctx)(body);

                } || target::category{} <<= body;

            } | [] (TypedExpression const & body) -> esl::result<TypedExpression> {
                return body;

            } || target::nested<target::tiny_vector, target::category>{} <<= body;
        }
#endif

        esl::result<void> directImplementation (
            Main & ctx,
            FunctionDefinition & def,
            FunctionDefinition::Implementation const & impl
        ) {
            Function funCtx;
            auto funScope = ctx.makeFunctionChild(funCtx);

            // TODO: Generalize this. (It is also used in expressions/application.cpp)
            for (auto const & [name, capture]: impl.closure->values) {
                auto varsResult = esl::unite_results <<= captureVariable || target::tiny_vector{} <<= capture;
                if (!varsResult) return varsResult.error();
                auto result = funScope.lookup.insertValue(name, *std::move(varsResult));
                if (!result) return result.error();
            }
            for (auto const & [name, type]: impl.closure->types) {
                auto typeResult = funScope.lookup.insertType(name, {type});
                if (!typeResult) return typeResult.error();
            }

            auto paramDecls = interface::parameterDeclarations(impl.parameters, def.type.in);
            if (!paramDecls) return paramDecls.error();
            auto paramDeclResult = syn::decl_nodes::declare(funScope, *paramDecls, true);
            if (!paramDeclResult) return paramDeclResult.error();
            /*
            auto paramDecls = [&] (auto decls) {
                return syn::decl_nodes::declare(funScope, decls, true);
            } || target::result{} <<= interface::parameterDeclarations(impl.parameters, def.type.in);
            if (!paramDecls) return paramDecls.error();
            */

            auto & params = funScope.function.getParameters();

            auto processingResult = interface::processExpression(funScope) || target::category{} <<= *impl.body;
            if (!processingResult) return processingResult.error();
            auto translationResult = esl::unite_results <<= interface::translateResolvedValue(funScope) || target::tiny_vector{} <<= *std::move(processingResult);
            if (!translationResult) return translationResult.error();
            auto bodyResults = *std::move(translationResult);

            auto const & outTypes = def.type.out;
            if (bodyResults.size() > outTypes.size())
                return esl::result_error{"Returning more values than specified in function signature."};
            if (bodyResults.size() < outTypes.size())
                return esl::result_error{"Returning less values than specified in function signature."};

            esl::tiny_vector<std::string> stmts;
            for (auto const & [i, type, result]: esl::enumerate(outTypes, std::move(bodyResults))) {
                if (!(interface::sameTypes || target::category{} <<= args(result.type, type)))
                    return esl::result_error{"Returning a value of an incompatible type."};

                auto defResult = [&, i = i] (sem::type::Function const & fun) -> esl::result<void> {
                    if (!fun.definition) // Implementation error.
                        return esl::result_error{"No definition in function type after translation."};
                    // Add more info about the returned function to the function definition:
                    def.type.out[i] = fun;
                    // TODO: This is not needed anymore...
                    // Remove it from the FunctionDefinition type.
                    //def.returnedFunctions.push_back(fun.definition);
                    return {};
                } | [] (auto const &) -> esl::result<void> {
                    return {}; // Skip.
                } || target::category{} <<= result.type;
                if (!defResult) return defResult.error();

                stmts.push_back(c::returnValue(i, result.expression));
            }

            auto typeSpecResult = esl::unite_results <<= interface::translateTypeSpecifier ||
                target::nested<target::component_vector_tiny_result, target::category>{} <<= def.type.out;
            if (!typeSpecResult) return typeSpecResult.error();
            auto outType = ctx.global.instantiateType(tpl::Tuple{*typeSpecResult});

            auto resultInit   = c::functionResultInit(outType);
            auto resultReturn = c::functionResultReturn();
            auto end          = c::end();
            auto newLine      = c::newLine();
            auto indent       = c::indentation();

            /*
            auto closure  = def.closureType
                ? c::declaration(c::pointer(c::constness(*def.closureType)), c::closureArgumentName())
                : c::declaration(c::pointer(c::constness(c::emptyType())), "_");
            */
            auto closure  = def.closureType
                ? c::declaration(*def.closureType, c::closureArgumentName())
                : c::declaration(c::emptyType(), "_");
            if (!def.closureType)
                def.closureType = c::emptyType();
            auto funHead  = c::functionBegin(outType, *def.name, closure, params);
            auto returned = c::join("", stmts);
            auto body     = c::join("", funScope.getStatements());
            auto allocs   = c::join("", funScope.function.getData());
            auto funBody  = c::join("",
                allocs,
                resultInit,
                body,
                returned,
                resultReturn
            );
            auto funDef = c::join("",
                funHead,
                c::indented(funBody),
                end
            );

            /***
            struct cth_tup$<outType1>$<outType2>$... <sfun> (struct cth_empty _, <inDecl0>, <inDecl2>...) {
                struct cth_tup$<outType1>$<outType2>$... result;
                <body>; // Potential helper statements for the <result> values.
                result.e0 = <result0>;
                result.e1 = <result1>;
                ...
                return result;
            }
            ***/
            ctx.global.insertFunction(funDef);

            return {};

        }

        esl::result<void> switchImplementation (
            Main & ctx,
            FunctionDefinition & def,
            FunctionDefinition::Switch & funs,
            esl::tiny_vector<std::string> const & inTypes
        ) {
            // Switch implementation:
            esl::tiny_vector<std::string> names;
            esl::tiny_vector<std::string> closureTypes;
            for (auto & fun: funs) {
                auto id = ctx.defineFunction(fun.definition);
                if (!id) return id.error();
                names.push_back(id->name);
                closureTypes.push_back(id->closureType);
            }

            auto typeSpecResult = esl::unite_results <<= interface::translateTypeSpecifier ||
                target::nested<target::component_vector_tiny_result, target::category>{} <<= def.type.out;
            if (!typeSpecResult) return typeSpecResult.error();
            auto outType = ctx.global.instantiateType(tpl::Tuple{*typeSpecResult});

            if (!def.closureType) // Implementation error.
                return esl::result_error{"No closure type prepared for a switch function."};

            // Note: def.closureType already contains the "struct " part, so doing a little hack here...
            // TODO: Solve this properly.
            /*
            auto closureStructDef = c::statement(c::detail::translation::compoundDefinition("",
                def.closureType,
                c::declaration(c::integralType(), def::branchMember),
                c::declaration(c::anonymousVariantUnionDefinition(closureTypes), def::closureDataMember)
            ));
            */
            // Update: This is slightly better, but still not ideal:
            auto closureTypeName = *def.closureType;
            def.closureType = c::structure(closureTypeName);
            auto closureStructDef = c::statement(c::structureDefinition(
                closureTypeName,
                c::declaration(c::integralType(), def::branchMember),
                c::declaration(c::anonymousVariantUnionDefinition(closureTypes), def::closureDataMember)
            ));

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
            ctx.global.insertType(closureStructDef);

            auto newLine     = c::newLine();
            auto fwdParams   = c::functionParameters(inTypes);
            auto args        = c::functionArguments(inTypes);
            auto closureArg  = c::closureArgumentName();
            auto closureDecl = c::declaration(*def.closureType, closureArg);
            auto funHead     = fwdParams.empty()
                ? c::functionBegin(outType, *def.name, closureDecl)
                : c::functionBegin(outType, *def.name, closureDecl, fwdParams); // TODO...
            auto switchHead  = c::switchBegin(c::closureBranch(closureArg));
            auto end         = c::end();
            esl::tiny_vector<std::string> cases;
            //for (std::size_t i = 0; i < names.size(); ++i) { // TODO: use esl::enumerate instead
            for (auto const & [i, name]: esl::enumerate(names)) {
                auto result = args.empty()
                    ? c::statement(c::functionReturn(c::call(name, c::closureData(closureArg, i))))
                    : c::statement(c::functionReturn(c::call(name, c::closureData(closureArg, i), args))); // TODO...
                cases.push_back(c::switchCase(i, i == 0, false, result));
            }
            auto switchBody = c::join("", cases);
            auto funBody    = c::indented(c::join("", switchHead, switchBody, end));
            auto funDef     = c::join("", funHead, newLine, funBody, end);

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
            ctx.global.insertFunction(funDef);

            return {};
        }

    }

    esl::result<Global::FunctionId> Main::defineFunction (FunctionDefinition & def) {
        if (def.name && def.closureType) { // Already defined.
            return Global::FunctionId{*def.name, *def.closureType};
        }

        //if (!def.name)
        def.name = c::functionName(c::id(nextId()));

        // Note: The closure structure should already be defined (upon function definition).
        // If closureType is not set, there is no need for runtime closure,
        // and the `struct cth_empty {}` type is used instead.

        /*
        outSpecs...
        esl::unite_results <<= interface::translateTypeSpecifier || target::nested<target::component_vector_tiny_result, target::category>{} <<= def.type.out
        translateTypeSpecifiers(def.type.out)
        auto outType = global.instantiateType(tpl::Tuple{outSpecs});
        */
        auto translationResult = esl::unite_results <<= interface::translateType ||
                target::nested<target::component_vector_tiny_result, target::category>{} <<= def.type.in;
        if (!translationResult) return translationResult.error();
        auto inTypes = *std::move(translationResult);

        auto result = [&] (FunctionDefinition::Implementation const & impl) -> esl::result<void> {
            return directImplementation(*this, def, impl);

        } | [&] (FunctionDefinition::Switch & funs) -> esl::result<void> {
            return switchImplementation(*this, def, funs, inTypes);

        } || target::variant{} <<= def.implementation;

        if (!result) return result.error();

        return Global::FunctionId{*def.name, def.closureType.value_or(c::emptyType())};
    }

    std::string Main::assemble () const {
        auto indent      = c::indentation();
        auto newLine     = c::newLine();
        auto local       = c::join("", statements);
        auto funAlloc    = c::join("", function.data);
        auto staticAlloc = c::join("", global.data);
        auto includes    = c::join("", global.includes);
        auto types       = c::join("", global.types);
        auto depTypes    = c::join("", global.dependantTypes);
        auto funs        = c::join("", global.functions);
        auto inVals      = global.inputValues;
        auto outBuffs    = global.outputBuffers;
        auto end         = c::end();

        // TODO: esl::join returns a new line for empty input
        auto global = c::join("",
            includes,
            c::inlineComment("Types:"),
            types,
            depTypes,
            c::inlineComment("Static data:"),
            staticAlloc,
            c::inlineComment("Functions:"),
            funs
        );

        auto time    = c::declaration(integral, "time");
        auto runHead = c::inlineFunctionBegin(integral, c::global("run"), time);

        /***
        float * cth_output_buffer (char const * name) {
            if (strcmp(name, "<name1>") == 0) return &<var1>; else
            if (strcmp(name, "<name2>") == 0) return &<var2>; else
            ...
            if (strcmp(name, "<nameN>") == 0) return &<varN>; else
            return NULL;
        }
        bool * cth_input_bool (char const * name) {
            ...
        }
        int * cth_input_int (char const * name) {
            ...
        }
        float * cth_input_float (char const * name) {
            ...
        }
        ***/


        std::vector<std::string> getters;

        std::vector<std::string> possibleIoTypes = {"bool", integral, floating};
        for (auto const & type: possibleIoTypes) {
            std::vector<std::string> cases;
            for (auto const & [name, entry]: inVals) if (entry.first == type)
                cases.push_back(indent + "if (strcmp(name, \"" + name + "\") == 0) return &" + entry.second + "; else ");
            cases.push_back(indent + "return NULL;");
            getters.push_back(
                type + " * cth_input_" + type + " (char const * name) {" + newLine +
                c::join("", cases) + newLine +
                "}"
            );
        }
        std::vector<std::string> buffCases;
        for (auto const & [name, var]: outBuffs)
            buffCases.push_back(indent + "if (strcmp(name, \"" + name + "\") == 0) return " + var + ".data; else ");
        buffCases.push_back(indent + "return NULL;");
        getters.push_back(
            std::string{} + floating + " * cth_output_buffer (char const * name) {" + newLine +
            c::join("", buffCases) + newLine +
            "}"
        );

        return c::join("",
            global,
            c::join("", getters),
            runHead,
            c::indented(c::join("",
                funAlloc,
                local
            )),
            end
        );
    }

}
