#include "sem/values.hpp"

#include "esl/category.hpp"
#include "esl/component.hpp"
#include "esl/lift.hpp"
#include "esl/result.hpp"
#include "esl/sugar.hpp"
#include "esl/tiny_vector.hpp"
#include "esl/view.hpp"

#include "config.hpp"
#include "interface/common.hpp"
#include "interface/compound.hpp"
#include "interface/values.hpp"
#include "sem/translation.hpp"
#include "syn/nodes/common/array_nodes.hpp"

#include "esl/debug.hpp"

namespace esl {

    using cynth::sem::CompleteValue;
    using cynth::sem::IncompleteValue;

    // Note: Some of these specializations are needed for the implementations below to work properly.
    // TODO: Maybe I should move it elsewhere. These specializations are only needed
    // for code that doesn't know about complete definitions of these types.
    // However, code in any of the implementation files can include the full definitions,
    // and so the default specializations can be used instead.

    template <>
    void component_deleter<CompleteValue>::operator () (CompleteValue * ptr) const {
        delete ptr;
    }

    template <>
    CompleteValue * component_allocator<CompleteValue>::operator () (CompleteValue const & other) const {
        return new CompleteValue{other};
    }

    template <>
    CompleteValue * component_allocator<CompleteValue>::operator () (CompleteValue && other) const {
        return new CompleteValue{std::move(other)};
    }

    template <>
    void component_deleter<IncompleteValue>::operator () (IncompleteValue * ptr) const {
        delete ptr;
    }

    template <>
    IncompleteValue * component_allocator<IncompleteValue>::operator () (IncompleteValue const & other) const {
        return new IncompleteValue{other};
    }

    template <>
    IncompleteValue * component_allocator<IncompleteValue>::operator () (IncompleteValue && other) const {
        return new IncompleteValue{std::move(other)};
    }

}

namespace cynth::sem {

    using namespace esl::sugar;
    namespace target = esl::target;
    using interface::DisplayResult;
    using interface::GetResult;
    using interface::ValueTranslationResult;

    //// Bool ////

    DisplayResult value::Bool::display () const {
        return "bool(" + std::string{value ? "true" : "false"} + ")";
    }

    GetResult<bool> value::Bool::get () const {
        return value;
    }

    ValueTranslationResult value::Bool::translateValue (context::Main &) const {
        return TypedExpression{valueType, c::booleanLiteral(value)};
    }

    //// Int ////

    DisplayResult value::Int::display () const {
        return "int(" + std::to_string(value) + ")";
    }

    GetResult<Integral> value::Int::get () const {
        return value;
    }

    ValueTranslationResult value::Int::translateValue (context::Main &) const {
        return TypedExpression{valueType, c::integralLiteral(value)};
    }

    //// Float ////

    DisplayResult value::Float::display () const {
        return "float(" + std::to_string(value) + ")";
    }

    GetResult<Floating> value::Float::get () const {
        return value;
    }

    ValueTranslationResult value::Float::translateValue (context::Main &) const {
        return TypedExpression{valueType, c::floatingLiteral(value)};
    }

    //// String ////

    DisplayResult value::String::display () const {
        return "string(" + value + ")";
    }

    ValueTranslationResult value::String::translateValue (context::Main &) const {
        return esl::result_error{"Strings are not implemented yet."};
    }

    //// In ////

    DisplayResult value::In::display () const {
        return "in(" + allocation + ")";
    }

    ValueTranslationResult value::In::translateValue (context::Main &) const {
        return TypedExpression{valueType, c::addressof(allocation)}; // TODO: Cast to a const pointer?
    }

    //// Out ////

    DisplayResult value::Out::display () const {
        return "out(" + allocation + ")";
    }

    ValueTranslationResult value::Out::translateValue (context::Main &) const {
        return TypedExpression{valueType, c::addressof(allocation)}; // TODO: Cast to a const pointer?
    }

    //// Array ////

    ArithmeticSequence::ArithmeticSequence (Integral const & from, Integral const & to, Integral const & by):
        definition{
            CompleteValue{value::Int{from}},
            CompleteValue{value::Int{to}},
            CompleteValue{value::Int{by}}
        } {}

    CompleteType ArithmeticSequence::type () const {
        return interface::valueType || target::category{} <<= *definition.from;
    }

    Integral ArithmeticSequence::size () const {
        auto from = *interface::get<Integral>(*definition.from->get<value::Int>());
        auto to   = *interface::get<Integral>(*definition.from->get<value::Int>());
        auto by   = *interface::get<Integral>(*definition.from->get<value::Int>());
        return (to - from - 1) / by + 1; // TODO: Check if this makes sense.
    }

    esl::view<ArrayAllocation::Vector::iterator> ArrayAllocation::trimmedValue (Integral size) {
        return esl::view{value.begin(), value.begin() + size};
    }

    namespace {

        // Note: I'm copy-pasting some implementations here with some minor alterations temporarily,
        // because I don't want to change the respective headers until I test everything thouroughly,
        // which I don't have enough time for right now.

        // TODO: Incorporate these two into array_nodes::arrayAllocation and array_nodes::individualArrayInitialization respectively.
        // See (*) below.
        std::string globalArrayAllocation (
            context::Main            & ctx,
            tpl::TypeSpecifier const & type,
            Integral                   size
        ) {
            auto valType = ctx.global.instantiateType(tpl::Array{
                .elemType = type,
                .size     = size
            }); // cth_arr$<size>$<type>
            // (*) And here's a change:
            //auto valName = c::valueName(c::id(ctx.nextId()));
            auto valName = c::global(c::valueName(c::id(ctx.nextId())));
            auto valInit = c::zeroInitialization();
            auto alloc   = c::statement(c::definition(valType, valName, valInit));
            // (*) And here's another change:
            //ctx.function.insertAllocation(alloc);
            ctx.global.insertAllocation(alloc);
            return valName;
        }
        void globalIndividualArrayInitialization (
            context::Main                       & ctx,
            std::string                   const & allocation,
            esl::tiny_vector<std::string> const & elements
        ) {
            auto init = c::arrayIndividualInitialization(allocation, elements);
            // (*) Here's the only change that's needed for global allocations:
            //ctx.insertStatement(init);
            ctx.global.insertInitialization(init);
        }

    }

    std::string ArrayAllocation::allocate (context::Main & ctx) {
        if (variable)
            return *variable;

        auto translType  = *(interface::translateTypeSpecifier || target::category{} <<= type());
        auto translElems = interface::expression || target::tiny_vector{} <<=
            *(esl::unite_results <<= interface::translateResolvedValue(ctx) || target::sized_range_tiny_result{} <<= value);
        // An esl::result_error would indicate an implementation error here.
        // TODO: Why?

        auto allocName = globalArrayAllocation(ctx, std::move(translType), value.size());
        globalIndividualArrayInitialization(ctx, allocName, translElems);
        variable = allocName;
        return *variable;
    }

    std::optional<ArithmeticSequence> ArrayAllocation::sequentialize () {
        if (sequence)
            return *sequence;
        return [&] (sem::type::Int) -> std::optional<ArithmeticSequence> {
            Integral from;
            Integral count = 0;
            std::optional<Integral> step;
            std::optional<Integral> last;
            for (auto const & elem: value) {
                // Note: This assumes correct types.
                Integral val = elem.get<sem::value::Int>()->get();
                if (last) {
                    if (!step)
                        step = val - *last;
                    else if (step != val - *last)
                        return std::nullopt;
                } else {
                    last = val;
                    from = val;
                }
                ++count;
            }
            if (!step)
                return std::nullopt;
            sequence = ArithmeticSequence{from, from + count * *step, *step};
            return sequence;

        } | [] (auto) -> std::optional<ArithmeticSequence> {
            return std::nullopt;

        } || target::category{} <<= type();
    }

    CompleteType ArrayAllocation::type () const {
        return sequence ? sequence->type() : interface::valueType || target::category{} <<= value.front();
    }

    void ArrayAllocation::relax () {
        constant = false;
    }

    DisplayResult value::Array::display () const {
        return "array<" + valueType.display() + ">(...)";
    }

    ValueTranslationResult value::Array::translateValue (context::Main & ctx) const {
        return [&] (ArrayAllocation * alloc) -> ValueTranslationResult {
            auto val = alloc->allocate(ctx);
            return TypedExpression{valueType, val}; // TODO: Cast to a const pointer?

        } | [&] (std::string const & alloc) -> ValueTranslationResult {
            return TypedExpression{valueType, alloc}; // TODO: Cast to a const pointer?

        } || target::variant{} <<= allocation;
    }

    //// Buffer ////

    DisplayResult value::Buffer::display () const {
        return "buffer(...)";
    }

    ValueTranslationResult value::Buffer::translateValue (context::Main &) const {
        //return TypedExpression{valueType, c::bufferData(allocation)}; // TODO: Cast to a const pointer?
        return TypedExpression{valueType, c::expression(c::addressof(allocation))};
    }

    //// Function ////

    DisplayResult value::Function::display () const {
        return "function(...)";
    }

    ValueTranslationResult value::Function::translateValue (context::Main & ctx) const {
        auto typeCopy = valueType;
        typeCopy.definition = &definition;
        auto id = ctx.defineFunction(definition);
        if (!id) return id.error();
        return TypedExpression{typeCopy, closureVariable.value_or(c::emptyValue())};
    }

}
