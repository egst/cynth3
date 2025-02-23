#include "syn/nodes/incomplete/statements/if.hpp"
#include "syn/nodes/statements.hpp" // To complete circular dependencies.

#include "esl/category.hpp"
#include "esl/string.hpp"
#include "esl/lift.hpp"
#include "esl/sugar.hpp"

#include "context/main.hpp"
#include "interface/common.hpp"
#include "interface/nodes.hpp"
#include "syn/nodes/common/if_nodes.hpp"

namespace cynth::syn {

    using namespace esl::sugar;
    namespace target = esl::target;
    using interface::DisplayResult;
    using interface::NameExtractionResult;
    using interface::StatementProcessingResult;
    using interface::TypeNameExtractionResult;

    DisplayResult node::If::display () const {
        return
            "if "   + esl::parenthesized(interface::display || target::category{} <<= *condition) +
            " "     + (interface::display || target::category{} <<= *positiveBranch) +
            "else " + (interface::display || target::category{} <<= *positiveBranch);
    }

    StatementProcessingResult node::If::processStatement (context::Main & ctx) const {
        return if_nodes::processStatement(ctx, *condition, *positiveBranch, negativeBranch.get());
    }

    NameExtractionResult node::If::extractNames (context::Lookup & outerScope) const {
        auto nestedScope = outerScope.makeChild();
        auto c = interface::extractNames(nestedScope) || target::category{} <<= *condition;
        auto p = interface::extractNames(nestedScope) || target::category{} <<= *positiveBranch;
        auto n = interface::extractNames(nestedScope) || target::category{} <<= *negativeBranch;
        return esl::insert_cat || target::result{} <<= args(c, p, n);
    }

    TypeNameExtractionResult node::If::extractTypeNames (context::Lookup & outerScope) const {
        auto nestedScope = outerScope.makeChild();
        auto c = interface::extractTypeNames(nestedScope) || target::category{} <<= *condition;
        auto p = interface::extractTypeNames(nestedScope) || target::category{} <<= *positiveBranch;
        auto n = interface::extractTypeNames(nestedScope) || target::category{} <<= *negativeBranch;
        return esl::insert_cat || target::result{} <<= args(c, p, n);
    }

}
