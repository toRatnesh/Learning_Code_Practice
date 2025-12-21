/*****

References

    Programming with C++20 | Andreas Fertig
    https://en.cppreference.com/w/cpp/numeric/bit_cast.html

Chapter 10 | New STL elements

10.1 bit_cast: Reinterpreting your objects

    bit_cast is used to bitwise cast from one type to another
    .   various checks are performed to ensure that the conversion is valid
    .   The two types need to have the same size, they also need to be trivially copyable
    .   bit_cast doesn’t do any kind of rounding
    .   STL bit_cast is constexpr should the two types and their subobjects have:
        ■ no union
        ■ no a pointer or member-pointer
        ■ no volatile
        ■ no non-static data members that are references

**********/

#include <bit>
#include <format>
#include <iostream>
#include <cstring>

int main() {
    
    {
        std::cout << "=== using bit_cast ===\n";
        const float fval{6.25f};
        const int ival = std::bit_cast<int>(fval);
        std::cout << "float value: " << fval << ", its std::bit_cast to int value is: " << ival << '\n';
    }

    {
        std::cout << "=== using memcpy ===\n";
        const float fval{6.25f};
        int ival{0};
        memcpy(&ival, &fval, sizeof(ival));
        std::cout << "float value: " << fval << ", its std::bit_cast to int value is: " << ival << '\n';
    }

    return 0;
}

/*****
    END OF FILE
**********/
