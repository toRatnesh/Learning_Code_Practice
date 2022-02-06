/*********
 *	
 *	This example demonstrates the use of cpp11 std::fmin and cpp17 varidic template to create a variadic fmin.
 *
 * *******/

#include <iostream>
#include <algorithm>
#include <cmath>

template<typename First, typename ... T>
decltype(auto) variadic_fmin(const First & f, const T & ... t) {
	First retval = f;
	((retval = std::fmin(retval, t)), ...);
	return retval;
}

int main() {
	std::cout << variadic_fmin(3.1f, -1.2f, NAN, 5.6f, 6.7f) << '\n';
	return 0;
}

/*******
 *	END OF FILE
 * *******/
