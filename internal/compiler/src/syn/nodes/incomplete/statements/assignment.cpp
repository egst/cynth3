#include "syn/nodes/incomplete/statements/assignment.hpp"
#include "syn/nodes/statements.hpp" // To complete circular dependencies.

#include "esl/category.hpp"
#include "esl/string.hpp"
#include "esl/lift.hpp"
#include "esl/sugar.hpp"

#include "context/main.hpp"
#include "interface/common.hpp"
#include "interface/nodes.hpp"
#include "interface/types.hpp"
#include "interface/compound.hpp"
#include "sem/compound.hpp"

namespace cynth::syn {

    using namespace esl::sugar;
    namespace target = esl::target;
    using interface::DisplayResult;
    using interface::NameExtractionResult;
    using interface::StatementProcessingResult;
    using interface::TypeNameExtractionResult;

    DisplayResult node::Assignment::display () const {
        return
            (interface::display || target::category{} <<= *target) + " = " +
            (interface::display || target::category{} <<= *value);
    }

    StatementProcessingResult node::Assignment::processStatement (context::Main & ctx) const {
        return [&] (auto targets, auto values) -> StatementProcessingResult {
            if (targets.empty())
                return esl::result_error{"No targets in an assignment."};
            if (values.empty())
                return esl::result_error{"No values in an assignment."};
            if (values.size() > targets.size())
                return esl::result_error{"More values than targets in an assignment."};
            if (targets.size() > values.size())
                return esl::result_error{"More targets than values in an assignment."};

            for (auto const & [target, value]: esl::zip(targets, values)) {
                auto result = [&, &target = target] (auto value) -> esl::result<void> {
                    if (!(interface::sameTypes || target::category{} <<= args(value.type, target.type)))
                        return esl::result_error{"Assigning incompatible values."};

                    return [&] (sem::type::Array const & type) -> esl::result<void> {
                        if (target.values) {
                            // Assigning to array values:
                            if (type.constval())
                                return esl::result_error{"Assigning to constant array values."};

                            return [&] (auto const & translType) -> esl::result<void> {
                                auto copy = c::statement(
                                    c::arrayBulkCopy(target.expression, value.expression, type.size, translType)
                                );
                                /***
                                memcpy(<target>, <value>, <size> * sizeof(<type>))
                                ***/
                                ctx.insertStatement(copy);
                                return {};

                            } || target::result{} <<= interface::translateType || target::category{} <<= *type.type;
                        }

                        // Reassigning the array reference:
                        // Note: This is essentially the same as the case below (for simple values).
                        if (type.constant)
                            return esl::result_error{"Assigning to a constant variable."};
                        auto assgn = c::statement(c::assignment(value.expression, target.expression));
                        /***
                        <target> = <value>
                        ***/
                        ctx.insertStatement(assgn);
                        return {};

                    } | [&] <interface::simpleType T> (T const & type) -> esl::result<void> {
                        // TODO: Or I could take cake of this check in node::Name::resolveTarget.
                        if (type.constant)
                            return esl::result_error{"Assigning to a constant variable."};
                        auto assgn = c::statement(c::assignment(value.expression, target.expression));
                        /***
                        <target> = <value>
                        ***/
                        ctx.insertStatement(assgn);
                        return {};

                    } | [&] (auto const &) -> esl::result<void> {
                        return esl::result_error{"Cannot assign to this type."};

                    } || target::category{} <<= target.type;

                } || target::result{} <<= interface::translateResolvedValue(ctx)(value);
                if (!result) return result.error();

            }

            return {sem::NoReturn{}};

        } || target::result{} <<= args(
            interface::resolveTarget(ctx)     || target::category{} <<= *target,
            interface::processExpression(ctx) || target::category{} <<= *value
        );
    }

    NameExtractionResult node::Assignment::extractNames (context::Lookup & ctx) const {
        auto v = interface::extractNames(ctx) || target::category{} <<= *value;
        auto t = interface::extractNames(ctx) || target::category{} <<= *target;
        return esl::insert_cat || target::result{} <<= args(
            interface::extractNames(ctx) || target::category{} <<= *value,
            interface::extractNames(ctx) || target::category{} <<= *target
        );
    }

    TypeNameExtractionResult node::Assignment::extractTypeNames (context::Lookup & ctx) const {
        auto v = interface::extractTypeNames(ctx) || target::category{} <<= *value;
        auto t = interface::extractTypeNames(ctx) || target::category{} <<= *target;
        return esl::insert_cat || target::result{} <<= args(v, t);
    }

}
