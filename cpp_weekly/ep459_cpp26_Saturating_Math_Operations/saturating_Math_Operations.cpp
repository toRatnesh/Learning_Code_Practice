/*****

References

    episode https://www.youtube.com/watch?v=XNMnQOFrEIY
    Saturation arithmetic (since C++26) https://en.cppreference.com/w/cpp/numeric
    saturate_cast https://en.cppreference.com/w/cpp/numeric/saturate_cast

    Saturation arithmetic
        This operation (unlike built-in arithmetic operations on integers) behaves as-if it is a mathematical operation with an infinite range. Let q denote the result of such operation. Returns:
        ->	q, if q is representable as a value of type T. Otherwise,
        ->	the largest or smallest value of type T, whichever is closer to the q.
        This overload participates in overload resolution only if T is an integer type.

    std::saturate_cast
        Converts the value x to a value of type T, clamping x between the minimum and maximum values of type T.
        The program is ill-formed if either T or U is not a signed or unsigned integer type (including standard integer type and extended integer type).

**********/

#include <iostream>
#include <string>
#include <numeric>
#include <cstdint>

int main() {

    constexpr uint8_t val = 140;
    static_assert(std::add_sat(val, val) == 255);

    constexpr int ival = 123'456'789;
    static_assert(std::saturate_cast<int8_t>(ival) == 127);
    static_assert(std::saturate_cast<uint8_t>(ival) == 255);

    static_assert(std::saturate_cast<int16_t>(ival) == 32'767);
    static_assert(std::saturate_cast<uint16_t>(ival) == 65'535);

    static_assert(std::saturate_cast<int32_t>(ival) == 123'456'789);
    static_assert(std::saturate_cast<uint32_t>(ival) == 123'456'789);

    return 0;
}

/*****
    END OF FILE
**********/

