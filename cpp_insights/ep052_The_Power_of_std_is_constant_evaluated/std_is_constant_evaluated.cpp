/*****

ep052_The_Power_of_std_is_constant_evaluated

References
    episode https://www.youtube.com/watch?v=S4Zv0Qh20vY
    https://en.cppreference.com/w/cpp/types/is_constant_evaluated

**********/

#include <print>
#include <string_view>

constexpr void xAssert(const bool bval, const std::string_view msg) {
    if (not std::is_constant_evaluated()) {
        if (not bval) {
            std::println("{}", msg);
            std::terminate();
        }

    } else {

    }
}

constexpr auto getVal(const int ival) {
    xAssert(ival > 5, "value should be greater than 5");
    return ival - 5;
}

int main() { 

    { constexpr auto val = getVal(7); static_assert(val == 2); }
    { constexpr auto val = getVal(5); static_assert(val == 0); }
    
    { auto val = getVal(7); }
    { auto val = getVal(5); }

    return 0; 
}

/*****
    END OF FILE
**********/
