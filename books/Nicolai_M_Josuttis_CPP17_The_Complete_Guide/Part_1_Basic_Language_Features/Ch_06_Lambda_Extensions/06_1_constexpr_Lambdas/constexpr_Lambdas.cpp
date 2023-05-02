/************

References:
	C++17 - The Complete Guide | Nicolai M. Josuttis

Lambda
	C++11   Lambda
	C++14   Generic lambdas
	C++17   In constant expression
	In places where you need a copy of the current object

	1. constexpr Lambdas
		Since C++17, lambdas are implicitly constexpr provided the features it uses are valid for compile-time contexts 
		(e.g., only literal types, no static variables, no virtual, no try/catch, no new/delete).
		Declare lambda constexpr to be valid for compile-time context
		Using features in costexpr lambda which are not valid for compile-time context results in compilation error

 *************/

#include <iostream>
#include <cassert>
#include <array>
int main() {
	auto constexpr_lambda = [](){ int val = 4; return val; };
	static_assert(4 == constexpr_lambda());

	auto non_constexpr_lambda = [](){ static int val = 4; return val; };
	assert(4 == non_constexpr_lambda());
	//static_assert(4 == non_constexpr_lambda()); // CE error: non-constant condition for static assertion

	auto declare_constexpr_lambda = []() constexpr { int val = 4; return val; };
	//auto check_constexpr_lambda = []() constexpr { static int val = 4; return val; }; // error: 'val' defined 'static' in 'constexpr' function only available with '-std=c++2b' or '-std=gnu++2b'

	std::array<int, declare_constexpr_lambda()> larr{1, 2, 3, 4};

	return 0;
}

/************
  END OF FILE
 ***********/

