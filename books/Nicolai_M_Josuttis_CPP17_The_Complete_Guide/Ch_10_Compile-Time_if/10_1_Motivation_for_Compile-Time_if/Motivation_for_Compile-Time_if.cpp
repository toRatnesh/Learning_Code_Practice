/********************

References:
	C++17 - The Complete Guide | Nicolai M. Josuttis

10. Compile-Time if

10.1 Motivation for Compile-Time if
    If we’d use the run-time if in the example the corresponding code would never compile. This is a consequence of the rule that function templates usually are either not compiled or compiled as a whole.
    For example, when passing a numeric value, the compilation fails, because the f and third return statements would be invalid.

    only by using the compile-time if, the then and else parts that can’t be used become discarded statements
    For example, When passing a numeric value, the then part of the first if and the final else part get discarded.
    So, each invalid combination can’t occur any longer at compile-time and the code compiles successfully.

    Note that a discarded statement is not ignored. The effect is that it doesn’t get instantiated, when depending on template parameters. 
    The syntax must be correct and calls that don’t depend on template parameters must be valid.
    All static_asserts must also be valid, even in branches that aren’t compiled.

*********************/

#include <iostream>
#include <string>

constexpr int get() {
    if constexpr(4) {
        return 4;
    }
    else {
        return 1;
    }
}

template <typename T>
std::string asString(T x) {
    if constexpr(std::is_same_v<T, std::string>) {
        return x; // statement invalid, if no conversion to string
    }
    else if constexpr(std::is_arithmetic_v<T>) {
        return std::to_string(x);   // statement invalid, if x is not numeric
    }
    else {
        return std::string(x); // statement invalid, if no conversion to string
    }
}

template <typename T>
std::string assertion_condition_independent_of_template(T x) {
    if constexpr(std::is_same_v<T, std::string>) {
        return x; // statement invalid, if no conversion to string
    }
    else if constexpr(std::is_arithmetic_v<T>) {
        //static_assert(false, "this fails to compile because assertion condition does not depend on template parameter");
        return std::to_string(x);   // statement invalid, if x is not numeric
    }
    else {
        return std::string(x); // statement invalid, if no conversion to string
    }
}

template <typename T>
std::string assertion_condition_dependent_of_template(T x) {
    if constexpr(std::is_same_v<T, std::string>) {
        return x; // statement invalid, if no conversion to string
    }
    else if constexpr(std::is_arithmetic_v<T>) {
        static_assert(std::is_arithmetic_v<T>, "T is not arithmetic type");
        return std::to_string(x);   // statement invalid, if x is not numeric
    }
    else {
        return std::string(x); // statement invalid, if no conversion to string
    }
}

int main() {

    static_assert(4 == get());

    std::clog << asString(42) << '\n';
    std::clog << asString(std::string("hello")) << '\n';
    std::clog << asString("hello") << '\n';

    std::clog << assertion_condition_dependent_of_template(42) << '\n';

    return 0;
}

/********
    END OF FILE
********/
