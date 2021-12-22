#pragma once

#include <concepts>
#include <optional>
#include <string>

#include "esl/containers.hpp"
#include "esl/lift.hpp"
#include "esl/ranges.hpp"
#include "esl/string.hpp"
#include "esl/tiny_vector.hpp"
#include "esl/zip.hpp"

// TODO: Either put this in the `sem::` namespace, or move it out of the `sem/` directory.
namespace cynth {

    namespace str {

        // Strings used to construct names:
        /***
        cth_bool
        cth_int
        var_<id>
        ctxvar_<id>
        itervar_<id>
        val_<id>
        inval_<id>
        <struct>.m_<id>
        <struct>.internal_member
        <tuple>.e<n>
        ***/
        constexpr char const * array     = "arr";
        constexpr char const * boolean   = "bool";
        constexpr char const * buffer    = "buff";
        constexpr char const * constant  = "const";
        constexpr char const * context   = "ctx";
        constexpr char const * element   = "e";
        constexpr char const * floating  = "float";
        constexpr char const * function  = "fun";
        constexpr char const * global    = "cth";
        constexpr char const * input     = "in";
        constexpr char const * integral  = "int";
        constexpr char const * iterator  = "iter";
        constexpr char const * member    = "m";
        constexpr char const * output    = "out";
        constexpr char const * string    = "str";
        constexpr char const * structure = "struct";
        constexpr char const * tuple     = "tup";
        constexpr char const * value     = "val";
        constexpr char const * variable  = "var";
        constexpr char const * variant   = "v";

        // Seaprator in template names:
        //constexpr char const * separator = "__";
        constexpr char const * separator = "$"; // GNU C (GCC) allows dollars, but other compilers might not.

        // Whitespace:
        //constexpr char const * indent = "\t";
        constexpr char const * indent  = "    ";
        constexpr char const * newLine = "\n";

        // GNU extensions and their alternate keywords:
        //constexpr char const * gnuTypeof = "typeof";
        constexpr char const * gnuTypeof    = "__typeof__";
        constexpr char const * gnuAuto      = "__auto_type";
        constexpr char const * gnuLabel     = "__label__";
        constexpr char const * gnuAttribute = "__attribute__";

    }

    namespace def {

        // Strings refering to names of internal implementation declarations:

        // Conversions:
        /***
        convert$<from>$<to>(<value>)
        ***/
        constexpr char const * convert = "convert";

#if 0
        // Arrays:
        // I'm not sure yet, how I'll implement and use this.
        constexpr char const * arrayCopy    = "arr_copy";
        constexpr char const * arrayCopyTo  = "arr_copy_to";
#endif

        // Built-in operations:
        /***
        op$<type>(<value>, ...)
        ***/
        constexpr char const * neg = "neg";
        constexpr char const * add = "add";
        constexpr char const * sub = "sub";
        constexpr char const * mul = "mul";
        constexpr char const * div = "div";
        constexpr char const * mod = "mod";

        // Buffers:
        /***
        <buff>.data
        <buff>.offset
        ***/
        constexpr char const * dataMember   = "data";
        constexpr char const * offsetMember = "offset";

        // Function contexts:
        constexpr char const * ctxDataMember = "data";
        constexpr char const * branchMember  = "branch";

        // Returning:
        /***
        __label__ ret;
        struct result {} result;
        ret: result;
        ***/
        constexpr char const * returnLabel    = "ret";
        constexpr char const * returnVariable = "result";
        constexpr char const * returnType     = "result";

        // Iteration:
        /***
        struct {
            cth_int pos;
            ...
        } iter = {0, ...}
        ***/
        constexpr char const * position  = "pos";
        constexpr char const * iteration = "iter";
    }

    namespace c {

        /**
         *  Most expressions are explicitly parenthesized to avoid precedence issues.
         *  By default, this doesn't introduce unnecessary parentheses.
         *  The expression is scanned for matching parentheses on both ends.
         *  However, this might be a slight translation time slowdown
         *  so set `neatParentheses` to false in the config if readable C code is not a concern.
         */
        /***
        `(<expr>)`
        ***/
        inline std::string expression (std::string const & expr) {
            constexpr bool neatParentheses = true; // TODO: Put this in some global config.
            if constexpr (neatParentheses)
                return esl::parenthesized(expr);
            else
                return std::string{} + "(" + expr + ")";
        }

        /***
        <stmt>;
        ***/
        inline std::string statement (std::string const & stmt) {
            return stmt + ";";
        }

        //// Whitespace ////

        /***
        \t...\t
        ***/
        inline std::string indentation (int n = 1) {
            return esl::repeat(str::indent, n);
        }

        /***
        \t...\t<stmt>
        ***/
        inline std::string indented (std::string stmt, int n = 1) {
            return indentation(n) + stmt;
        }

        inline std::string newLine () {
            return str::newLine;
        }

        //// Declarations & definitions ////

        /***
        <type> <name>
        ***/
        inline std::string declaration (std::string const & type, std::string const & name) {
            return type + " " + name;
        }

        /***
        <type> <name> = <val>
        ***/
        inline std::string definition (std::string const & type, std::string const & name, std::string const & val) {
            return type + " " + name + " = " + val;
        }

        //// Naming ////

        /**
         *  For now, I'll jsut use the unique id numbers in decimal
         *  but I might switch do hex or base64 representation later.
         *  TODO: Update code everyghere to use this function instead of std::to_string.
         */
        template <std::integral T>
        inline std::string id (T number) {
            return std::to_string(number);
        }

        /***
        cth_<name>
        ***/
        inline std::string global (std::string const & name) {
            return std::string{} + str::global + "_" + name;
        }

        /***
        # Statically allocated value
        val_<id> (no global prefix)
        ***/
        inline std::string valueName (std::string const & id) {
            return std::string{} + str::value + "_" + id;
        }

        /***
        # Statically allocated output value
        cth_outval_<id>
        ***/
        inline std::string outputValueName (std::string const & id) {
            return c::global(std::string{} + str::output + str::value + "_" + id);
        }

        /***
        # Statically allocated input value
        cth_inval_<id>
        ***/
        inline std::string inputValueName (std::string const & id) {
            return c::global(std::string{} + str::input + str::value + "_" + id);
        }

        /***
        # Statically allocated buffer value
        cth_buffval_<id>
        ***/
        inline std::string bufferValueName (std::string const & id) {
            return c::global(std::string{} + str::buffer + str::value + "_" + id);
        }

        /***
        # Statically allocated input buffer value
        cth_inbuffval_<id>
        ***/
        inline std::string inputBufferValueName (std::string const & id) {
            return c::global(std::string{} + str::input + str::buffer + str::value + "_" + id);
        }

        /***
        # Statically allocated output buffer value
        cth_outbuffval_<id>
        ***/
        inline std::string outputBufferValueName (std::string const & id) {
            return c::global(std::string{} + str::output + str::buffer + str::value + "_" + id);
        }

        /***
        # Local variable
        var_<id>
        ***/
        inline std::string variableName (std::string const & id) {
            return std::string{} + str::variable + "_" + id;
        }

        /***
        # For loop iteration variable
        itervar_<id>
        ***/
        /* TODO: Maybe won't be needed.
        inline std::string iterationVariableName (std::string const & id) {
            return std::string{} + str::iterator + str::variable + "_" + id;
        }
        */

        /***
        # Local tuple variable - returning from blocks.
        tupvar_<id>
        ***/
        inline std::string tupleVariableName (std::string const & id) {
            return std::string{} + str::tuple + str::variable + "_" + id;
        }

        // TODO: Might be not needed.
        /***
        # Struct member name
        m_<id>
        ***/
        inline std::string memberName (std::string const & id) {
            return std::string{} + str::member + "_" + id;
        }

        /***
        # Tuple struct member name
        e<number>
        ***/
        inline std::string tupleElementName (std::size_t number) {
            return std::string{} + str::element + std::to_string(number);
        }

        /***
        # Result struct member name
        e<number>
        ***/
        inline std::string returnElementName (std::size_t number) {
            return std::string{} + str::element + std::to_string(number);
        }

        /***
        # Local variable holding a function's context
        ctxvar_<id>
        ***/
        inline std::string contextVariableName (std::string const & id) {
            return std::string{} + str::context + str::variable + "_" + id;
        }

        /***
        # Function context type
        cth_ctx_<id>
        ***/
        inline std::string contextVariableType (std::string const & id) {
            return c::global(std::string{} + str::context + "_" + id);
        }

        /***
        cth_fun_<id>
        ***/
        inline std::string functionName (std::string const & id) {
            return c::global(std::string{} + str::function + "_" + id);
        }

        //// Built-in operations ////

        /***
        *<val>
        ***/
        inline std::string dereference (std::string const & val) {
            return "*" + val;
        }

        /***
        &<val>
        ***/
        inline std::string addressof (std::string const & val) {
            return "&" + val;
        }

        /***
        <array>[<index>]
        ***/
        inline std::string arraySubscript (std::string const & array, std::string const & index) {
            return array + "[" + index + "]";
        }

        /***
        <f>(<arg1>, <arg2>, ...)
        ***/
        template <typename... Ts>
        std::string call (std::string f, Ts const &... args) {
            return f + "(" + esl::join(", ", args...) + ")";
        }

        /***
        (<type>) <val>
        ***/
        inline std::string cast (std::string const & val, std::string const & type) {
            return c::global(str::boolean);
        }

        /***
        ++<val>
        ***/
        inline std::string increment (std::string const & val) {
            return "++" + val;
        }

        /***
        <target> += <diff>
        ***/
        inline std::string advance (std::string const & target, std::string const & diff) {
            return target + " += " + diff;
        }

        /***
        <cond> ? <pos> : <neg>
        ***/
        inline std::string ternary (std::string const & cond, std::string const & pos, std::string const & neg) {
            return cond + " ? " + pos + " : " + neg;
        }

        /***
        <a> < <b>
        ***/
        inline std::string lt (std::string const & a, std::string const & b) {
            return a + " < " + b;
        }

        //// Built-in types ////

        /***
        struct <name>
        ***/
        inline std::string structure (std::string const & name) {
            return std::string{} + "struct " + name;
        }

        /***
        struct <name> {
            <decl1>;
            <decl2>;
            ...
        }
        ***/
        template <typename... Ts>
        inline std::string structureDefinition (std::string const & name, Ts const &... decls) {
            auto head     = std::string{} + "struct " + name + " {";
            auto indent   = c::indentation();
            auto declEnd  = std::string{} + ";" + c::newLine();
            auto contents = esl::join(declEnd + indent, decls...);
            return head + (!contents.empty() ? c::newLine() + indent + contents + declEnd : "") + "}";
            // When empty: `struct <name> {}`
        }

        /***
        <type> const
        ***/
        inline std::string constness (std::string const & type) {
            return type + " const";
        }

        /***
        <type> volatile
        ***/
        inline std::string volatility (std::string const & type) {
            return type + " volatile";
        }

        /***
        <type> *
        ***/
        inline std::string pointer (std::string const & type) {
            return type + " *";
        }

        /***
        # GNU typeof extension
        typeof(<value>)
        ***/
        inline std::string infer (std::string const & value) {
            return std::string{} + str::gnuTypeof + "(" + value + ")";
        }

        /***
        # GNU auto type extension
        __auto_type
        ***/
        inline std::string autoType () {
            return str::gnuAuto;
        }

        //// Simple types ////

        // TODO: boolType, intType and floatType should be somehow connected with interface::directTypeName

        /***
        cth_bool
        ***/
        inline std::string boolType () {
            return c::global(str::boolean);
        }

        /***
        cth_int
        ***/
        inline std::string intType () {
            return c::global(str::integral);
        }

        /***
        cth_float
        ***/
        inline std::string floatType () {
            return c::global(str::floating);
        }

        //// Compound statements ////

        /***
        {\n\t<stmt1>;\n\t<stmt2>;\n\t...;\n\t<stmtN>;\n}
        ***/
        template <typename... Ts>
        inline std::string block (Ts const &... stmts) {
            return std::string{} +
                "{\n" + str::indent + esl::join(std::string{} + ";\n" + str::indent, stmts...) + ";\n}";
        }

        /***
        # GNU statement expression extension
        ({\n\t<stmt1>;\n\t<stmt2>;\n\t...;\n\t<stmtN>;\n})
        ***/
        template <typename... Ts>
        inline std::string blockExpression (Ts const &... stmts) {
            return std::string{} +
                "({\n" + str::indent + esl::join(std::string{} + ";\n" + str::indent, stmts...) + ";\n})";
        }

        //// Assignments ////

        /***
        <dst> = <src>
        ***/
        inline std::string assignment (std::string const & src, std::string const & dst) {
            return dst + " = " + src;
        }

        /***
        *<dst> = <src>
        ***/
        inline std::string valueAssignment (std::string const & src, std::string const & dst) {
            return c::assignment(c::dereference(dst), src);
        }

        //// Initialization ////

        /***
        .<dst> = <src>
        ***/
        inline std::string designatedInitialization (std::string const & src, std::string const & dst) {
            return "." + dst + " = " + src;
        }

        /***
        # Brace initialization
        {
            <arg1>,
            <arg2>,
            ...
        }
        ***/
        template <typename... Ts>
        std::string init (Ts const &... args) {
            auto indent  = c::indentation();
            auto newLine = c::newLine();
            auto contents = esl::join("," + newLine + indent, args...);
            return "{" + (!contents.empty() ? newLine + indent + contents + newLine : "") + "}";
        }

        /***
        {0}
        ***/
        inline std::string zeroInitialization () {
            return "{0}";
        }

        /***
        .data = <expr>
        ***/
        inline std::string dataInitialization (std::string const & expr) {
            return c::designatedInitialization(expr, def::dataMember);
        }

        /***
        .data.v<number> = <expr>
        ***/
        inline std::string contextDataInitialization (std::size_t number, std::string const & expr) {
            return c::designatedInitialization(
                expr, std::string{} + def::dataMember + "." + str::variant + std::to_string(number)
            );
        }

        /***
        .branch = <number>
        ***/
        inline std::string branchInitialization (std::size_t const & number) {
            return c::designatedInitialization(std::to_string(number), def::branchMember);
        }

        //// Structural access ////

        /***
        <structure>.<member>
        ***/
        inline std::string memberAccess (std::string const & structure, std::string const & member) {
            return structure + "." + member;
        }

        /***
        <structure>.e<number>
        ***/
        inline std::string tupleElement (std::string const & structure, std::size_t number) {
            return c::memberAccess(structure, c::tupleElementName(number));
        }

        /***
        # Union "variant"/"alternative"
        <structure>.v<number>
        ***/
        inline std::string unionVariant (std::string const & structure, std::size_t number) {
            return c::memberAccess(structure, str::variant + std::to_string(number));
        }

        /***
        # Buffer wrapper raw data
        <structure>.data
        ***/
        inline std::string bufferData (std::string const & structure) {
            return structure + "." + def::dataMember;
        }

        /***
        # Buffer wrapper offset
        <structure>.offset
        ***/
        inline std::string bufferOffset (std::string const & structure) {
            return structure + "." + def::dataMember;
        }

        /***
        # Result struct member access
        result.e<number>
        ***/
        inline std::string returnElement (std::size_t number) {
            return c::memberAccess(def::returnVariable, c::returnElementName(number));
        }

        //// Templates ////

        /***
        <tplArg1>$<tplArg2>$...
        ***/
        template <typename... Ts>
        std::string templateArguments (Ts const &... args) {
            return esl::join("$", args...);
        }

        /***
        const_<type>
        ***/
        inline std::string constantSpecifier (std::string const & type) {
            return std::string {} + str::constant + "_" + str::constant;
        }

        /***
        struct__<type>__const
        ***/
        inline std::string structureSpecifier (std::string const & type) {
            return std::string{} + str::structure + "_" + type;
        }

        /***
        struct cth_tup$<type1>$<type2>$...
        ***/
        template <typename... Ts>
        std::string tupleType (Ts const &... types) {
            return c::structure(c::global(std::string{} + str::tuple + c::templateArguments(types...)));
        }

        /***
        cth_arr$<size>$<type>
        # alternatively:
        typeof(<type> [<size>])
        ***/
        inline std::string arrayType (std::string const & size, std::string const & type) {
            return c::structure(c::global(c::templateArguments(std::string{} + str::array, size, type)));
            //return std::string{} + str::gnuTypeof + "(" + type + " " + "[" + size + "])";
        }

        /***
        struct cth_buff$<size>
        ***/
        inline std::string bufferType (std::string size) {
            return c::structure(c::global(c::templateArguments(std::string{} + str::buffer, size)));
        }

        /***
        cth_float const * const
        ***/
        inline std::string bufferPointer () {
            return c::constness(c::pointer(c::constness(c::floatType())));
        }

        /***
        <type>
        ***/
        inline std::string inputType (std::string const & type) {
            return c::volatility(type);
        }

        /***
        <type> *
        ***/
        inline std::string inputPointerType (std::string const & type) {
            return c::pointer(c::inputType(type));
        }

        /***
        <type>
        ***/
        inline std::string outputType (std::string const & type) {
            return type;
        }

        /***
        <type> *
        ***/
        inline std::string outputPointerType (std::string const & type) {
            return c::pointer(c::outputType(type));
        }

        //// Compound head (begin) & end ////

        /***
        # GNU statement expression extension
        ({
        ***/
        inline std::string blockExpressionBegin () {
            return "({";
        }

        /***
        # Extracting a returned value from an expression block.
        __auto_type <var> = ({
        ***/
        inline std::string blockExpressionBegin (std::string const & var) {
            return c::definition(c::autoType(), var, c::blockExpressionBegin());
        }

        /***
        # GNU statement expression extension
        })
        ***/
        inline std::string blockExpressionEnd () {
            return "({";
        }

        /***
        }
        ***/
        inline std::string end () {
            return "}";
        }

        /***
        {
        ***/
        inline std::string blockBegin () {
            return "{";
        }

        /***
        if (<cond>) {
        ***/
        inline std::string ifBegin (std::string const & cond) {
            return std::string{} + "if (" + cond + ") {";
        }

        /***
        else {
        ***/
        inline std::string elseBegin () {
            return "else {";
        }

        /***
        } else {
        ***/
        inline std::string cuddledElse () {
            return "} else {";
        }

        /***
        while (<cond>) {
        ***/
        inline std::string whileBegin (std::string const & cond) {
            return std::string{} + "while (" + cond + ") {";
        }

        /***
        for (<init>; <cond>; <iter>) {
        ***/
        inline std::string forBegin (std::string const & init, std::string const & cond, std::string const & iter) {
            return std::string{} + "for (" + init + ";" + cond + ";" + iter + ") {";
        }

        //// Looping ////


        /***
        struct {
            cth_int pos;
            <decl1>;
            <decl2>;
            ...
        } iter;
        ***/
        template <typename... Ts>
        std::string iterationStructure (Ts const &... decls) {
            auto indent  = c::indentation();
            auto declSep = ";" + c::newLine() + indent;
            auto posDecl = c::declaration(c::intType(), def::position);
            return c::structureDefinition(def::iteration, posDecl, decls...);
        }

        //// Labels ////

        /***
        goto <label>
        ***/
        inline std::string jump (std::string label) {
            return std::string{} + "goto " + label;
        }

        /***
        <label>:
        ***/
        inline std::string label (std::string label) {
            return label + ":";
        }

        /***
        # GNU extension - local labels
        __label__ <name>
        ***/
        inline std::string labelDeclaration (std::string const & name) {
            return std::string{} + str::gnuLabel + " " + name;
        }

        //// Returning ////

        // TODO: Might not be needed.
        /***
        __label__ ret;
        struct result {
            <type1> e0;
            <type2> e1;
            ...
        } result;
        ***/
        template <esl::sized_range T> requires (std::convertible_to<esl::range_value_type<T>, std::string>)
        inline std::string returnInit (T const & types) {
            esl::tiny_vector<std::string> decls;
            decls.reserve(decls.size());
            for (auto const & [i, type]: esl::enumerate(types))
                decls.push_back(std::string{type} + " " + c::tupleElementName(i));
            return
                c::statement(c::labelDeclaration(def::returnLabel)) + c::newLine() +
                c::statement(c::declaration(c::structureDefinition(def::returnType, decls), def::returnVariable));
        }

        /***
        __label__ ret;
        struct result {
            <type1> e0;
            <type2> e5; # Some elements can be skipped.
            ...
        } result;
        ***/
        template <esl::sized_range T> requires (std::convertible_to<esl::range_value_type<T>, std::string>)
        inline std::string returnInitFromDeclarations (T const & decls) {
            return
                c::statement(c::labelDeclaration(def::returnLabel)) + c::newLine() +
                c::statement(c::declaration(c::structureDefinition(def::returnType, decls), def::returnVariable));
        }

        /***
        ret: result;
        ***/
        inline std::string blockExpressionReturn () {
            return c::statement(c::label(def::returnLabel) + " " + def::returnVariable);
        }

        /***
        ret: <TODO>;
        ***/
        inline std::string mainReturn () {
            return c::statement(c::label(def::returnLabel) + " /* TODO */");
        }

        /***
        result.e<number> = <value>;
        goto ret;
        ***/
        inline std::string returnValue (std::size_t number, std::string const & value) {
            auto newLine = c::newLine();
            auto target  = c::returnElement(number);
            return
                c::statement(c::assignment(value, target)) + newLine +
                c::statement(c::jump(def::returnLabel));
        }

        /***
        result.e<number>.branch = <branch>;
        result.e<number>.data.v<branch> = <expr>; # optionally
        goto ret;
        ***/
        inline std::string returnFunction (
            std::size_t number,
            std::size_t branch,
            std::optional<std::string> const & value
        ) {
            auto newLine      = c::newLine();
            auto branchString = std::to_string(branch);
            auto branchTarget = c::memberAccess(c::returnElement(number), def::branchMember);
            if (value) {
                auto dataTarget = c::memberAccess(c::returnElement(number), def::ctxDataMember);
                return
                    c::statement(c::assignment(branchString, branchTarget)) + newLine +
                    c::statement(c::assignment(*value, dataTarget)) + newLine +
                    c::statement(c::jump(def::returnLabel));
            }
            return
                c::statement(c::assignment(branchString, branchTarget)) + " " +
                c::statement(c::jump(def::returnLabel));
        }

        //// Attributes ////

        /***
        # GNU extension
        __attribute__((<attr>))
        ***/
        inline std::string attribute (std::string const & attr) {
            return std::string{} + str::gnuAttribute + "((" + attr + "))";
        }

        /** Avoids warnings about unused declarations with -Wall. */
        inline std::string unused () {
            return c::attribute("unused");
        }

        /** Could be useful for some IO declarations. */
        inline std::string used () {
            return c::attribute("used");
        }

        /** A hot branch or a function. */
        inline std::string hot () {
            return c::attribute("hot");
        }

        /** A cold branch or a function. */
        inline std::string cold () {
            return c::attribute("cold");
        }

        /** A pure function. */
        inline std::string pure () {
            return c::attribute("pure");
        }

        //// Literals ////

        /***
        # Boolean literal
        (cth_bool) 0
        (cth_bool) 1
        ***/
        inline std::string boolLiteral (bool val) {
            return c::cast(val ? "1" : "0", c::boolType());
        }

        /***
        # Integer literal
        (cth_int) val
        ***/
        inline std::string intLiteral (int val) {
            return c::cast(std::to_string(val), c::intType());
        }

        // TODO: Note that it is also possible to construct arrays with a compound literal:
        // (int [4]) {1, 2, 3, 4}
        // This could be useful when passing around newly initialized arrays.
        /***
        # GNU compound literals extension
        (<structure>) {
            <init1>,
            <init2>,
            ...
        }
        ***/
        template <typename... Ts>
        inline std::string structureLiteral (std::string const & structure, Ts const &... inits) {
            return c::cast(c::init(inits...), structure);
        }

        /***
        (struct <type>) {
            .branch = <branch>,
            .data.v<branch> = <expr> # optionally
        }
        ***/
        inline std::string contextLiteral (
            std::string                const & type,
            std::size_t                const & branch,
            std::optional<std::string> const & expr
        ) {
            if (expr)
                return c::structureLiteral(
                    c::structure(type),
                    c::branchInitialization(branch),
                    c::contextDataInitialization(branch, *expr)
                );

            return c::structureLiteral(
                c::structure(type),
                c::branchInitialization(branch)
            );
        }

        //// Unsorted (TODO) ////

#if 0
        /***
        arr_copy(<src>)
        ***/
        inline std::string arrayCopy (std::string const & src) {
            return c::call(def::arrayCopy, src);
        }

        /***
        arr_copy_to(<src>)
        ***/
        inline std::string arrayCopyTo (std::string const & src, std::string const & dst) {
            return c::call(def::arrayCopy, src, dst);
        }
#endif

        // TODO: All functions should follow this parameter order:
        // name, type, value (e.g. declare(name, type), define(name, type, value))
        // except when there is a "source" and "destination", then it should be:
        // source, destination
        // (e.g. cast(value, type))

    }

    namespace tpl {

        /** E.g. `const_struct_cth_foo_bar` -> `struct cth_foo_bar const` */
        struct TypeSpecifier {
            constexpr static char const * delim = "_";

            std::string type;
            bool constant  = false;
            bool structure = false;

            // TODO: Should I omit the `cth` prefix in the merged form?
            // It would make the merged type names shorter,
            // but keeping the prefix will be simpler to implement and will be more flexible.
            std::string merged () const {
                if (constant && structure)
                    return std::string{} + str::constant + delim + str::structure + delim + type;
                if (constant)
                    return std::string{} + str::constant + delim + type;
                if (structure)
                    return std::string{} + str::structure + delim + type;
                return type;
            }

            std::string full () const {
                if (constant && structure)
                    return c::constness(c::structure(c::global(type)));
                if (structure)
                    return c::structure(c::global(type));
                if (constant)
                    return c::constness(c::global(type));
                return type;
            }
        };

        inline std::string mergeTypeSpecifier (TypeSpecifier spec) {
            return spec.merged();
        }

        struct Array {
            std::size_t   size;
            TypeSpecifier elemType;

            std::string name () const {
                return c::arrayType(std::to_string(size), elemType.merged());
            }

            std::string definition () const {
                return std::string{} + "typedef " + elemType.full() + " " + name() + " [" + std::to_string(size) + "]";
            }
        };

        struct Buffer {
            std::size_t size;

            std::string name () const {
                return c::bufferType(std::to_string(size));
            }

            std::string definition () const {
                return c::structureDefinition(
                    name(),
                    c::declaration(c::floatType(), def::dataMember),
                    c::declaration(c::intType(), def::offsetMember)
                );
            }
        };

        struct Tuple {
            esl::tiny_vector<TypeSpecifier> types;

            std::string name () const {
                return c::tupleType(
                    esl::lift<esl::target::vector>(mergeTypeSpecifier)(types)
                );
            }

            std::string definition () const {
                std::vector<std::string> decls;
                decls.reserve(types.size());
                for (auto const & [i, s]: esl::enumerate(types))
                    decls.push_back(c::declaration(s.full(), c::tupleElementName(i)));
                return c::structureDefinition(name(), decls);
            }
        };

    }

}
