/*****

References

	Programming with C++20 | Andreas Fertig
	https://en.cppreference.com/w/cpp/utility/format.html

Chapter 5 | std::format Modern & typesafe text formatting
	
5.1 Formatting a string before C++20
    before C++20 we use iostreams or snprintf or a library
    both have their pros and cons

5.1.1 Formatting a stock index with iostreams
    .   iostreams requires care and some knowledge about which functions to call
    .   as soon as localization gets in, things get a bit more complicated
    .   iostreams are type-safe

    . with iostreams atomic write is not possible because of multiple invocations of operator<<

5.1.2 Formatting a stock index with printf
    .   advantage atomicity, printf is a variadicfunction and takes all its arguments in a single call
        we can write them easier atomically without the risk of interleaved output, as we have with iostream
    .   POSIX version of printf mandates that the operation must be thread-safe

    .   No checks are possible to determine whether the argument matches the format argument


iostream has the advantage of type-safety while 
printf provides a readable format string and is only a single function call

std::format offers both type-safety and readable format string

**********/

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <cstdint>

struct Employee {
    std::string name;
    uint32_t    age;
    double      salary;
};


std::ostream & operator<<(std::ostream & os, const Employee & emp) {

    std::cout << std::setprecision(2);
    //std::cout << std::fixed;
    std::cout << std::scientific;

    std::cout << std::setw(15) << std::left << emp.name << ' ' 
    << std::setw(5) << std::right << emp.age << ' ' 
    << std::setw(8) << std::right << emp.salary << '\n';  

    return os;  
}

int main() {
    const std::vector<Employee>   employee_vec{
        {"employee-1", 32, 53.67},
        {"emp-2", 23, 33},
        {"contractor-3", 26, 43.6789},
    };

    const double dval1{2.3000};
    const double dval2{3.40};

    const double dval3{5.0000};
    const double dval4{6.0};

    {
        std::cout << "=== 5.1.1 Formatting with iostreams ===\n";
        std::cout << "\n--- Using simple iostream(std::cout) to print ---\n";
        for(const auto & emp : employee_vec) {
            std::cout << emp.name << ' ' << emp.age << ' ' << emp.salary << '\n';
        }

        std::cout << "\n--- Using std manipulator ---\n";
        for(const auto & emp : employee_vec) {

            std::cout << std::setprecision(2);
            std::cout << std::fixed;
            //std::cout << std::scientific;

            std::cout << std::setw(15) << std::left << emp.name << ' ' 
            << std::setw(5) << std::right << emp.age << ' ' 
            << std::setw(8) << std::right << emp.salary << '\n';
        }

        std::cout << "\n--- Using overloaded operator<< ---\n";
        for(const auto & emp : employee_vec) {
            std::cout << emp;
        }

        std::cout << "\n--- Using locale ---\n";
        for(const auto & emp : employee_vec) {

            std::cout << std::setprecision(2);
            //std::cout << std::fixed;
            std::cout << std::scientific;

            //std::cout.imbue(std::locale("de_DE.UTF-8"));
            std::cout.imbue(std::locale("POSIX"));

            std::cout << std::setw(15) << std::left << emp.name << ' ' 
            << std::setw(5) << std::right << emp.age << ' ' 
            << std::setw(8) << std::right << emp.salary << '\n';            
        }

        std::cout << std::fixed << "\nPrinting double 2.3000: " << dval1 << ", 3.40: " << dval2 << ", 5.0000: " << dval3 << ", 6.0: " << dval4 << '\n';

    }

    {
        std::cout << "\n=== 5.1.2 Formatting with printf ===\n";

        for(const auto & emp : employee_vec) {
            std::printf("%-15s %5d %8.2f\n", emp.name.c_str(), emp.age, emp.salary);
        }

        std::printf("\nPrinting double 2.3000: %f, 3.40: %f, 5.0000: %f, 6.0: %f \n", dval1, dval2, dval3, dval4);
    }

	return 0;
}

/*****
    END OF FILE
**********/

