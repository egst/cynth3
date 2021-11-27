#include "ast/nodes/array_elems.hpp"

#include "ast/categories/expression.hpp"
#include "ast/interface.hpp"

#include <string>

namespace cynth {

    template <>
    void component_deleter<ast::node::RangeTo>::operator () (ast::node::RangeTo * ptr) const {
        delete ptr;
    }

    template <>
    ast::node::RangeTo * component_allocator<ast::node::RangeTo>::operator () (ast::node::RangeTo const & other) const {
        return new ast::node::RangeTo{other};
    }

    template <>
    ast::node::RangeTo * component_allocator<ast::node::RangeTo>::operator () (ast::node::RangeTo && other) const {
        return new ast::node::RangeTo{std::move(other)};
    }

    display_result ast::node::RangeTo::display () const {
        return cynth::display(from) + " to " + cynth::display(to);
    }

    ast::array_elem_eval_result ast::node::RangeTo::eval_array_elem (sem::context &) const {
        return ast::make_array_elem_eval_result(result_error{"Range array elements are not supported yet."});
    }

    template <>
    void component_deleter<ast::node::RangeToBy>::operator () (ast::node::RangeToBy * ptr) const {
        delete ptr;
    }

    template <>
    ast::node::RangeToBy * component_allocator<ast::node::RangeToBy>::operator () (
        ast::node::RangeToBy const & other
    ) const {
        return new ast::node::RangeToBy{other};
    }

    template <>
    ast::node::RangeToBy * component_allocator<ast::node::RangeToBy>::operator () (
        ast::node::RangeToBy && other
    ) const {
        return new ast::node::RangeToBy{std::move(other)};
    }

    display_result ast::node::RangeToBy::display () const {
        return cynth::display(from) + " to " + cynth::display(to) + " by " + cynth::display(by);
    }

    ast::array_elem_eval_result ast::node::RangeToBy::eval_array_elem (sem::context &) const {
        return ast::make_array_elem_eval_result(result_error{"Range array elements are not supported yet."});
    }

    template <>
    void component_deleter<ast::node::Spread>::operator () (ast::node::Spread * ptr) const {
        delete ptr;
    }

    template <>
    ast::node::Spread * component_allocator<ast::node::Spread>::operator () (ast::node::Spread const & other) const {
        return new ast::node::Spread{other};
    }

    template <>
    ast::node::Spread * component_allocator<ast::node::Spread>::operator () (ast::node::Spread && other) const {
        return new ast::node::Spread{std::move(other)};
    }

    display_result ast::node::Spread::display () const {
        return "..." + cynth::display(container);
    }

    ast::array_elem_eval_result ast::node::Spread::eval_array_elem (sem::context &) const {
        return ast::make_array_elem_eval_result(result_error{"Range array elements are not supported yet."});
    }

}
