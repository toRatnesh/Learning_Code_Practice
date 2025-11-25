/*****

References

	Programming with C++20 | Andreas Fertig
	https://en.cppreference.com/w/cpp/utility/format.html
	https://en.cppreference.com/w/cpp/utility/format/spec.html

Chapter 5 | std::format Modern & typesafe text formatting

5.5 Using a custom buffer

5.5.1 Formatting into a dynamically sized buffer

    std::format_to allows to format a string directly into a dynamic buffer
    std::formatted_size returns the number of characters the resulting string will take

    We can either write the formatted string into an empty buffer or 
    append a string writing to an existing dynamically increasing buffer like a std::vector
    
    std::format has no way of checking whether the size of the buffer is exceeded

    use std::format_to only with std::back_inserter to prevent buffer overflows
    std::back_inserter is used to append to an existing buffer

5.5.2 Formatting into a fixed sized buffer

    std::format_to_n not only gives us safe formatting that stays in bounds, 
    but also ensures that there are no memory allocations

**********/

#include <iostream>
#include <format>
#include <vector>
#include <iterator>
#include <string>
#include <string_view>
#include <array>

int main() {

    {
        std::cout << std::format("=== 5.5.1 Formatting into a dynamically sized buffer ===\n");

        {
            std::vector<char>   buffer;
            std::format_to(std::back_inserter(buffer), "{} {}", "Formatting in a dynamic buffer using std::format_to present in C++", 20);
            std::cout << std::string(buffer.data(), buffer.size()) << '\n';
        }

        {
            const std::string data{"ALREADY PRESENT DATA IN BUFFER "};
            std::vector<char>   buffer{data.begin(), data.end()};

            std::format_to(std::back_inserter(buffer), "{} {}", "Formatting in a dynamic buffer using std::format_to present in C++", 20);
            std::cout << std::string(buffer.data(), buffer.size()) << '\n';
        }

        {
            std::vector<char>   buffer(16);
            
            std::format_to(std::back_inserter(buffer), "{} {} {}", "std::format present in C++", 20, "can't check size of the buffer"); // std::back_inserter appends to buffer and does reallocation if needed

            //std::format_to(buffer.begin(), "{} {} {}", "std::format present in C++", 20, "can't check size of the buffer"); THIS LINE WILL CAUSE RUNTIME ERROR IF BUFFER SIZE IS SMALL
            
            std::cout << std::string(buffer.data(), buffer.size()) << '\n';
        }

        {
            constexpr std::string_view fmt_str{"{} {}"};
            const auto fmt_size = std::formatted_size(fmt_str, "Formatting in a preallocated dynamic buffer using std::format_to present in C++", 20);

            std::vector<char>   buffer(fmt_size);
            std::format_to(buffer.begin(), fmt_str, "Formatting in a preallocated dynamic buffer using std::format_to present in C++", 20);
            std::cout << std::string(buffer.data(), buffer.size()) << '\n';
        }

        {
            constexpr std::string_view fmt_str{"{} {}"};
            const auto arg1 = "Formatting in a preallocated dynamic buffer using std::format_to present in C++";
            const auto arg2 = 20;
            const auto fmt_size = std::formatted_size(fmt_str, arg1, arg2);

            std::vector<char>   buffer(fmt_size);
            std::format_to(buffer.begin(), fmt_str, arg1, arg2);
            std::cout << std::string(buffer.data(), buffer.size()) << '\n';
        }        

    }
    

    {
        std::cout << std::format("\n=== 5.5.2 Formatting into a fixed sized buffer ===\n");

        {
            std::array<char, 16>   buffer;

            std::format_to_n(buffer.data(), buffer.size()-1, "{} {}", "Formatting in a fixed sized buffer using std::format_to_n present in C++", 20);

            std::cout << buffer.data() << '\n';
        }

        {
            std::array<char, 1024>   buffer;

            std::format_to_n(buffer.data(), buffer.size()-1, "{} {}", "Formatting in a fixed sized buffer using std::format_to_n present in C++", 20);

            std::cout << buffer.data() << '\n';
        }

        
    }

    return 0;
}

/*****
    END OF FILE
**********/

