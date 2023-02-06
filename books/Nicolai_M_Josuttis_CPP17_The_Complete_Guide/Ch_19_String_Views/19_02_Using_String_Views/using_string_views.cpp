/*******

References
    C++17 - The Complete Guide | Nicolai M. Josuttis
	https://en.cppreference.com/w/cpp/string/basic_string_view

19 String Views

std::string_view objects refer to external character sequences without owning them.
The object can be considered as a reference to a character sequence.
It is also potentially dangerous, because similar to raw pointers it is up to the programmer to ensure that the referred character sequences is still valid

19.2 Using String Views
Two major applications of string views:
1. You might have allocated or mapped data with character sequences or strings and want to use this data without allocating more memory.
2. You want to improve the performance for functions/operations that receive strings just to directly process them read-only not needing a trailing null terminator.

At any time you might use the string view to initialize or assign their value to a std::string.
NOTE: using string views just like “the better string” can result to worse performance and to severe run-time errors.

******************/

#include <iostream>
#include <string>
#include <string_view>

void display(const std::string_view msg) {
    // read-only not needing a trailing null terminator
    std::clog << msg << '\n';
}

int main() {

    std::string     astr{"sample string"};
    display(astr);

    std::string     empty_str;
    display(empty_str);

    display("sample char array literal, using view there is no need to allocate memeory for it");

    std::string_view    asview{astr};
    std::string         str_using_view{asview}; // this will allocate memory
    std::clog << "str_using_view: " << str_using_view << '\n';

    return 0;
}

/*****
    END OF FILE
********/


