/*****

References

    Programming with C++20 | Andreas Fertig
    https://en.cppreference.com/w/cpp/container/array/to_array.html

Chapter 10 | New STL elements

10.3 to_array

    Creates a std::array from the one dimensional built-in array a 
    Copying or moving multidimensional built-in array is not supported.

    we can use std::to_array in auto-mode, letting it deduce the type and the size

    For move-only types, in case we want to move the values of an existing array 
    into a std::array, we can use std::to_array as well.

**********/

#include <iostream>
#include <format>
#include <string>

void display(const auto & cont) {
    for(const auto & elem: cont) {
        std::cout << elem << ", ";
    }
    std::cout << '\n';
}

int main() {

    {
        const auto larr = std::to_array("Learning c++20 to_array");
        std::cout << "array size: " << larr.size() << '\n';
        display(larr);
    }

    {
        const char carr[] = {"Learning c++20 to_array"};
        const auto larr = std::to_array(carr);
        std::cout << "array size: " << larr.size() << '\n';
        display(larr);
    }

    {
        const auto larr = std::to_array({1, 2, 3, 4, 5});
        std::cout << "array size: " << larr.size() << '\n';
        display(larr);
    }

	return 0;
}

/*****
    END OF FILE
**********/

