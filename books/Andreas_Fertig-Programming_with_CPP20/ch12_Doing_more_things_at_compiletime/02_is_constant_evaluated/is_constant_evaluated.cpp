/*****

References

    Programming with C++20 | Andreas Fertig
    https://en.cppreference.com/w/cpp/language/constexpr.html

Chapter 12 | Doing (more) things at compiletime

12.2 is_constant_evaluated: Is this a constexprcontext?

    Detects whether the function call occurs within a constant-evaluated context.
    Returns true if the evaluation of the call occurs within the evaluation of 
    an expression or conversion that is manifestly constant-evaluated; otherwise returns false.

NOTES:
    When directly used as the condition of static_assert declaration or constexpr if statement, std::is_constant_evaluated() always returns true.
    Because if consteval is absent in C++20, std::is_constant_evaluated is typically implemented using a compiler extension.

12.2.1 Different things at compile and runtime


12.2.2 is_constant_evaluated is a runtime value
    In a constexpr if, std::is_constant_evaluated will always return true because the function is always evaluated during compile-time.

**********/

#include <format>
#include <iostream>
#include <type_traits>
#include <cstring>
#include <cassert>

constexpr auto withConstexpr() {
    if constexpr(std::is_constant_evaluated()) {      // ALWAYS TRUE
        return 1;
    }
    return 0;
}

constexpr auto withoutConstexpr() {
    if(std::is_constant_evaluated()) {
        return 1;
    }
    return 0;
}

constexpr size_t xstrlen(const char * str) {

    //if constexpr(std::is_constant_evaluated())  // ALWAYS TRUE
    if(std::is_constant_evaluated())
    {
        return *str ? (1 + xstrlen(str + 1)) : 0;
    }

    return strlen(str);
}

int main(const int , char * argv[]) {

    constexpr char sval[]{"Learning constexpr"};
    const auto slen = xstrlen(sval);
    static_assert(slen == 18);
    std::cout << std::format("string: {}, length: {}\n", sval, slen);


    const auto alen = xstrlen(argv[0]);
    //static_assert(alen == 10);  // CE error: the value of 'alen' is not usable in a constant expression
    std::cout << std::format("executable: {}, length: {}\n", argv[0], alen);

    std::cout << std::format("{}\n", R"(static_assert((std::is_constant_evaluated() ? 2 : 3) == 2))");
    static_assert((std::is_constant_evaluated() ? 2 : 3) == 2);
    
    std::cout << std::format("{}\n", R"(assert((std::is_constant_evaluated() ? 2 : 3) == 3))");
    assert((std::is_constant_evaluated() ? 2 : 3) == 3);


    {
        static_assert(withoutConstexpr() == 1);
        assert(withoutConstexpr() == 0);

        static_assert(withConstexpr() == 1);
        assert(withConstexpr() == 1);
    }

    return 0; 
}

/*****
    END OF FILE
**********/


