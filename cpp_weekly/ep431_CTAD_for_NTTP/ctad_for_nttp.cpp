/*****

ep431_CTAD_for_NTTP

References
episode https://www.youtube.com/watch?v=yPB_btV8epo
https://en.cppreference.com/w/cpp/language/template_parameters

**********/

#include <iostream>
#include <array>

template<std::array arr>
void display_array() {
    for(const auto & elem : arr) {
        std::cout << elem << ' ';
    }
    std::cout << '\n';
}

int main() {

    // CTAD
    constexpr std::array  iarr{1, 2, 3, 4};           // CTAD std::array<int, 4>
    constexpr std::array  darr{1.2, 2.3, 3.4, 4.5};   // CTAD std::array<double, 4>
    //darr = iarr;  CE error: no match for 'operator=' (operand types are 'std::array<double, 4>' and 'std::array<int, 4>')


    // CTAD FOR NTTP
    display_array<iarr>();
    display_array<darr>();

    display_array<{11, 12, 13}>();
    display_array<{2.4, 3.6, 4.8, 5.10}>();

    return 0;
}

/*****
    END OF FILE
**********/


