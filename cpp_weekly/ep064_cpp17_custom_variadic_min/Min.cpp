/**********
 *
 * 	This example demonstrates the use of cpp11 std::min and cpp17 variadic template to create a variadic min. 
 *
 * **********/

#include <iostream>
#include <algorithm>

int min_1(const int a, const int b) {
	return std::min(a, b);
}

int min_2(const int a, const int b, const int c) {
	//return std::min(std::min(a, b), c);
	return std::min({a,b,c});           // since C++11
}

template<typename First, typename ... T>
decltype(auto) variadic_min(const First & f, const T & ... t) {
	First retval = f;
	((retval = std::min(retval, t)), ...);
	return retval;
}

int main() {

	std::cout << std::min(1, 3) << '\n';
	std::cout << std::min(3, 1) << '\n';

	std::cout << std::min(99, 99999999) << '\n';
	std::cout << std::min(99999999, 99) << '\n';
	std::cout << '\n';

	std::cout << std::min(1, -3) << '\n';
	std::cout << std::min(-3, 1) << '\n';

	std::cout << std::min(99, -99999999) << '\n';
	std::cout << std::min(-99999999, 99) << '\n';

	// CE: no matching function for call to 'min(int, long int)'
	//std::cout << std::min(99, 999999999999) << '\n';
	std::cout << ((99 < 999999999999) ? 99 : 999999999999) << '\n';
	std::cout << '\n' << '\n';


	std::cout << min_1(1, 3) << '\n';
	std::cout << min_1(3, 1) << '\n';

	std::cout << min_1(99, 99999999) << '\n';
	std::cout << min_1(99999999, 99) << '\n';
	std::cout << '\n';

	std::cout << min_1(1, -3) << '\n';
	std::cout << min_1(-3, 1) << '\n';

	std::cout << min_1(99, -99999999) << '\n';
	std::cout << min_1(-99999999, 99) << '\n';

	// CE: no matching function for call to 'min(int, long int)'
	//std::cout << std::min(99, 999999999999) << '\n';
	std::cout << ((99 < 999999999999) ? 99 : 999999999999) << '\n';
	std::cout << '\n' << '\n';


	std::cout << min_2(1, 2, 3) << '\n';
	std::cout << min_2(3, 2, 1) << '\n';

	std::cout << min_2(99, 999, 99999999) << '\n';
	std::cout << min_2(99999999, 999, 99) << '\n';
	std::cout << '\n';

	std::cout << min_2(1, 0, -3) << '\n';
	std::cout << min_2(-3, 0, 1) << '\n';

	std::cout << min_2(99, 0, -99999999) << '\n';
	std::cout << min_2(-99999999, 0, 99) << '\n';

	// CE: no matching function for call to 'min(int, long int)'
	//std::cout << std::min(99, 999999999999) << '\n';
	std::cout << ((99 < 999999999999) ? 99 : 999999999999) << '\n';
	std::cout << '\n' << '\n';

	std::cout << variadic_min(1, 3) << '\n';
	std::cout << variadic_min(3, 1) << '\n';

	std::cout << variadic_min(99, 99999999) << '\n';
	std::cout << variadic_min(99999999, 99) << '\n';
	std::cout << '\n';

	std::cout << variadic_min(1, -3) << '\n';
	std::cout << variadic_min(-3, 1) << '\n';

	std::cout << variadic_min(99, -99999999) << '\n';
	std::cout << variadic_min(-99999999, 99) << '\n';

	// CE: no matching function for call to 'min(int, long int)'
	//std::cout << std::min(99, 999999999999) << '\n';
	std::cout << ((99 < 999999999999) ? 99 : 999999999999) << '\n';
	std::cout << '\n' << '\n';


	return 0;
}

/*******
 *	END OF FILE
 * ******/
