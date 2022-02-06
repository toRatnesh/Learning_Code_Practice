/***************
	This example demonstrates the use of c++23 'Consteval if'

	For more info visit:
	https://en.cppreference.com/w/cpp/language/if#Consteval_if
	Episode video:	https://www.youtube.com/watch?v=_xvAmEbK1vE&list=PLs3KjaCtOwSZ2tbuV1hx8Xz-rFZTan2J1&index=306

**********************/

#include <cassert>
#include <type_traits>

constexpr auto do_constexpr(auto val) {
	// c++17
	// if constexpr is used to make a compile time choice
	// in a metaprogramming sense, between multiple options
	if constexpr (std::is_integral_v<decltype(val)>) {
		return 1;
	}
	else {
		return 1.5;
	}
}

constexpr auto do_is_constant_evaluated() {
	if(std::is_constant_evaluated()) {
		return 2;
	}
	else {
		return 3;
	}
}

constexpr auto do_consteval() {
	if !consteval {
		return 4;
	}
	else {
		return 5;
	}
}

int main() {
	static_assert(1 == do_constexpr(5));
	static_assert(1.5 == do_constexpr(5.3));

	auto res1 = do_is_constant_evaluated();
	assert(3 == res1);
	const auto res2 = do_is_constant_evaluated();
	static_assert(2 == res2);
	constexpr auto res3 = do_is_constant_evaluated();
	static_assert(2 == res3);

	auto res4 = do_consteval();
	assert(4 == res4);
	const auto res5 = do_consteval();
	static_assert(5 == res5);
	constexpr auto res6 = do_consteval();
	static_assert(5 == res6);

	return 0;
}

/*******
	END OF FILE
******/
