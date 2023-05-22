/*******

References
    C++17 - The Complete Guide | Nicolai M. Josuttis
    https://en.cppreference.com/w/cpp/types/byte

Chapter 18 std::byte
    std::byte represent the “natural” type of the elements of memory, bytes
    Only bit-wise operators are supported for std::byte
    std::byte is define as enumeration type with unsigned char as the underlying type

18.1 Using std::byte

    * list initialization (using curly braces) is the only way you can directly initialize a single value of a std::byte object
    * no implicit conversion
    * value of an uninitialized std::byte is undefined
    * force an initialization with all bits set to zero with list initialization
    * std::to_integer<>() provides the ability to use the byte object as integral value (including bool and char).
    * size of a std::byte is always 1 (size of underlying unsigned char)
    * number of bits depends on the number of bits of type unsigned char, Most of the time it’s 8, but there are platforms where this is not the case.

***********/

#include <iostream>
#include <cstddef>
#include <limits>

int main() {

    // list initialization (using curly braces) is the only way you can directly initialize a single value of a std::byte object
    /* // CE error: cannot convert 'int' to 'std::byte' in initialization
    std::byte b1 = 3;   
    std::byte b1 = {3};
    std::byte b1(3);
    */

    constexpr std::byte b1{3};
    constexpr std::byte b2{0b0001'0010};

    static_assert(3 == std::to_integer<int>(b1));
    static_assert(18 == std::to_integer<int>(b2));

    static_assert(1 == sizeof(b1));
    static_assert(1 == sizeof(b2));

    // no implicit conversion
    //std::byte barr[] {1, 5};    // error: cannot convert 'int' to 'std::byte' in initialization
    constexpr std::byte barr[] {std::byte{1}, std::byte{5}};
    static_assert(2 == sizeof(barr));

    // value of an uninitialized std::byte is undefined
    //constexpr std::byte b_uninitialized_undefined; // error: uninitialized 'const b_uninitialized_undefined'
    std::byte b_uninitialized_undefined;
    std::cout << std::to_integer<int>(b_uninitialized_undefined) << '\n';

    // force an initialization with all bits set to zero with list initialization
    constexpr std::byte zero_initialized{};   // same as zero_initialized{0};
    static_assert(0 == std::to_integer<int>(zero_initialized));

    // std::to_integer<>() provides the ability to use the byte object as integral value (including bool and char)
    constexpr std::byte bval{0b0110'0001};
    static_assert(97 == std::to_integer<int>(bval));
    static_assert('a' == std::to_integer<char>(bval));
    static_assert(true == std::to_integer<bool>(bval));

    std::cout << "std::to_integer<int>(bval)    " << std::to_integer<int>(bval) << '\n';
    std::cout << "std::to_integer<char>(bval)   " << std::to_integer<char>(bval) << '\n';
    std::cout << "std::to_integer<bool>(bval)   " << std::boolalpha << std::to_integer<bool>(bval) << '\n';

    // number of bits depends on the number of bits of type unsigned char, Most of the time it’s 8, but there are platforms where this is not the case.
    std::cout << "std::numeric_limits<unsigned char>::digits    " << std::numeric_limits<unsigned char>::digits << '\n';
    std::cout << "std::numeric_limits<std::byte>::digits    " << std::numeric_limits<std::byte>::digits << '\n';

    std::cout << "\n=== std::byte passed to generic lambda ===\n";
    auto display = [](const auto & bytval){ 
        std::cout << "std::to_integer<int>(bytval): " << std::to_integer<int>(bytval) << '\n';
    };
    display(bval);

    return 0;
}

/*******
    END OF FILE
***********/



