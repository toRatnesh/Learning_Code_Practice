/*******

References
    C++17 - The Complete Guide | Nicolai M. Josuttis
    https://en.cppreference.com/w/cpp/types/byte

Chapter 18 std::byte
    std::byte represent the “natural” type of the elements of memory, bytes
    Only bit-wise operators are supported for std::byte
    std::byte is define as enumeration type with unsigned char as the underlying type

18.2 std::byte Types and Operations

18.2.1 std::byte Types

    enum class byte : unsigned char { };
    std::byte is define as enumeration type with unsigned char as the underlying type
    that's why size of a std::byte is always 1

    number of bits depends on the number of bits of type unsigned char
    Most of the time it’s 8, but there are platforms where this is not the case

18.2.2 std::byte Operations

    ---------------------------------------------------------------
    Operation               Effect
    ---------------------------------------------------------------
    constructors            Create a byte object (value undefined with default constructor)
    destructor              Destroys a byte object (nothing to be done)
    =                       Assign a new value
    ==, !=, <, <=, >, >=    Compares byte objects
    <<, >>, |, &, ^, ~      Binary bit-operations
    <<=, >>=, |=, &=, ^=    Modifying bit-operations
    to_integer<T>()         Converts byte object to integral type T
    sizeof()                Yields 1
    ---------------------------------------------------------------

    Conversion to Integral Types
        to_integer<>()  convert a std::byte to any fundamental integral type (bool, a character type, or an integer type)
        to_integer<>() uses the rules for static casts from an unsigned char to the destination type

    I/O with std::byte
        no input and output operators defined for std::byte, so that you have to convert them to an integral value
        By using a std::bitset<>, you can also output the value as binary value (a sequence of bits)
        read the value as an integral, string or bitset value and convert it

***********/

#include <iostream>
#include <cstddef>
#include <limits>
#include <bitset>
#include <sstream>
#include <exception>

std::istream & operator>>(std::istream & is, std::byte & bval) {
    
    std::bitset<std::numeric_limits<unsigned char>::digits> bsval;
    is >> bsval;

    if(! is.fail()) {
        bval = static_cast<std::byte>(bsval.to_ulong());
    }
    else {
        throw std::runtime_error("Failure in getting data from input stream");
    }
    return is;
}

int main() {

    std::cout << "=== std::to_integer<> ===\n";
    // to_integer<>() uses the rules for static casts from an unsigned char to the destination type
    constexpr std::byte hex_b{0xFF};

    static_assert(255 == std::to_integer<unsigned int>(hex_b));
    static_assert(255 == std::to_integer<int>(hex_b));
    static_assert(-1 == std::to_integer<signed char>(hex_b));
    static_assert(-1 == static_cast<int>(std::to_integer<signed char>(hex_b)));

    // no input and output operators defined for std::byte, so that you have to convert them to an integral value
    std::cout << "std::to_integer<unsigned int>(hex_b):  " << std::to_integer<unsigned int>(hex_b) << '\n';
    std::cout << "std::to_integer<int>(hex_b):   " << std::to_integer<int>(hex_b) << '\n';
    std::cout << "std::to_integer<signed char>(hex_b):   " << std::to_integer<signed char>(hex_b) << '\n';
    std::cout << "static_cast<int>(std::to_integer<signed char>(hex_b)): " << static_cast<int>(std::to_integer<signed char>(hex_b)) << '\n';

    // By using a std::bitset<>, you can also output the value as binary value (a sequence of bits)
    using byte_bitset_t = std::bitset<std::numeric_limits<unsigned char>::digits>;
    std::cout << byte_bitset_t{std::to_integer<unsigned char>(hex_b)} << '\n';

    const std::string str = byte_bitset_t{std::to_integer<unsigned char>(hex_b)}.to_string();
    std::cout << "byte_bitset_t{std::to_integer<unsigned char>(hex_b)}.to_string():  " << str << '\n';

    constexpr std::byte bval{0x0F};
    static_assert(15 == std::to_integer<unsigned int>(bval));
    static_assert(240 == std::to_integer<unsigned int>(~bval));
    static_assert(3 == std::to_integer<unsigned int>(bval >> 2));
    static_assert(60 == std::to_integer<unsigned int>(bval << 2));

    std::cout << "std::to_integer<unsigned int>(bval):  " << std::to_integer<unsigned int>(bval) << '\n';
    std::cout << "std::to_integer<unsigned int>(~bval):  " << std::to_integer<unsigned int>(~bval) << '\n';
    std::cout << "std::to_integer<unsigned int>(bval >> 2):  " << std::to_integer<unsigned int>(bval >> 2) << '\n';
    std::cout << "std::to_integer<unsigned int>(bval << 2):  " << std::to_integer<unsigned int>(bval << 2) << '\n';

    std::cout << "\n=== I/O with std::byte ===\n";
    std::stringstream   ss{"01111101"};
    std::byte           bval2;
    try {
        ss >> bval2;
    }
    catch(const std::exception & exp) {
        std::cout << "Exception " << exp.what() << '\n';
    }
    std::cout << "std::to_integer<unsigned int>(bval2):  " << std::to_integer<unsigned int>(bval2) << '\n';

    return 0;
}

/*******
    END OF FILE
***********/


