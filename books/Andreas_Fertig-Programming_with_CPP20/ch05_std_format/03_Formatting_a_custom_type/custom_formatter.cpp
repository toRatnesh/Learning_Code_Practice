/*****

References

	Programming with C++20 | Andreas Fertig
	https://en.cppreference.com/w/cpp/utility/format.html
	https://en.cppreference.com/w/cpp/utility/format/spec.html

Chapter 5 | std::format Modern & typesafe text formatting
	
5.3 Formatting a custom type

    iostream    provide an overload for our type of operator<<
    printf      does allow to register custom convert functions in the GNU libc

    std::format
        specialize struct template std::formatter<T> for our type
        This type provides  two methods we must provide:
            ■ constexpr auto parse(format_parse_context& ctx)
            ■ auto format(const T& t, format_context& ctx)

5.3.1 Writing a custom formatter

    parse,  allows us to parse the format specifier
    format, does the actual formatting of the data

    check example code

5.3.2 Parsing a custom format specifier
    
    parse method gives us great fine control of the desired output
    the approach is to generate different format strings and simply call std::format_to for all the different combinations

**********/

#include <iostream>
#include <string>
#include <vector>
#include <format>
#include <cstdint>
#include <algorithm>

std::string make_upper(std::string s)
{
    std::transform(s.begin(), s.end(), s.begin(),
                // static_cast<int(*)(int)>(std::toupper)         // wrong
                // [](int c){ return std::toupper(c); }           // wrong
                // [](char c){ return std::toupper(c); }          // wrong
                   [](unsigned char c){ return std::toupper(c); } // correct
                  );
    return s;
}

struct Employee {
    std::string name;
    uint32_t    age;
    double      salary;
};


/* 
// 5.3.1 Writing a custom formatter
template<>
struct  std::formatter<Employee>
{
    constexpr auto parse(std::format_parse_context & ctx) {
        return ctx.begin();
    }

    auto format(const Employee & emp, std::format_context & ctx) const {
        return std::format_to(ctx.out(), "{1:15} {0:->5} {2:>8.2f}{3}", emp.age, emp.name, emp.salary, "₹");
    }

};

 */

// 5.3.2 Parsing a custom format specifier
template<>
struct  std::formatter<Employee>
{
    bool use_upper_case{false};

    constexpr auto parse(std::format_parse_context & ctx) {

        auto it = ctx.begin();

        auto is_char = [&](const char c){
            if( (it != ctx.end()) and (*it == c) ) {
                ++it;
                return true;
            }

            return false;
        };

        if(is_char('u')) { use_upper_case = true; }

        if( (it != ctx.end()) and (*it != '}') ) {
            throw std::format_error("Invalid format");
        }

        return it;

    }

    auto format(const Employee & emp, std::format_context & ctx) const {
        if(use_upper_case) {
            return std::format_to(ctx.out(), "{1:15} {0:->5} {2:>8.2f}{3}", emp.age, make_upper(emp.name), emp.salary, "₹");
        }

        return std::format_to(ctx.out(), "{1:15} {0:->5} {2:>8.2f}{3}", emp.age, emp.name, emp.salary, "₹");
    }

};



int main() {

    const std::vector<Employee>   employee_vec{
        {"employee-1", 32, 53.67},
        {"emp-2", 23, 33},
        {"contractor-3", 26, 43.6789},
    };

    {
        std::cout << std::format("=== 5.3.1 Writing a custom formatter ===\n");
        
        for(const auto & emp : employee_vec) {
            //std::cout << std::format("{1:15} {0:->5} {2:>8.2f}{3}\n", emp.age, emp.name, emp.salary, "₹");
            std::cout << std::format("{}\n", emp);
        }

        std::cout << std::format("\n=== 5.3.2 Parsing a custom format specifier ===\n");
        
        for(const auto & emp : employee_vec) {
            //std::cout << std::format("{1:15} {0:->5} {2:>8.2f}{3}\n", emp.age, emp.name, emp.salary, "₹");
            std::cout << std::format("{:u}\n", emp);
        }        
    }

	return 0;
}

/*****
    END OF FILE
**********/

