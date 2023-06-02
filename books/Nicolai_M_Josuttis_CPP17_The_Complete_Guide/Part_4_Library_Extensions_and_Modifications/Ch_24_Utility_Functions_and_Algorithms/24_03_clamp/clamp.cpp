/**********

References

    C++17 - The Complete Guide | Nicolai M. Josuttis
    https://en.cppreference.com/w/cpp/algorithm/clamp

Chapter 24 Other Utility Functions and Algorithms
	C++17 provides a couple of new utility functions and algorithms

24.3 clamp()
    enables to “clamp” a value between a passed minimum and maximum value
    return value is a const references to one of the passed arguments
    clamp(i, 5, 13) has the same effect as calling std::min(std::max(i, 5), 13)

    requires that all arguments, which are passed by const reference, have the same type T
    to pass arguments of different type, you can explicitly specify the template parameter T
    can also pass floating-point values provided they don’t have the value NaN

    you can pass a predicate as comparison operation
    no overload of clamp() taking an initializer list of values (as min() and max() have)

*************/

#include <iostream>
#include <algorithm>
#include <vector>

int main() {
    const int     cmin = 3, cmax = 12;
    std::cout << "=== std::clamp() ===\n";
    std::vector     lvec{-9, -5, -4, -2, -1, 0, 3, 5, 8, 2, 7, 13, 18};
    for(const auto & elem : lvec) {
        std::cout << "min " << cmin << ", max " << cmax << 
            ", element value " << elem << 
            ", clamp value " << std::clamp(elem, cmin, cmax) << '\n';
    }
    std::cout << '\n';

    std::cout << "=== predicate as comparison operation ===\n";
    for(const auto & elem : lvec) {
        std::cout << "min " << cmin << ", max " << cmax << 
            ", element value " << elem << 
            ", clamp value " << 
            std::clamp(elem, cmin, cmax, [](const auto v1, const auto v2){ 
                return std::abs(v1) < std::abs(v2);
                }) << '\n';
    }
    std::cout << '\n';

    std::cout << "=== different types of arguments to clamp ===\n";
    double  dval = 5.6;
            std::cout << "min " << cmin << ", max " << cmax << 
            ", element value " << dval << 
            ", clamp value " << std::clamp<double>(dval, cmin, cmax) << '\n';

    return 0;
}

/**********
    END OF FILE
*************/


