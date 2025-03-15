/*****

References
    episode https://www.youtube.com/watch?v=reWnel5uLS4
    https://en.cppreference.com/w/cpp/numeric/math

    This episode demonstrates about constexpr math functions

**********/

#include <iostream>
#include <cmath>

int main() {
    
    constexpr float f1 = 5.2f;
    constexpr float f2 = 5.2f;
    constexpr float f3 = 5.3f;
    static_assert(std::fmaxf(f1, f2) == f2);
    static_assert(std::fmaxf(f1, f2) == f1);
    static_assert(std::fmaxf(f1, f3) == f3);

    return 0;
}

/*****
    END OF FILE
**********/


