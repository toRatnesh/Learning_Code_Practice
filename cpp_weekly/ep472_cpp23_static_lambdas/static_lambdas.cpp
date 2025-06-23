/*****

References
    episode https://www.youtube.com/watch?v=M_AUMiSbAwQ
    https://en.cppreference.com/w/cpp/language/lambda
    https://en.cppreference.com/w/cpp/language/function#Explicit_object_parameter

static Lambda since C++23
    Specifies that operator() is a static member function.
    static and mutable cannot be specified at the same time.
    Cannot be used if captures is not empty, or an explicit object parameter is present.

Explicit object parameter
    parameter declaration with the specifier this (syntax (2)/(5)) declares an explicit object parameter.    
    attr(optional) this decl-specifier-seq declarator                           (2)	(since C++23)
    attr(optional) this decl-specifier-seq abstract-declarator(optional)        (5)	(since C++23)

**********/

#include <iostream>
#include <string>
#include <memory>
#include <array>

int main() {

    {   std::puts("=== Lambda without capture on heap ===");
        // CE error: 'mutable' specifier conflicts with 'static'
        auto lambda = [] (const int multiplier) static /*mutable*/ { 
            std::puts("Lambda without capture"); 
            return 5 * multiplier;
        };
        const auto res = lambda(5);
        std::puts(std::to_string(res).c_str());
    }

    {   std::puts("\n === Lambda with capture on heap ===");
        // error: 'static' lambda specifier with lambda capture
        auto lambda = [arr = std::array<int, 1024>{1, 2, 3, 4}] (const int multiplier) /*static*/ { 
            std::puts("Lambda with capture"); 
            return 5 * multiplier * arr[2];
        };
        const auto res = lambda(5);
        std::puts(std::to_string(res).c_str());

    }
    
    return 0;
}

/*****
    END OF FILE
**********/


