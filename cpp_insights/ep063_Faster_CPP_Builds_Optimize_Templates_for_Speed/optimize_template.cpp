/*****

References

	episode https://www.youtube.com/watch?v=xQy9oBRJw1g

    code https://cppinsights.io/s/86e60dc7
    code https://godbolt.org/z/q5h9v36zd

    if we have return type as auto in the function template and we use it in unevaluated context 
    template function is instantiated to find out the return type

    execute this code in cppinsights to check instantiation 

**********/

#include <iostream>

int funi(int val) {
    std::cout << "inside " << __func__ << '\n';
    return val;
}

template<typename T>
auto funt_auto(T val) {
    std::cout << "inside " << __func__ << '\n';
    return val;
}

template<typename T>
T funt_T(T val) {
    std::cout << "inside " << __func__ << '\n';
    return val;
}

int main() {

    std::cout << sizeof(funi(3)) << '\n';
    std::cout << sizeof(funt_auto(3)) << '\n';
    std::cout << sizeof(funt_T(3)) << '\n';

    return 0;
}

/*****
    END OF FILE
**********/

