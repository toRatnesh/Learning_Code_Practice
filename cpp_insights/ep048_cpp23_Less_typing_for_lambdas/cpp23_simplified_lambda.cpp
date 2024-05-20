
/*****

    References:
    episode : https://www.youtube.com/watch?v=t67j-uHaDTg
    C++ Weekly - Ep 273 - C++23's Lambda Simplification 
    https://github.com/toRatnesh/Learning_Code_Practice/blob/main/cpp_weekly/ep273_cpp23_Lambda_Simplification/lambda_with_optional_paramlist.cpp

    This example demonstrates about lambda improvement in C++23
    
    1. more optional () for lambdas
        Parentheses () is not required for
            lambda template parameters
            constexpr
            mutable
            consteval
            Exception specifications and noexcept
            attributes
            trailing return types
            requires
    2. Attributes on lambdas
    3. Change scope of lambda trailing-return-type

**********/

#include <iostream>

int main() {

    {
        std::cout << "=== more optional () for lambdas ===\n";
        auto l = [j = 5] mutable { return ++j; };
        std::cout << "l() " << l() << '\n';
    }
    
    {
        std::cout << "=== Attributes on lambdas ===\n";
        auto l = [] [[nodiscard]] (int val)  { return val; };
        std::cout << "l(7) " << l(7) << '\n';
        l(7);   // this will generate warning
    }
    
    {
        std::cout << "=== Change scope of lambda trailing-return-type ===\n";
        auto l = [j = 5] { return j; };
        std::cout << "l() " << l() << '\n';
    }

    return 0;
}

/*****
    END OF FILE
**********/

