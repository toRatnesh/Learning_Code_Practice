/***************
  This example demonstrates about C++20 template parameter list

  For more info visit:
https://www.youtube.com/watch?v=MbvBK6QsDgw
https://en.cppreference.com/w/cpp/language/lambda
 **************/

#include <iostream>

int main () {
	// generic lambda
	auto gl_max = [](const auto v1, const auto v2) {
		return (v1 > v2) ? v1 : v2;
	};

	// c++20 template lambda
	auto tl_max = []<typename T>(T v1, T v2) {
		return (v1 > v2) ? v1 : v2;
	};

	// another version of generic lambda also using template
	auto gtl_max = []<typename T>(T v1, const auto v2) {
		return (v1 > v2) ? v1 : v2;
	};

	static_assert(3 == gl_max(3,2));
	static_assert(3 == gl_max(2,3));
	static_assert(3.5 == gl_max(2,3.5));
	static_assert(3.5 == gl_max(3.5,2));
	static_assert(3.5 == gl_max(3.5,3.5));
	static_assert(3.5001 == gl_max(3.5001,3.5));
	static_assert(3.5001 == gl_max(3.5,3.5001));

	static_assert(3 == tl_max(3,2));
	static_assert(3 == tl_max(2,3));
	//static_assert(3.5 == tl_max(2,3.5));  // cannot call with tl_max with different types
	//static_assert(3.5 == tl_max(3.5,2));  // cannot call with tl_max with different types
	static_assert(3.5 == tl_max(3.5,3.5));
	static_assert(3.5001 == tl_max(3.5001,3.5));
	static_assert(3.5001 == tl_max(3.5,3.5001));

	static_assert(3 == gtl_max(3,2));
	static_assert(3 == gtl_max(2,3));
	static_assert(3.5 == gtl_max(2,3.5));
	static_assert(3.5 == gtl_max(3.5,2));
	static_assert(3.5 == gtl_max(3.5,3.5));
	static_assert(3.5001 == gtl_max(3.5001,3.5));
	static_assert(3.5001 == gtl_max(3.5,3.5001));

	return 0;
}

/*****
  END OF FILE
 ****/
