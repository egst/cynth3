#pragma once

#include <cmath>

#include "sem/numeric_types.hpp"

namespace cynth::sem {

    constexpr auto plus  = [] <typename T> (T a)      { return +a;     };
    constexpr auto minus = [] <typename T> (T a)      { return -a;     };
    constexpr auto inc   = [] <typename T> (T a)      { return ++a;    };
    constexpr auto dec   = [] <typename T> (T a)      { return --a;    };
    constexpr auto add   = [] <typename T> (T a, T b) { return a + b;  };
    constexpr auto sub   = [] <typename T> (T a, T b) { return a - b;  };
    constexpr auto mul   = [] <typename T> (T a, T b) { return a * b;  };
    constexpr auto div   = [] <typename T> (T a, T b) { return a / b;  };
    constexpr auto mod   = [] <typename T> (T a, T b) { return a % b;  };
    constexpr auto fmod  = [] <typename T> (T a, T b) { return std::fmod(a, b); };
    constexpr auto pow   = [] <typename T> (T a, T b) { return std::pow(a, b);  };
    constexpr auto lt    = [] <typename T> (T a, T b) { return a < b;  };
    constexpr auto gt    = [] <typename T> (T a, T b) { return a > b;  };
    constexpr auto le    = [] <typename T> (T a, T b) { return a <= b; };
    constexpr auto ge    = [] <typename T> (T a, T b) { return a >= b; };
    constexpr auto eq    = [] <typename T> (T a, T b) { return a == b; };
    constexpr auto ne    = [] <typename T> (T a, T b) { return a != b; };
    constexpr auto lnot  = [] <typename T> (T a)      { return !a;     };
    //constexpr auto land  = [] <typename T> (T a, T b) { return a && b; };
    //constexpr auto lor   = [] <typename T> (T a, T b) { return a || b; };
    constexpr auto land  = [] (auto a, auto b)        { return a && b; };
    constexpr auto lor   = [] (auto a, auto b)        { return a || b; };
    constexpr auto bnot  = [] <typename T> (T a)      { return ~a;     };
    constexpr auto band  = [] <typename T> (T a, T b) { return a & b;  };
    constexpr auto bor   = [] <typename T> (T a, T b) { return a | b;  };
    constexpr auto bxor  = [] <typename T> (T a, T b) { return a ^ b;  };

    // TODO: Decide if single type (i.e. <typename T> (T a, T b)) or potentially different types (i.e. (auto a, auto b))
    // Note: land and lor need different types because they must accept lazy values, which are always composed of different ad-hoc created functor types.

    // TODO: Better modulo semantics.
    // TODO: Better conversions.

    // TODO: Division by 0? (And other special floating point values...)

    constexpr auto btoi = [] (bool     a) -> Integral { return a; };
    constexpr auto itob = [] (Integral a) -> bool     { return a; };
    constexpr auto itof = [] (Integral a) -> Floating { return a; };
    constexpr auto ftoi = [] (Floating a) -> Integral { return a; };
    constexpr auto btof = [] (bool     a) -> Floating { return itof(btoi(a)); };
    constexpr auto ftob = [] (Floating a) -> bool     { return itob(ftoi(a)); };

}
