/*****

References

    Programming with C++20 | Andreas Fertig
    https://en.cppreference.com/w/cpp/language/constexpr.html

Chapter 12 | Doing (more) things at compiletime

12.1 The two worlds: compile_vs_run_time

    For constexpr functions to execute at compile time, 
    we need to force a constexpr-context, 
    which in the standard is called a constant expression


    Updates to constexpr functions:

    ============================================================================
    Functionality                                   11      14      17      20
    ============================================================================
    constexpr member-function implicitly const      ✔
    
    void as return-type                                     ✔
    More than just a single return                          ✔
    Using throw a(*)                                        ✔

    inline for static members with constexpr                        ✔
    Lambda can be implicitly constexpr                              ✔

    try/catch-Block(**)                                                     ✔
    Use of new / delete                                                     ✔
    constexpr virtual member functions                                      ✔
    Inline asm                                                              ✔
    ============================================================================
    *   May not be called on the constexpr path.
    **  As we can’t throw, we can never reach the catch-block on the constexpr path.    


12.1.1 The benefit of compiletime execution

    if that function is never invoked in a run-time context, 
    its code will not be in the resulting binary

**********/

#include <format>
#include <iostream>

constexpr size_t xstrlen(const char * str) {
    return *str ? (1 + xstrlen(str + 1)) : 0;
}

int main(const int , char * argv[]) {

    constexpr char sval[]{"Learning constexpr"};
    const auto slen = xstrlen(sval);        // COMPILE TIME
    static_assert(slen == 18);

    std::cout << std::format("string: {}, length: {}\n", sval, slen);

    const auto alen = xstrlen(argv[0]);     // RUN TIME
    //static_assert(alen == 21);  // error: the value of ‘alen’ is not usable in a constant expression
    std::cout << std::format("executable: {}, length: {}\n", argv[0], alen);

    return 0; 
}

/*****
    END OF FILE
**********/


