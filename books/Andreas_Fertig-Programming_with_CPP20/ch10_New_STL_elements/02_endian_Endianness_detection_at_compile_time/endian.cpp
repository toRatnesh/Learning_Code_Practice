/*****

References

    Programming with C++20 | Andreas Fertig
    https://en.cppreference.com/w/cpp/types/endian.html

Chapter 10 | New STL elements

10.2 endian: Endianness detection at compile time

    enum class endian   (since C++20)
    {
        little = , // implementation-defined
        big    = , // implementation-defined
        native = , // implementation-defined
    };


    Indicates the endianness of all scalar types:
        If all scalar types are little-endian, std::endian::native equals std::endian::little. 
        If all scalar types are big-endian, std::endian::native equals std::endian::big.

**********/

#include <bit>
#include <format>
#include <iostream>

// Reference: https://github.com/andreasfertig/programming-with-cpp20/blob/main/10.03-byteSwap0/main.cpp
constexpr auto change_byte_order_helper(std::integral auto value)
{
  return [&]<size_t... I>(std::index_sequence<I...>) -> decltype(value) {
    return (
      (((value >> I * 8) & 0xff) << ((8 * sizeof(value)) - ((1 + I) * 8))) |
      ...);
  }(std::make_index_sequence<sizeof(value)>{});
}

// conert to n/w byte order(big endian)
constexpr auto change_byte_order(std::integral auto const value) {
    if constexpr ((std::endian::native == std::endian::big) ||
                  (sizeof(value) == 1)) {
        
        return value;

    } else {
        return change_byte_order_helper(value);
    }
}

int main() {
    if constexpr (std::endian::native == std::endian::little) {
        std::cout << "host is little endian\n";
    } else if constexpr (std::endian::native == std::endian::big) {
        std::cout << "host is big endian\n";
    } else {
        std::cout << "host is mix endian\n";
    }

    constexpr auto value = 5;
    constexpr auto nw_value = change_byte_order(value);
    std::cout << "Value: " << value << " after changing byte order: " << nw_value << '\n';

    constexpr auto h_value = change_byte_order(nw_value);
    std::cout << "Value: " << nw_value << " after changing byte order: " << h_value << '\n';

    return 0;
}

/*****
    END OF FILE
**********/
