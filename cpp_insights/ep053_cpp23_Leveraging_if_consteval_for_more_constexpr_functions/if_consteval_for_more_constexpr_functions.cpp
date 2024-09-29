/*****

ep053_cpp23_Leveraging_if_consteval_for_more_constexpr_functions

References
    episode https://www.youtube.com/watch?v=5cFyn5b0f4w
    https://en.cppreference.com/w/cpp/types/is_constant_evaluated
    https://en.cppreference.com/w/cpp/language/if

**********/

#include <print>
#include <string_view>

consteval void compileTimeAssert(const bool condition, const std::string_view msg) {
    if (not condition) {
        throw(msg);
    }
}

constexpr void xAssert(const bool condition, const std::string_view msg) {
    //if (std::is_constant_evaluated()) 
    if consteval
    {
        compileTimeAssert(condition, msg);
    } else {
        if (not condition) {
            std::println("{}", msg);
            std::terminate();
        }        
    }
}

constexpr auto getVal(const int ival) {
    xAssert(ival > 5, "value should be greater than 5");
    return ival - 5;
}

int main() { 

    { constexpr auto val = getVal(7); static_assert(val == 2); }
    //{ constexpr auto val = getVal(5); static_assert(val == 0); }
    
    { auto val = getVal(7); }
    //{ auto val = getVal(5); }

    return 0; 
}

/*****
    END OF FILE
**********/
