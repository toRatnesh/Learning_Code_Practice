/*****

References

    Programming with C++20 | Andreas Fertig
    https://en.cppreference.com/w/cpp/language/constexpr.html
    https://en.cppreference.com/w/cpp/language/consteval.html

Chapter 12 | Doing (more) things at compiletime

12.5 consteval: Do things guaranteed at compiletime

consteval
    to mark functions, forcing the compiler to always evaluate them always at 
    compile time consteval doesn’t have a dual nature
    We get a compile error if the function cannot be evaluated at compile-time 
    or if the function contains forbidden statements in the compile-time path.

12.5.1 as_constant a use case for consteval
    To force a constexpr-function execution at compile-time 
    the function needs to be forced  into compile-time evaluation.

    With the help of consteval and abbreviated function templates
    , we can build ourselves a handy little helper as_constant:
    we can pass any constexpr function or constant value to as_constant, 
    forcing compile-time evaluation on it

12.5.2 Force compile-time evaluation for compile-time checks


12.5.3 is_constant_evaluated doesn’t make it compile-time
    We cannot call a consteval function in the std::is_constant_evaluated path
    The std::is_constant_evaluated() is used in a run-time if
    The result for the run-time path is, that std::is_constant_evaluated() returns false

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

consteval auto get_constant(const auto val) {
    return val;
}

int main(const int , char * argv[]) {

    constexpr char carr[] = "constexpr char array";
    static_assert(xstrlen(carr) == 20);
    assert(xstrlen(carr) == 20);

    constexpr auto alen = xstrlen(carr);
    //constexpr auto blen = xstrlen(argv[0]);     //  error: 'argv' is not a constant expression
    const auto blen = my_strlen(argv[0]);


    get_constant(2);
    //get_constant(carr);     // CE error: call to consteval function 'get_constant<const char *>' is not a constant expression

    return 0; 
}

/*****
    END OF FILE
**********/


