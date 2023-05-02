/********************

References:
	C++17 - The Complete Guide | Nicolai M. Josuttis

10. Compile-Time if

10.3 Compile-Time if with Initialization
    compile-time if can also use the new form of if with initialization

*********************/

#include <iostream>
#include <string>
#include <type_traits>
#include <functional>

template<typename T>
constexpr auto getConstexprVal(T t) { return t; }

template<typename T>
constexpr auto getConstexprSquare(T t) { return t * t; }

template<typename T>
constexpr auto get(T t) {
    if constexpr(auto obj = getConstexprVal(t); std::is_same_v<decltype(obj), int>) {
        return t * t;
    }
    else {
        return t;
    }
}

template<typename T>
constexpr auto getVal(T t) {
    constexpr int val = 10;
    if constexpr(constexpr auto obj = getConstexprSquare(val); ((obj == 100) && std::is_same_v<T, int>)) {
        return t * t;
    }
    else {
        return t;
    }
}

int main() {

    static_assert(4 == get(2));
    static_assert(16 == get(4));
    static_assert(2.5 == get(2.5));
    static_assert(4.9f == get(4.9f));
    static_assert("sample" == get("sample"));

    static_assert(4 == getVal(2));
    static_assert(16 == getVal(4));
    static_assert(2.5 == getVal(2.5));
    static_assert(4.9f == getVal(4.9f));
    static_assert("sample" == getVal("sample"));

    return 0;
}

/********
    END OF FILE
********/
