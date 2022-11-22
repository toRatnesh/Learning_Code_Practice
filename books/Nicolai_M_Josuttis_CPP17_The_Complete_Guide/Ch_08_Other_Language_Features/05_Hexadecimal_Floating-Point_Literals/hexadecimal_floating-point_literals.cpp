/************
References:
	C++17 - The Complete Guide | Nicolai M. Josuttis

5. Hexadecimal Floating-Point Literals
    useful when an exact floating-point representation is desired 
    (for decimal floating-point values there is no general guarantee that the exact value exists)

    support for hexadecimal floating-point notation already existed for 
    output streams using the std::hexfloat manipulator (available since C++11).

*************/

#include <iostream>
#include <iomanip>
#include <vector>

int main() {

    std::vector<double> dvec{
        0xA,    // 10
        10e0,   // 10 (10^0)    = 10
        0xAp1,  // 10 (2^1)     = 20
        10e1,   // 10 (10^1)    = 100
        0xAp2,  // 10 (2^2)     = 40
        10e2,   // 10 (10^2)    = 1000
        0xAp-2, // 10 (2 ^ -2)  = 10 (1/ 4)     = 2.5
        10e-2   // 10 (10 ^ -2) = 10 (1/100)    = 0.1
    };

    for(auto d : dvec) {
        std::clog << "dec: " << std::setw(6) << std::defaultfloat << d << " hex: " << std::hexfloat << d << '\n';
    }

    return 0;
}

/***************
    END OF FILE
*****************/
