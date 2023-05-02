/**********

    This example demonstrates about std library std::valarray

    std::valarray is the class for representing and manipulating arrays of values.
    It supports element-wise mathematical operations and various forms of generalized subscript operators, slicing and indirect access

    For more info visit:
    C++ Weekly - Ep 367: https://www.youtube.com/watch?v=hxcrOwfPhkE&t=450s
    https://en.cppreference.com/w/cpp/numeric/valarray

**************/

#include <iostream>
#include <valarray>

void display(const std::valarray<int> & varr) {
    for(const auto & elem : varr) {
        std::cout << elem << ' ';
    }
    std::cout << '\n';
}

int main() {
    std::valarray<int> varr_int{1,2,3,4,5,6,7,8,9,10};
    display(varr_int);

    auto res_varr1 = varr_int + 3;
    display(varr_int);
    display(res_varr1);

    varr_int += 4;
    display(varr_int);

    std::cout << "varr_int.size() " << varr_int.size() << '\n';
    std::cout << "varr_int.min() " << varr_int.min() << '\n';
    std::cout << "varr_int.max() " << varr_int.max() << '\n';

    auto res_varr2 = varr_int.apply([](int n){ return n*n;});
    display(res_varr2);

    auto res_varr3 = varr_int.apply([](const int & n){ return n*n*n;});
    display(res_varr3);

    return 0;
}

/*****
    END OF FILE
********/


