/*************
 *
 * 	This example demonstrates the use of fold expression in CPP 11.
 *
 * 	NOTE : Min values calculated will be stored in initializer list.
 * 		It's tough to get a unique min value from initializer list. 
 *
 * ***********/



#include <iostream>
#include <algorithm>
#include <cmath>
#include <initializer_list>

	template<typename First, typename ... T>
auto variadic_fmin(const First & f, const T & ... t) -> decltype(f) 
{
	First retval = f;
	std::initializer_list<First> list{(retval = std::fmin(retval, t)) ...};
	return *std::next(list.begin(), list.size()-1);
	// return *std::rbegin(list);       // C++14
}

int main() {
	std::cout << variadic_fmin(3.1f, 0.8f, NAN, 0.6f, 6.7f, 0.9f) << '\n';
	return 0;
}

/********
 *	END OF FILE
 * *******/
