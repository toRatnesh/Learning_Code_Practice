/*****

References

    Programming with C++20 | Andreas Fertig
    https://en.cppreference.com/w/cpp/language/constexpr.html
    https://en.cppreference.com/w/cpp/language/consteval.html
    https://en.cppreference.com/w/cpp/language/constinit.html

Chapter 12 | Doing (more) things at compiletime

12.6 constinit: Initialize a non-const object at compile-time

    constinit is an assertion that asserts that a variable is initialized with constant initialization.
    The scope of constinit is therefore limited to variables with static storage duration,
    e.g. global variables or static variables.

12.6.1 The static initialization order problem


12.6.2 Ensure compile-time initialization

    constinit is to assert that constant initialization happens.
    Once applied to the variable that must be initialized at compile-time,

    You can say that all constinit does is to check that the constructor 
    of the object is constexpr or consteval.

    You can see constexpr as constinit plus const

**********/

#include <format>
#include <iostream>
#include <cassert>
#include <cstring>

consteval size_t xstrlen(const char * str) {
    return *str ? (1 + xstrlen(str + 1)) : 0;
}

constexpr size_t my_strlen(const char * str) {
    if(std::is_constant_evaluated()) {
        //return xstrlen(str);    // CE error: call to consteval function 'xstrlen(str)' is not a constant expression
        return *str ? (1 + my_strlen(str + 1)) : 0;
    }
    
    return strlen(str);
}

int main(const int , char * argv[]) {

    static constinit char carr[] = "constexpr char array";
    static_assert(sizeof(carr) == 21);
    
    //static constinit auto alen = xstrlen(carr);
    //constinit auto alen = xstrlen(carr);    // CE error: 'constinit' can only be applied to a variable with static or thread storage duration
    
    //static constinit auto exe = argv[0];        // CE error: 'constinit' variable 'exe' does not have a constant initializer
    static constinit auto ival{20};

    return 0; 
}

/*****
    END OF FILE
**********/


