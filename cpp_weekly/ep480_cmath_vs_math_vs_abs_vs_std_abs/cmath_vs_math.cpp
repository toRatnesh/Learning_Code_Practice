/*****

References
    episode https://www.youtube.com/watch?v=0kciYs-sK6M
    https://en.cppreference.com/w/cpp/numeric/math/fabs
    https://en.cppreference.com/w/c/numeric/math/fabs

std::abs vs abs


Best Practice
    Qualify all of your std c lib function with std::

**********/

#include <iostream>
#include <iomanip>

#ifdef USE_CMATH
    #include <cmath>
#else 
    #include <math.h>
#endif

int main() {

    auto val = -3.1265506288320943;


    std::cout << std::setprecision(20) << std::abs(val) << '\n';

    // Warning in  case we use cmath
    // warning: using integer absolute value function 'abs' when argument is of floating point type
    std::cout << std::setprecision(20) << abs(val) << '\n';

    return 0;
}

/*****
    END OF FILE
**********/


