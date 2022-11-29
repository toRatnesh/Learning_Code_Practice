/********************

References:
	C++17 - The Complete Guide | Nicolai M. Josuttis

10. Compile-Time if

10.4 Using Compile-Time if Outside Templates

    if constexpr in non-template functions only need a compile-time expression resulting in bool. However, in that case in both the then and the else parts all statements always have to be valid even if discarded.

    Advantage: Reduces size of binary
    Because code in discarded branch does not become part of resulting program

*********************/

#include <iostream>
#include <string>
#include <type_traits>

auto compile_fail(int val) {
    if constexpr(4 == sizeof(int)) {
        return val * 4;        
    }
    else {
        //static_assert(false);   // this will fail always and program will fail to compile
        return val;
    }
}

template<typename T>
auto tfun(T val) {
    if constexpr(std::is_integral_v<decltype(val)>) {
        return std::to_string(val) + std::to_string(val);
    }
    else {
        return ++val++; // invalid statement in discarded else
    }
}

auto fun(int val) {
    if constexpr(std::is_integral_v<decltype(val)>) {
        return std::to_string(val) + std::to_string(val);
    }
    else {
        //return ++val++; // invalid statement in discarded else
        return ++val;
    }
}

int main() {

    std::clog << tfun(2) << '\n';
    std::clog << fun(2) << '\n';

    return 0;
}

/*************
    END OF FILE
*************/
