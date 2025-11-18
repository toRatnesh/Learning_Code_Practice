/*****

References

	Programming with C++20 | Andreas Fertig
	https://en.cppreference.com/w/cpp/utility/format.html
	https://en.cppreference.com/w/cpp/utility/format/spec.html

Chapter 5 | std::format Modern & typesafe text formatting
	
5.4 Referring to a format argument

    we can put argument index before ':' in format specifier to refer to an argument

    we can provide argument in any order and use argument index to format them
    we need to provide argument indices for all the format specifiers

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
        std::cout << std::format("=== without using format argument index ===\n");
        
        for(const auto & emp : employee_vec) {
            std::cout << std::format("{:15} {:->5} {:>8.2f}₹\n", emp.name, emp.age, emp.salary);
        }   
    }

    {
        std::cout << std::format("\n=== using format argument index ===\n");
        
        for(const auto & emp : employee_vec) {
            std::cout << std::format("{1:15} {0:->5} {2:>8.2f}{3}\n", emp.age, emp.name, emp.salary, "₹");
        }   
    }

	return 0;
}

/*****
    END OF FILE
**********/

