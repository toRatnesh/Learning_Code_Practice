/*****

References
    episode https://www.youtube.com/watch?v=8-_6-nJGzNo
    https://cppreference.com/cpp/language/template_parameters#Non-type_template_parameter

    code https://godbolt.org/z/doG7dxs11

    since c++ 20 a floating-point type is considered as structural type for NTTP

**********/

#include <iostream>


template<double PI = 3.14, typename T>
void display(T radius) {
    std::cout << "pi " << PI << ", radius: " << radius << '\n';
}

int main() {

    display<>(5);
    display<3.1415>(6);

    display<+0.0>(8);
    display<-0.0>(9);

    return 0;
}

/*****
    END OF FILE
**********/

