/*****

References

	episode https://www.youtube.com/watch?v=9bHSiqXZhFI
    https://en.cppreference.com/cpp/language/consteval
    https://en.cppreference.com/cpp/language/if#Consteval_if

    code https://godbolt.org/z/joecdWMdb

    Consteval if
        The statement that begins with if consteval is known as the consteval if statement. All substatements of a consteval if statement are control-flow-limited statements.

        statement must be a compound statement, and it will still be treated as a part of the consteval if statement even if it is not a compound statement (and thus results in a compilation error):

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
        [[maybe_unused]] auto v2 = xdiv(4, 0);
    }


    return 0;
}

/*****
    END OF FILE
**********/

