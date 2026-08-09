/*****

ep544_UB_Ranges_of_Enumerations_constexpr

References:
    episode     https://www.youtube.com/watch?v=AhMlBVnTYkE
    https://en.cppreference.com/cpp/language/enum
    https://eel.is/c++draft/dcl.enum#8

    code https://godbolt.org/z/YzqeeM6ds

    This example demonstrates about ranges of enums

    For an enumeration whose underlying type is fixed, 
    the values of the enumeration are the values of the underlying type.

    Otherwise, the values of the enumeration are the values representable by a 
    hypothetical integer type with minimal width M such that all enumerators 
    can be represented.
    The width of the smallest bit-field large enough to hold all the values of 
    the enumeration type is M. It is possible to define an enumeration that has 
    values not defined by any of its enumerators. 
    
    If the enumerator-list is empty, the values of the enumeration are as 
    if the enumeration had a single enumerator with value 0.

**********/

#include <climits>

consteval int c_style_enum() {

    enum Color { RED = 1, BLACK = 2 };

    [[maybe_unused]] Color cr{RED};
    [[maybe_unused]] Color cb{BLACK};

    { [[maybe_unused]] Color c{static_cast<Color>(0)}; }
    { [[maybe_unused]] Color c{static_cast<Color>(1)}; }
    { [[maybe_unused]] Color c{static_cast<Color>(2)}; }
    { [[maybe_unused]] Color c{static_cast<Color>(3)}; }

    {
        // gcc warning: the result of the conversion is unspecified because '4' is outside the range of type 'c_style_enum()::Color' [-Wconversion]
        // clang error: integer value 4 is outside the valid range of values [0, 3] for the enumeration type 'Color'
        
        //[[maybe_unused]] Color c{static_cast<Color>(4)};
    }

    static_assert(sizeof(Color) == 4);

    return sizeof(Color);
}

consteval int cpp_style_enum() {

    enum struct Color { RED = 1, BLACK = 2 };

    [[maybe_unused]] Color cr{Color::RED};
    [[maybe_unused]] Color cb{Color::BLACK};

    { [[maybe_unused]] Color c{static_cast<Color>(0)}; }
    { [[maybe_unused]] Color c{static_cast<Color>(1)}; }
    { [[maybe_unused]] Color c{static_cast<Color>(2)}; }
    { [[maybe_unused]] Color c{static_cast<Color>(3)}; }

    {
        // NO issue because underlying type is int
        [[maybe_unused]] Color c{static_cast<Color>(4)};
    }

    { [[maybe_unused]] Color c{3}; }
    { [[maybe_unused]] Color c{INT_MAX}; }
    {
        // gcc error: narrowing conversion of '4294967295' from 'unsigned int' to 'int' [-Wnarrowing]
        // clang error: constant expression evaluates to 4294967295 which cannot be narrowed to type 'Color' [-Wc++11-narrowing]
        // [[maybe_unused]] Color c{UINT_MAX}; 
    }
    
    static_assert(sizeof(int) == 4);
    static_assert(sizeof(Color) == 4);

    return sizeof(Color);
}

consteval int cpp_style_enum2() {

    enum struct Color : char { RED = 1, BLACK = 2 };

    [[maybe_unused]] Color cr{Color::RED};
    [[maybe_unused]] Color cb{Color::BLACK};

    { [[maybe_unused]] Color c{static_cast<Color>(0)}; }
    { [[maybe_unused]] Color c{static_cast<Color>(1)}; }

    { [[maybe_unused]] Color c{static_cast<Color>(127)}; }
    { [[maybe_unused]] Color c{static_cast<Color>(-128)}; }

    { 
        // gcc warning: the result of the conversion is unspecified because '128' is outside the range of type 'cpp_style_enum2()::Color' [-Wconversion]
        [[maybe_unused]] Color c{static_cast<Color>(128)}; 
    }

    { [[maybe_unused]] Color c{127}; }

    { 
        // gcc error: narrowing conversion of '128' from 'int' to 'char' [-Wnarrowing]
        // clang error: constant expression evaluates to 128 which cannot be narrowed to type 'Color' [-Wc++11-narrowing]
        // [[maybe_unused]] Color c{128}; 
    }

    static_assert(sizeof(char) == 1);
    static_assert(sizeof(Color) == 1);

    return sizeof(Color);
}

int main() {
    
    { [[maybe_unused]] constexpr int val = c_style_enum(); }
    { [[maybe_unused]] constexpr int val = cpp_style_enum(); }
    { [[maybe_unused]] constexpr int val = cpp_style_enum2(); }

    return 0;
}

/*****
    END OF FILE
**********/
