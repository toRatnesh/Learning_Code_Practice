/*****

References

    Programming with C++20 | Andreas Fertig
	https://en.cppreference.com/w/cpp/string/basic_string.html
    https://en.cppreference.com/w/cpp/string/basic_string/starts_with.html
    https://en.cppreference.com/w/cpp/string/basic_string/ends_with.html

Chapter 10 | New STL elements

10.7 starts_with and ends_with for std::string

	starts_with:    Checks if the string begins with the given prefix
    ends_with:      Checks if the string ends with the given suffix

**********/

#include <iostream>
#include <string>
#include <iomanip>

int main() {

    const std::string sval{"I am learning new C++ feature of std::string in C++"};
    const std::string prefix{"I am"};
    const std::string suffix{"C++"};

    if(sval.starts_with(prefix)) {
        std::cout << std::quoted(sval) << " starts with " << std::quoted(prefix) << '\n';
    }

    if(sval.ends_with(suffix)) {
        std::cout << std::quoted(sval) << " ends with " << std::quoted(suffix) << '\n';
    }

    // pre C++20
    if(sval.find(prefix) == 0) {
        std::cout << std::quoted(sval) << " starts with " << std::quoted(prefix) << '\n';
    }

    if(sval.rfind(suffix) == (sval.size() - suffix.size())) {
        std::cout << std::quoted(sval) << " ends with " << std::quoted(suffix) << '\n';
    }

	return 0;
}

/*****
    END OF FILE
**********/

