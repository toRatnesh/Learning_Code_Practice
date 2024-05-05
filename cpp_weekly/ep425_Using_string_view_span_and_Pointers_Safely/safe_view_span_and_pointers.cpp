
/*****

    This example demonstrates about potential risk of using 
    string_view, span and pointers
    these are pointers to others data and the uderlying data may be released or destructed
    and in that case they may cause UB

    Reason: implicit conversion from string to string_view 
    Solution:
        Enable warnings
        Use address sanitizers
        use constexpr

**********/

#include <iostream>
#include <string>
#include <string_view>

constexpr std::string_view get_right_view() {
    return "Const character litreals have same lifetime as program so this is correct behaviour";
}

std::string_view get_wrong_view() {
    std::string msg("This function has UB because of msg will go out of scope after return");
    return msg;
}

int main() {

    {
    constexpr auto val = get_right_view();
    std::cout << val << '\n';
    }
    {
    const auto val = get_wrong_view();
    std::cout << val << '\n';        
    }

    return 0;
}

/*****
    END OF FILE
**********/


