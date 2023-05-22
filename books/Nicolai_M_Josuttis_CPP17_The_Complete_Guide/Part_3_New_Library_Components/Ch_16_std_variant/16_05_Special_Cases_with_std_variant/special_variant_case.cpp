/*********

References
    C++17 - The Complete Guide | Nicolai M. Josuttis
    https://en.cppreference.com/w/cpp/utility/variant

Chapter 16 std::variant<>
    std::variant<>
        a new union class
        supports a new way of polymorphism and dealing with inhomogeneous collections
        allows us to deal with elements of different data types  without the need for a common base class and pointers (raw or smart).

16.5 Special Cases with std::variant<>

16.5.1 Having Both bool and std::string Alternatives

	assigning string literals can become surprising because a string literal converts better to bool than to std::string
	couple of options to “fix” the assignment
		use emplace<> with alternative index
		use emplace<> with std::string type
		assign object of std::string type
		assign string literals with ""s

************/

#include <iostream>
#include <string>
#include <variant>


int main() {

    {
    std::cout << "=== Issue with Both bool and std::string Alternatives ===\n";
    {
        std::variant<std::string, bool> vval{"sample string"};
        std::cout << "vval.index() " << vval.index() << '\n';        
    }
    {
        std::variant<std::string, bool> vval;
        vval = "sample string";
        std::cout << "vval.index() " << vval.index() << '\n';        
    }

    {
        std::variant<bool, std::string> vval{"sample string"};
        std::cout << "vval.index() " << vval.index() << '\n';        
    }
    {
        std::variant<bool, std::string> vval;
        vval = "sample string";
        std::cout << "vval.index() " << vval.index() << '\n';        
    }
    }

    {
    std::cout << "=== Fix for Both bool and std::string Alternatives ===\n";
    {
        std::variant<bool, std::string> vval{"sample string"};
        std::cout << "vval.index() " << vval.index() << '\n';        
    }
    {
        std::variant<bool, std::string> vval;
        vval = "sample string";
        std::cout << "vval.index() " << vval.index() << '\n';        
    }
    }

    return 0;
}

/*********
    END OF FILE
************/


