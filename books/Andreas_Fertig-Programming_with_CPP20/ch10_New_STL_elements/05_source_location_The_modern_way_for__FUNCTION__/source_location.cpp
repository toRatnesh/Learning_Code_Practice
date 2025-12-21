/*****

References

    Programming with C++20 | Andreas Fertig
    https://en.cppreference.com/w/cpp/utility/source_location.html

Chapter 10 | New STL elements

10.5 source_location: The modern way for __FUNCTION__

    The std::source_location class represents certain information about the source code, 
    such as file names, line numbers, and function names.

**********/

#include <format>
#include <iostream>
#include <source_location>

constexpr auto ASSERT(
    const bool cond, const std::string_view msg,
    const std::source_location location = std::source_location::current()) {

        if (not cond) {
            const auto logit = std::format("[{} {} {}]", location.file_name(), location.line(), location.function_name());
            std::cout << msg << " at " << logit << '\n';
        }
        
    }

int main() { 

    const auto val{5};
    ASSERT(5 != val, "value is not equal to 5");

    return 0; 
}

/*****
    END OF FILE
**********/
