/******

    This example demonstrtes about C++17 Class Template Argument Deduction (CTAD)

    For more info visit:
    C++17 - The Complete Guide | Chapter 9 Class Template Argument Deduction
    https://github.com/socialratnesh/Learning_Code_Practice/tree/main/books/Nicolai_M_Josuttis_CPP17_The_Complete_Guide

*********/

#include <iostream>
#include <vector>

template<typename T>
class S {
    public:
    S(T, T) {}
};

int main() {
    S<int>  s1(2, 3);
    S       s2(2, 3);

    std::vector<int>    v1{1,2,3,4,5};
    std::vector         v2{1,2,3,4,5};

    return 0;
}

/*********
    END OF FILE
**********/


