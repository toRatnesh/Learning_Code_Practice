/*****

References

	Programming with C++20 | Andreas Fertig
	https://en.cppreference.com/w/cpp/utility/format.html
	https://en.cppreference.com/w/cpp/utility/format/spec.html

Chapter 5 | std::format Modern & typesafe text formatting
	
5.2 Formatting a string using std::format

    C++20, in fact, brings us the combination of iostream and printf in the form of std::format

    std::format uses curly braces to specify format arguments
    Because std::format is a variadic template, the type of each argument is preserved

5.2.1 std::format specifiers

    .   std::format uses curly braces to specify format arguments. 
        In these braces, we can specify the type we expect and the format for it.
    .   We can further control the alignment, padding, the padding character, 
        and whether the formatting uses the current system locale

    { arg-id : fill-and-align sign # 0 width .precision L type }

    arg-id :    positional argument to use
    fill:       any character other than { or }
    align:      :>  left
                :<  right
                :^  center
    sign:       :+  negative and positive numbers have a sign
                :-  only negative numbers have a sign
                :␣  Insert leading space for non-negative numbers
    #:          prefix 0 0o 0O 0x or 0X
    width .precision:   positive int
    L:          locate aware formatting
    type:       a A b B c d e E f F g G o p s x X

    For std::format format specifiers
    https://en.cppreference.com/w/cpp/utility/format/spec.html

5.2.2 Escaping
    .   the start and end marker is just duplicated

5.2.3 Localization
    .   By default, all formatting of std::format is locale-independent
    .   for localized format add L to the format specifier before the type
        That way, the system’s current locale is used to format the format argument.
    .   we can use one of the std::format overloads, which takes a std::locale as the first argument

5.2.4 Formatting floating point numbers
    .   keep the provided value, but show only the required parts

**********/

#include <iostream>
#include <string>
#include <vector>
#include <format>
#include <cstdint>

struct Employee {
    std::string name;
    uint32_t    age;
    double      salary;
};

int main() {

    const std::vector<Employee>   employee_vec{
        {"employee-1", 32, 53.67},
        {"emp-2", 23, 33},
        {"contractor-3", 26, 43.6789},
    };

    {
        std::cout << std::format("=== std::format specifiers ===\n");
        
        for(const auto & emp : employee_vec) {
            std::cout << std::format("{:15} {:->5} {:>8.2f}\n", emp.name, emp.age, emp.salary);
        }
    }

    {
        std::cout << std::format("\n=== Escaping ===\n");
        std::cout << std::format("Having {{ }} in a string\n");
    }

    {
        std::cout << std::format("\n=== Localization ===\n");

        const auto lval = 1'234'567;
        {
            const auto locale_posix = std::locale("POSIX");
            std::cout << std::format(locale_posix, "1'234'567 in POSIX locale {:L}\n", lval); 
        }

        {
            const auto locale_us = std::locale("en_US.UTF-8");
            std::cout << std::format(locale_us, "1'234'567 in US locale {:L}\n", lval); 
        }
    }

    {
        std::cout << std::format("\n=== Formatting floating point numbers ===\n");

        const double dval1{2.3000};
        const double dval2{3.40};

        const double dval3{5.0000};
        const double dval4{6.0};

        std::cout << std::format("Printing double 2.3000: {}, 3.40: {}, 5.0000: {}, 6.0: {}\n", dval1, dval2, dval3, dval4);
        std::cout << std::format("Printing double 2.3000: {:f}, 3.40: {:f}, 5.0000: {:f}, 6.0: {:f}\n", dval1, dval2, dval3, dval4);     
    }

	return 0;
}

/*****
    END OF FILE
**********/

