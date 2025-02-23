#pragma once

#include "esl/category.hpp"
#include "esl/functional.hpp"
#include "esl/lift.hpp"
#include "esl/result.hpp"

#include "sem/compound.hpp"

#include "context/main.hpp"
#include "interface/forward.hpp"
#include "interface/values.hpp"

// For resolveParam: (It might be moved elsewhere.)
#include "config.hpp"
#include "sem/declarations.hpp"
#include "sem/types.hpp"
#include "sem/values.hpp"

namespace cynth::interface {

    // Concepts:

    namespace has {

        /*
        template <typename T>
        concept processAssignment = type<T> && requires (
            T type, context::Main & ctx,
            sem::ResolvedValue  value,
            sem::ResolvedTarget target
        ) {
            { type.processAssignment(ctx, value, target) } -> std::same_as<AssignmentProcessingResult>;
        };
        */

    }

    // Functions:

    // TODO: Should this be moved elsewhere? interface/declarations or something?

    inline sem::FunctionDefinition::Parameter resolveParameter (sem::CompleteDeclaration const & decl) {
        return {.name = decl.name, .arity = static_cast<Integral>(decl.type.size())};
    }

    template <esl::sized_range P, esl::sized_range T> requires (
        esl::same_but_cvref<esl::range_value_type<P>, sem::FunctionDefinition::Parameter> &&
        esl::same_but_cvref<esl::range_value_type<T>, sem::CompleteType>
    ) esl::result<esl::tiny_vector<sem::CompleteDeclaration>> parameterDeclarations (
        P const & parameters,
        T const & types
    ) {
        esl::tiny_vector<sem::CompleteDeclaration> result;
        auto typeIter = types.begin();
        for (auto const & param: parameters) {
            std::size_t count = param.arity;
            if (typeIter + count > types.end()) // Implementation error.
                return esl::result_error{"More parameters than types."};
            result.push_back(sem::CompleteDeclaration{
                esl::make_component_vector(esl::view{typeIter, count}),
                param.name
            });
            typeIter += count;
        }
        return result;
    }

    inline esl::tiny_vector<sem::CompleteType> declType (sem::CompleteDeclaration const & decl) {
        return decl.type;
    }

    inline std::string expression (sem::TypedExpression const & typed) {
        return typed.expression;
    }

    constexpr auto translateDirectResolvedValue (context::Main & ctx) {
        return esl::overload(
            [&ctx] (sem::CompleteValue const & value) -> ValueTranslationResult {
                return esl::lift<esl::target::category>(interface::translateValue(ctx))(value);
            },
            [] (sem::TypedExpression const & expr) -> ValueTranslationResult {
                return expr;
            }
        );
    }

    constexpr auto translateResolvedValue (context::Main & ctx) {
        return [&ctx] (sem::ResolvedValue const & value) {
            return esl::lift<esl::target::category>(translateDirectResolvedValue(ctx))(value);
        };
    }

    inline auto resolvedValueType (sem::ResolvedValue const & value) {
        return esl::lift<esl::target::category>(
            [] (sem::CompleteValue const & value) -> ValueTypeResult {
                return esl::lift<esl::target::category>(interface::valueType)(value);
            },
            [] (sem::TypedExpression const & expr) -> ValueTypeResult {
                return expr.type;
            }
        )(value);
    }

    inline auto targetType (sem::ResolvedTarget const & target) {
        return esl::lift<esl::target::category>(
            [] (sem::CompleteValue * target) -> ValueTypeResult {
                return esl::lift<esl::target::category>(interface::valueType)(*target);
            },
            [] (sem::TypedTargetExpression const & target) -> ValueTypeResult {
                return target.type;
            }
        )(target);
    }

    inline sem::CompleteType returnedValuesType (sem::ReturnedValues const & value) {
        // Note: This assumes non-empty value.
        return esl::lift<esl::target::category>(interface::valueType)(value.back());
    }

    inline auto returnedType (sem::Returned const & value) {
        return esl::lift<esl::target::category>(
            returnedValuesType,
            [] (sem::CompleteType const & type) -> sem::CompleteType {
                return type;
            }
        )(value);
    }

    /*
    constexpr auto processAssignment (context::Main & ctx) {
        return [&ctx] (sem::ResolvedValue const & value, sem::ResolvedTarget const & target) {
            auto type = targetType(target);

            return esl::lift<esl::target::category>(
                [&ctx, &value, &target] <has::processAssignment T> (T const & type) -> AssignmentProcessingResult {
                    return type.processAssignment(ctx, value, target);
                },
                [] (auto const &) -> AssignmentProcessingResult {
                    return esl::result_error{"An assignment of this type cannot be translated."};
                }
            )(type);
        };
    }
    */

}
