/*****

References

    Effective Modern C++ | Scott Meyers
    https://en.cppreference.com/w/cpp/language/enum

Item 10: Prefer scoped enums to unscoped enums

unscoped enum
	C++98-style enums belong to the scope containing the enum, 
	and that means that nothing else in that scope may have the same name
	This kind of enum is called unscoped enum

	Enumerators for unscoped enums implicitly convert to integral types (and, from there, to floating-point types).

C++11 scoped enums:
	scoped enums, don’t leak names in this way
	Also referred as enum classes because scoped enums are declared via “enum class”
	There are no implicit conversions from enumerators in a scoped enum to any other type
	
Advantage of scoped enums:
	reduction in namespace pollution
	more strongly typed
	no implicit conversions
	scoped enums may be forward-declared

enum underlying type
	C++98
	To make efficient use of memory, compilers often want to choose the smallest underlying type for an enum 
	that’s sufficient to represent its range of enumerator values.
	To make that possible, C++98 supports only enum definitions (where all enumerators are listed); enum declarations are not allowed. 
	That makes it possible for compilers to select an underlying type for each enum prior to the enum being used.
	
	C++11
	the underlying type for a scoped enum is always known, and for unscoped enums, you can specify it.
	By default, the underlying type for scoped enums is int
		enum class Status;					// underlying type is int
	If the default doesn’t suit you, you can override it:
		enum class Status: std::uint32_t;	// underlying type is uint32_t
		
		
	You may also specify the underlying type for an unscoped enum, and the result may be forward-declared
		enum Color: std::uint8_t; // fwd decl for unscoped enum; underlying type is std::uint8_t

	Underlying type specifications can also go on an enum’s definition
	

use of unscoped enum
	when referring to fields within C++11’s std::tuples
	What makes this work is the implicit conversion to std::size_t, which is the type that std::get requires.
	The corresponding code with scoped enums is substantially more verbose:
	See example code
	
Summary:
    • C++98-style enums are now known as unscoped enums. Ther are visible to the scope containing the enum.
    • Enumerators of scoped enums are visible only within the enum.
    • Unscoped enums implicitly convert to underlying type. Scoped enums convert to other types only with a cast.
    • Both scoped and unscoped enums support specification of the underlying type. 
    • The default underlying type for scoped enums is int. Unscoped enums have no default underlying type.
    • Scoped enums may always be forward-declared. Unscoped enums may be forward-declared only if their declaration specifies an underlying type.

**********/

#include <iostream>
#include <cstdint>
#include <array>

enum Color98 {
    RED,
    GREEN,
    BLACK,
    YELLOW
};


enum class Color11 {
    RED,
    GREEN,
    BLACK
};

//auto    YELLOW     = 5; // error: 'auto YELLOW' redeclared as different kind of entity

enum class msg_type_11;     // underlying type is int
//enum class msg_type_11 : uint32_t;  // underlying type is uint32_t
void use_enum(msg_type_11 ) {  std::puts("use_enum(msg_type_11 )"); }

//enum msg_type_98;   // error: use of enum 'msg_type_98' without previous declaration

enum msg_type_98 : uint32_t;    // underlying type is uint32_t
void use_enum(msg_type_98 ) {  std::puts("use_enum(msg_type_98 )"); }

enum class msg_type_11 {
    GET,
    POST
};

enum msg_type_98 : uint32_t {
    GET,
    POST
};

enum data_size_t_98 {
    BUF_SIZE    = 256,
    ARR_SIZE    = 32
};

enum class data_size_t_11 {
    BUF_SIZE    = 256,
    ARR_SIZE    = 32
};

int main() {

    {   std::puts("=== using unscoped enum ===");
        auto    YELLOW     = 5;

        Color98 c1      = RED;
        int     ival    = GREEN;
        float   fval    = BLACK;
        
        //Color98 c2      = Color11::RED; // error: cannot convert 'Color11' to 'Color98' in initialization
    }

    {   std::puts("=== using scoped enum ===");
        Color11     c1  = Color11::RED;
        //Color11 c1      = RED;      // error: cannot convert 'Color98' to 'Color11' in initialization
        //int     ival    = Color11::GREEN;   // error: cannot convert 'Color11' to 'int' in initialization
        //float   fval    = Color11::BLACK;     // error: cannot convert 'Color11' to 'float' in initialization
        int     ival    = static_cast<int>(Color11::GREEN);
        float   fval    = static_cast<float>(Color11::BLACK);
    }

    {   std::puts("=== forward declaring enum ===");
        use_enum(msg_type_11::GET);
        use_enum(GET);
    }

    {   std::puts("=== use of implicit conversion of unscoped enum ===");
        std::array<int, ARR_SIZE>    larr1;
        //std::array<int, data_size_t_11::ARR_SIZE>    larr2; // error: could not convert 'data_size_t_11::ARR_SIZE' from 'data_size_t_11' to 'long unsigned int'
        std::array<int, static_cast<std::size_t>(data_size_t_11::ARR_SIZE)>    larr2;
    }

    return 0; 
}

/*****
    END OF FILE
**********/


