/*************
 *	This example demonstrates how c++20 has deprecated comma operator in subscripts.
 *	It may lead to path of 2-D array support in c++ standard.
 *
 *	In C++ we also get warning where comma operator has no effect.
 *
 *	For more info visit:
 *	https://en.cppreference.com/w/cpp/language/operator_other#Built-in_comma_operator
 *
 * *****************/

#include <iostream>
#include <vector>

int log_this() {
	std::puts("deprecating comma");
	return 2;
}

int main() {
	std::vector<int> lv{1,2,3,4,5};

	std::cout << lv[3] << '\n';
	std::cout << lv[2, 3] << '\n';          // c++11 warning: left operand of comma operator has no effect
		// c++20 warning: top-level comma expression in array subscript is deprecated [-Wcomma-subscript]

	std::cout << lv[log_this(), 3] << '\n'; // c++20 warning: top-level comma expression in array subscript is deprecated [-Wcomma-subscript]

	return 0;
}

/*******
 *	END OF FILE
 * ********/
