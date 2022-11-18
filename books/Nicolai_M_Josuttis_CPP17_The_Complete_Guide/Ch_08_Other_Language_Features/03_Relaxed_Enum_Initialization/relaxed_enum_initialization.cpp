/************
References:
	C++17 - The Complete Guide | Nicolai M. Josuttis

3. Relaxed Enum Initialization from Integral Values
    for unscoped enumerations with a specified type | for enumerations with a fixed underlying type, since C++17 you can use an integral value of that type for direct list initialization
    for all scoped enumerations, because they always have an underlying default type
    list initialization still doesn’t allow narrowing
    std::byte, which directly uses this feature
    This feature was motivated to support the trick of defining new integral types

*************/

#include <iostream>
#include <cassert>

// 3. Relaxed Enum Initialization from Integral Values
enum UnscopedEnum_WithoutType {RED, GREEN, BLACK};
enum UnscopedEnum_WithType : char {BLUE, YELLOW, PINK};

enum class ScopedEnum_WithoutType {RED, GREEN, BLACK};
enum class ScopedEnum_WithType : uint8_t {RED, GREEN, BLACK};

enum class myInt_t : uint8_t { };
std::ostream & operator<< (std::ostream & os, const myInt_t mi) {
    return os << static_cast<uint32_t>(mi);
}


int main() {

    // 3. Relaxed Enum Initialization from Integral Values
    [[maybe_unused]] UnscopedEnum_WithoutType ue1{RED};
    //[[maybe_unused]] UnscopedEnum_WithoutType ue2{2}; // error: invalid conversion from 'int' to 'UnscopedEnum_WithoutType'

    [[maybe_unused]] UnscopedEnum_WithType uewt1{BLUE};
    assert(uewt1 == BLUE); 
    assert(uewt1 == 0);
    [[maybe_unused]] UnscopedEnum_WithType uewt2{2};
    assert(uewt2 == PINK);
    assert(uewt2 == 2);
    [[maybe_unused]] UnscopedEnum_WithType uewt3{'A'};
    [[maybe_unused]] UnscopedEnum_WithType uewt4{5};
    //[[maybe_unused]] UnscopedEnum_WithType uewt5(5); // error: invalid conversion from 'int' to 'UnscopedEnum_WithType'
    //[[maybe_unused]] UnscopedEnum_WithType uewt5 = 5; // error: invalid conversion from 'int' to 'UnscopedEnum_WithType'
    //[[maybe_unused]] UnscopedEnum_WithType uewt5 = {5}; // error: invalid conversion from 'int' to 'UnscopedEnum_WithType'
    //[[maybe_unused]] UnscopedEnum_WithType uewt6{6.2}; // error: narrowing conversion of '5.2000000000000002e+0' from 'double' to 'char'
    
    
    [[maybe_unused]] ScopedEnum_WithoutType se1{ScopedEnum_WithoutType::RED};
    [[maybe_unused]] ScopedEnum_WithoutType se2{2};
    [[maybe_unused]] ScopedEnum_WithoutType se3{7};

    [[maybe_unused]] ScopedEnum_WithType sewt1{ScopedEnum_WithType::RED};
    [[maybe_unused]] ScopedEnum_WithType sewt2{2};
    [[maybe_unused]] ScopedEnum_WithType sewt3{7};

    myInt_t mi{5};
    std::clog << mi << '\n';

    return 0;
}

/***************
    END OF FILE
*****************/
