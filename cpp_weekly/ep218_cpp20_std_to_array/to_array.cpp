/**************
 *	This example demonstrates the use of c++20 to_array() function.
 *
 *	std::to_array
 *	Creates a std::array from the one dimensional built-in array a. The elements of the std::array are copy-initialized from the corresponding element of a. Copying or moving multidimensional built-in array is not supported.
 *
 *	For more info visit:
 *	https://en.cppreference.com/w/cpp/container/array/to_array
 *
 *	EXAMPLE IS COPIED FROM: https://en.cppreference.com/w/cpp/container/array/to_array
 *
 * ****************/

#include <type_traits>
#include <utility>
#include <array>
#include <memory>

int main()
{
	// copies a string literal
	auto a1 = std::to_array("foo");
	static_assert(a1.size() == 4);

	// deduces both element type and length
	auto a2 = std::to_array({ 0, 2, 1, 3 });
	static_assert(std::is_same_v<decltype(a2), std::array<int, 4>>);

	// deduces length with element type specified
	// implicit conversion happens
	auto a3 = std::to_array<long>({ 0, 1, 3 });
	static_assert(std::is_same_v<decltype(a3), std::array<long, 3>>);

	auto a4 = std::to_array<std::pair<int, float>>(
			{ { 3, .0f }, { 4, .1f }, { 4, .1e23f } });
	static_assert(a4.size() == 3);

	// creates a non-copyable std::array
	auto a5 = std::to_array({ std::make_unique<int>(3) });
	static_assert(a5.size() == 1);

	// error: copying multidimensional arrays is not supported
	// char s[2][6] = { "nice", "thing" };
	// auto a6 = std::to_array(s);

	return 0;
}

/********
 *	END OF FILE
 * ********/
