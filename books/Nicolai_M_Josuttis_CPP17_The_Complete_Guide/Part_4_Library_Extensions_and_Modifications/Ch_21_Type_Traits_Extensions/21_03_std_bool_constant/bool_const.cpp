/**********

References

    C++17 - The Complete Guide | Nicolai M. Josuttis
    https://en.cppreference.com/w/cpp/header/type_traits

Chapter 21 Type Traits Extensions

C++17 extends the general abilities to use type traits (standard type functions) 
and introduces some new type traits

21.3 std::bool_constant<>

	Before C++17, 
	std::true_type	for std::integral_constant<bool,true> and 
	std::false_type	for std::integral_constant<bool,false> were directly defined as alias definitions

	Since C++17, If traits yield Boolean values, they use the alias template bool_constant<>:
	namespace std {
		template<bool B>
		using bool_constant	= integral_constant<bool, B>; // since C++17
		using true_type		= bool_constant<true>;
		using false_type	= bool_constant<false>;
	}


	define your own type trait by deriving from bool_constant<> 
	if you are able to formulate the corresponding compile-time expression as Boolean condition
	
	Example-1	to check size larger than int
	template<typename T>
	struct IsLargerThanInt : std::bool_constant<(sizeof(T) > sizeof(int))> { };
	
	Example-2	to checks whether the move constructor for a type T guarantees not to throw roughly as
	template<typename T>
	struct IsNothrowMoveConstructibleT : std::bool_constant<noexcept(T(std::declval<T>()))> { };

****************/

#include <iostream>
#include <type_traits>
#include <iomanip>

template<typename T>
struct is_largerthan_int : std::bool_constant<(sizeof(T) > sizeof(int))> { };

template<typename T>
inline static constexpr auto is_largerthan_int_v = is_largerthan_int<T>::value;

struct S1 {
    double dval;
};

struct S2 {
    short sival;
};

class S_MoveThrow {
    public:
    S_MoveThrow(S_MoveThrow &&);
};
S_MoveThrow::S_MoveThrow(S_MoveThrow &&) = default;

class S_MoveNoThrow {
    public:
    S_MoveNoThrow(S_MoveNoThrow &&) noexcept = default;
};

template<typename T>
struct is_nothrow_move_construct : std::bool_constant<noexcept(T(std::declval<T>()))> { };

template<typename T>
inline static constexpr auto is_nothrow_move_construct_v = is_nothrow_move_construct<T>::value;

int main() {
    {
    std::cout << "=== std::bool_constant<> ===\n";
    std::cout << "std::bool_constant<true>::value: " << std::boolalpha << std::bool_constant<true>::value << '\n';
    std::cout << "std::bool_constant<false>::value: " << std::boolalpha << std::bool_constant<false>::value << '\n';
    }

    {
    std::cout << "\n=== deriving from std::bool_constant<> ===\n";
    std::cout << "is_largerthan_int_v<S1>: " << is_largerthan_int_v<S1> << '\n';
    std::cout << "is_largerthan_int_v<S2>: " << is_largerthan_int_v<S2> << '\n';

    if constexpr(is_largerthan_int_v<S1>) {
        std::cout << "S1 is larger than int\n";
    } else {
        std::cout << "S1 is smaller than int\n";
    }

    if constexpr(is_largerthan_int_v<S2>) {
        std::cout << "S2 is larger than int\n";
    } else {
        std::cout << "S2 is smaller than int\n";
    }
    }

    {
    std::cout << "is_nothrow_move_construct_v<S_MoveThrow>: " << is_nothrow_move_construct_v<S_MoveThrow> << '\n';
    std::cout << "is_nothrow_move_construct_v<S_MoveNoThrow>: " << is_nothrow_move_construct_v<S_MoveNoThrow> << '\n';
    }

    return 0;
}

/**********
    END OF FILE
****************/


