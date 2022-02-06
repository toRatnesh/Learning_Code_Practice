/******************
 *	This example demonstrates the use of C++20 std::bind_front algorithm.
 *
 *	For more info visit tutorial video:
 *	https://en.cppreference.com/w/cpp/utility/functional/bind_front
 *
 * *******************/

#include <iostream>
#include <functional>

int my_sum(int p, int q, int r) {
	return p+q+r;
}

int main() {
	const auto func1 = std::bind_front(my_sum, 4); 
	std::cout << func1(6, 10) << '\n';

	const auto func2 = std::bind_front(my_sum, 4, 16); 
	std::cout << func2(10) << '\n';

	return 0;
}

/**********
 *	END OF FILE
 * ************/
