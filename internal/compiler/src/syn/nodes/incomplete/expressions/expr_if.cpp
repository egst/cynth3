#include "syn/nodes/incomplete/expressions/expr_if.hpp"
#include "syn/nodes/expressions.hpp" // To complete circular dependencies.

#include <string>

#include "esl/category.hpp"
#include "esl/type_manip.hpp"
#include "esl/containers.hpp"
#include "esl/lift.hpp"
#include "esl/result.hpp"
#include "esl/string.hpp"
#include "esl/sugar.hpp"
#include "esl/zip.hpp"

#include "config.hpp"
#include "context/main.hpp"
#include "interface/common.hpp"
#include "interface/compound.hpp"
#include "interface/nodes.hpp"
#include "interface/types.hpp"
#include "interface/values.hpp"
#include "sem/translation.hpp"
#include "syn/categories/expression.hpp"
#include "syn/nodes/common/if_nodes.hpp"

#include "esl/debug.hpp"

// TODO:
// Surely there must be a way to generalize the algohithms used here.
// I guess I won't be able to get rid of all the branches,
// not without too much runtime polymorphism and repeated
// "packing" and "unpacking" of abstractions and indirections.
// But I'll try to generalize the main ideas in some generic helper functions
// and just delegate to those in the different braeches.

namespace cynth::syn {

    namespace target = esl::target;
    using namespace esl::sugar;
    using interface::DisplayResult;
    using interface::ExpressionProcessingResult;
    using interface::NameExtractionResult;
    using interface::StatementProcessingResult;
    using interface::TypeNameExtractionResult;
    using sem::CompleteValue;
    using sem::FunctionDefinition;
    using sem::NoReturn;
    using sem::ResolvedValue;
    using sem::ReturnedValues;
    using sem::TypedExpression;

    DisplayResult node::ExprIf::display () const {
        return
            "if "    + esl::parenthesized(interface::display || target::category{} <<= *condition) +
            " "      + (interface::display || target::category{} <<= *positiveBranch) +
            " else " + (interface::display || target::category{} <<= *negativeBranch);
    }

    namespace {

        esl::result<void> runtimeValues (
            context::Main                        &       ctx,
            auto                                 const & pos,
            auto                                 const & neg,
            std::string                          const & tupleElement,
            esl::tiny_vector<tpl::TypeSpecifier> &       tupleTypes,
            esl::tiny_vector<std::string>        &       posTupleVals,
            esl::tiny_vector<std::string>        &       negTupleVals,
            esl::tiny_vector<ResolvedValue>      &       resolved
        ) {
            // At least one of them run-time:
            return [&] (auto pos, auto neg) -> esl::result<void> {
                // Note: No conversion to a common type will be implemented in the first version.
                if (!(interface::sameTypes || target::category{} <<= args(pos.type, neg.type)))
                    return esl::result_error{"Incompatible types in if expression branches."};

                resolved.push_back(TypedExpression{
                    .type       = pos.type,
                    .expression = tupleElement
                });
                posTupleVals.push_back(pos.expression);
                negTupleVals.push_back(neg.expression);

                return [&] (auto x) -> esl::result<void> {
                    tupleTypes.push_back(x);
                    return {};
                } || target::result{} <<=
                interface::translateTypeSpecifier || target::category{} <<= pos.type;

            } || target::result{} <<= args(
                interface::translateResolvedValue(ctx)(pos),
                interface::translateResolvedValue(ctx)(neg)
            );
        }

        esl::result<void> comptimeValues (
            context::Main                        &       ctx,
            CompleteValue                        const & pos,
            CompleteValue                        const & neg,
            std::string                          const & tupleElement,
            esl::tiny_vector<tpl::TypeSpecifier> &       tupleTypes,
            esl::tiny_vector<std::string>        &       posTupleVals,
            esl::tiny_vector<std::string>        &       negTupleVals,
            esl::tiny_vector<ResolvedValue>      &       resolved
        ) {
            auto posType = interface::valueType || target::category{} <<= pos;
            auto negType = interface::valueType || target::category{} <<= pos;
            // Note: No conversion to a common type will be implemented in the first version.
            if (!(interface::sameTypes || target::category{} <<= args(posType, negType)))
                return esl::result_error{"Incompatible types in if expression branches."};

            return [&] (sem::type::Function const & type) -> esl::result<void> {
                // Two partially run-time function values:

                auto posResult = pos.template get<sem::value::Function>();
                auto negResult = neg.template get<sem::value::Function>();
                if (!posResult) return posResult.error();
                if (!negResult) return negResult.error();
                auto & posFun = *posResult;
                auto & negFun = *negResult;

                // TODO: There should be two functions in translation.hpp: closureType and closureTypeName.
                //auto closureType = c::structure(c::closureType(c::id(ctx.nextId())));
                auto closureType = c::closureType(c::id(ctx.nextId()));
                auto & def = ctx.global.storeValue<FunctionDefinition>(FunctionDefinition{
                    .implementation = FunctionDefinition::Switch{posFun, negFun},
                    .type           = type,
                    .closureType    = closureType
                    //.name           = c::functionName(c::id(ctx.nextId()))
                });
                auto newFun = sem::value::Function{def, tupleElement};

                auto posExpr = c::closureLiteral(closureType, 0, posFun.closureVariable);
                auto negExpr = c::closureLiteral(closureType, 1, negFun.closureVariable);
                posTupleVals.push_back(posExpr);
                negTupleVals.push_back(negExpr);
                tupleTypes.push_back(tpl::TypeSpecifier{.type = closureType, .structure = true});
                resolved.push_back(CompleteValue{newFun});

                return {};

            } | [&] (auto type) -> esl::result<void> {
                // Two comp-time values:
                return [&] (auto type) -> esl::result<void> {
                    tupleTypes.push_back(type);
                    return {};

                } || target::result{} <<=
                [&] (auto pos, auto neg) {
                    resolved.push_back(TypedExpression{
                        .type       = type,
                        .expression = tupleElement
                    });
                    posTupleVals.push_back(pos.expression);
                    negTupleVals.push_back(neg.expression);

                    return interface::translateTypeSpecifier(type);

                } || target::result{} <<= args(
                    interface::translateValue(ctx) || target::category{} <<= pos,
                    interface::translateValue(ctx) || target::category{} <<= neg
                );

            } || target::category{} <<= posType;

            return {};
        }

        ExpressionProcessingResult runtimeCondition (
            context::Main & ctx,
            TypedExpression cond,
            category::Expression const & positiveBranch,
            category::Expression const & negativeBranch
        ) {
            // Note: No implicit conversions of the if condition will be implemented in the first version.
            if (!cond.type.template holds_alternative<sem::type::Bool>())
                return esl::result_error{"If condition must be a boolean value."};

            auto tupleVar = c::tupleVariableName(c::id(ctx.nextId()));

            return [&] (auto posVals, auto negVals) -> ExpressionProcessingResult {

                esl::tiny_vector<tpl::TypeSpecifier> tupleTypes;
                esl::tiny_vector<std::string>        posTupleVals;
                esl::tiny_vector<std::string>        negTupleVals;
                esl::tiny_vector<ResolvedValue>      resolved;

                for (auto const & [i, pos, neg]: esl::enumerate(posVals, negVals)) {
                    auto tupleElement = c::tupleElement(tupleVar, i);

                    auto result = [&] (CompleteValue const & pos, CompleteValue const & neg) -> esl::result<void> {
                        return comptimeValues(ctx, pos, neg, tupleElement, tupleTypes, posTupleVals, negTupleVals, resolved);

                    } | [&] (auto const & pos, auto const & neg) -> esl::result<void> {
                        return runtimeValues(ctx, pos, neg, tupleElement, tupleTypes, posTupleVals, negTupleVals, resolved);

                    } || target::category{} <<= args(pos, neg);
                    if (!result) return result.error();
                }

                auto tupleType = ctx.global.instantiateType(tpl::Tuple{tupleTypes});
                auto posExpr   = c::structureLiteral(tupleType, posTupleVals);
                auto negExpr   = c::structureLiteral(tupleType, negTupleVals);
                auto expr      = c::ternary(cond.expression, posExpr, negExpr);
                auto tupleDef  = c::statement(c::definition(c::autoType(), tupleVar, expr));

                /***
                __auto_type <tupvar> = <cond> ? (struct cth_tup$...) {
                    <pos1>,
                    ...
                } : (struct cth_tup$...) {
                    <neg1>,
                    ...
                };
                ***/
                ctx.insertStatement(tupleDef);

                return resolved;

            } || target::result{} <<= args(
                interface::processExpression(ctx) || target::category{} <<= positiveBranch,
                interface::processExpression(ctx) || target::category{} <<= negativeBranch
            );
        }

    }

    ExpressionProcessingResult node::ExprIf::processExpression (context::Main & ctx) const {
        auto r =  [&] (CompleteValue cond) -> ExpressionProcessingResult {
            // Compile-time condition value:
            // Note: No implicit conversions of the if condition will be implemented in the first version.
            auto boolResult = cond.template get<sem::value::Bool>();
            if (!boolResult) return boolResult.error();

            return [&] (auto cond) -> ExpressionProcessingResult {
                auto const & branch = cond ? *positiveBranch : *negativeBranch;
                return interface::processExpression(ctx) || target::category{} <<= branch;

            } || target::result{} <<= interface::get<bool>(*boolResult);

        } | [&] (TypedExpression cond) -> ExpressionProcessingResult {
            // Run-time condition value:
            return runtimeCondition(ctx, std::move(cond), *positiveBranch, *negativeBranch);

        } || target::nested<target::result, target::category>{} <<=
            esl::single || target::result{} <<=
            interface::processExpression(ctx) || target::category{} <<= *condition;
        return r;
    }

    StatementProcessingResult node::ExprIf::processStatement (context::Main & ctx) const {
        return if_nodes::processStatement(ctx, *condition, *positiveBranch, negativeBranch.get());
    }

    NameExtractionResult node::ExprIf::extractNames (context::Lookup & outerScope) const {
        auto nestedScope = outerScope.makeChild();
        auto c = interface::extractNames(nestedScope) || target::category{} <<= *condition;
        auto p = interface::extractNames(nestedScope) || target::category{} <<= *positiveBranch;
        auto n = interface::extractNames(nestedScope) || target::category{} <<= *negativeBranch;
        return esl::insert_cat || target::result{} <<= args(c, p, n);
    }

    TypeNameExtractionResult node::ExprIf::extractTypeNames (context::Lookup & outerScope) const {
        auto nestedScope = outerScope.makeChild();
        auto c = interface::extractTypeNames(nestedScope) || target::category{} <<= *condition;
        auto p = interface::extractTypeNames(nestedScope) || target::category{} <<= *positiveBranch;
        auto n = interface::extractTypeNames(nestedScope) || target::category{} <<= *negativeBranch;
        return esl::insert_cat || target::result{} <<= args(c, p, n);
    }

}
