/*****

References

	episode https://www.youtube.com/watch?v=-cGbf7hZOWU
    https://en.cppreference.com/cpp/utility/source_location

    code https://godbolt.org/z/1P6WfzKbx

    The std::source_location class represents certain information about the source code, 
    such as file names, line numbers, and function names. 
    Previously, functions that desire to obtain this information about the call site 
    (for logging, testing, or debugging purposes) must use macros so that predefined macros 
    like __LINE__ and __FILE__ are expanded in the context of the caller. 
    The std::source_location class provides a better alternative.

    It is intended that std::source_location has a small size and can be copied efficiently.

    It is unspecified whether the copy/move constructors and the copy/move assignment operators 
    of std::source_location are trivial and/or constexpr.

**********/

#include <iostream>
#include <print>
#include <source_location>
#include <exception>

constexpr void XASSERT(const bool cond, 
                const std::string_view msg, 
                const std::source_location loc = std::source_location::current()) 
{

    if(not cond) {

        //if constexpr (std::is_constant_evaluated())   // THIS IS WRONG, IT WILL ALWAYS EVALUATE TO TRUE
        //if(std::is_constant_evaluated()) 
        if consteval                                    // BETTER, since C++23
        {
            
        } else {
            std::println(std::cerr, "[{}:{}] {}", loc.file_name(), loc.line(), msg);
        }

        std::terminate();

    }

}

constexpr int xdiv(const int m, const int n) {
    
    XASSERT(n != 0, "denominator can't be 0");

    return m/n;
}

int main() {

    {
        [[maybe_unused]] constexpr auto v1 = xdiv(4, 2);
        //[[maybe_unused]] constexpr auto v2 = xdiv(4, 0);
    }

    {
        [[maybe_unused]] auto v1 = xdiv(4, 2);
        //[[maybe_unused]] auto v2 = xdiv(4, 0);
    }

    std::println("sizeof(std::source_location) {}", sizeof(std::source_location));


    return 0;
}

/*****
    END OF FILE
**********/


