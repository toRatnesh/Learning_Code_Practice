/******
 *	This example demonstrates the use of std::is_constant_evaluated.
 *	std::is_constant_evaluated
 *	Detects whether the function call occurs within a constant-evaluated context. 
 *	Returns true if the evaluation of the call occurs within the evaluation of an expression or conversion that is manifestly constant-evaluated; otherwise returns false.
 *
 *	For more info visit:
 *	https://en.cppreference.com/w/cpp/types/is_constant_evaluated
 *
 * ********/

#include <iostream>

constexpr auto fun() {
	if (std::is_constant_evaluated()) {
		return 5;
	}
	else {
		return 10;
	}
}

int main() {
	auto val = fun();
	const auto cval = fun();
	constexpr auto ceval = fun();

	std::cout << "val " << val << " cval " << cval << " ceval " << ceval << '\n';

	return 0;
}

/******
 *	END OF FILE
 * *****/
