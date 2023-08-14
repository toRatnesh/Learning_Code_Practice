/***********

    This example demonstrates aboout C++23 Lambda attributes
    new form attr with places to apply
    auto l = [] [[attr]] ([[attr]] auto) [[attr]] { };


    Lambda attr (since C++23) 
    If an attribute specifier sequence appears before the parameter list,  lambda specifiers, or noexcept specifier, 
    it applies to the function call operator or operator template of the closure type (and thus the [[noreturn]] attribute can be used). 
    Otherwise, it applies to the type of the function call operator or operator template.

    For more info visit
    episode https://www.youtube.com/watch?v=YlmxNJnone0
    https://en.cppreference.com/w/cpp/language/lambda
    https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2021/p2173r1.pdf
    https://eel.is/c++draft/expr.prim.lambda

****************/

#include <iostream>

struct lambda_impl {
    [[nodiscard]]
    auto operator() [[deprecated]] (auto val) {
        return val * 2;
    }
};

int main() {

    auto get_double = [] [[nodiscard]] (auto val) [[deprecated]] { return val * 2; };

    get_double(3);
    std::cout << get_double(3) << '\n';

    lambda_impl gd;
    //gd(4);
    //std::cout << gd(4) << '\n';

    return 0;
}

/***********
    END OF FILE
****************/



