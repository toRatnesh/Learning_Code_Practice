/**************
 *	This exmaple demonstrates the use of c++14 varible templates.
 *
 *	Variable Template:
 *	A variable template defines a family of variables or static data members.
 *
 *	For more info visit:
 *	https://en.cppreference.com/w/cpp/language/variable_template
 *
 * **************/

#include <iostream>
#include <iomanip>

namespace ns {

	template<class T>
		constexpr T pi = T(3.1415926535897932385L);

	template<int value>
		constexpr auto fib = fib<value-1> + fib<value-2>;
	template<>
		constexpr auto fib<0> = 0;
	template<>
		constexpr auto fib<1> = 1;

	template<typename T, typename U>
		constexpr auto is_same = false;

	template<typename T>
		constexpr auto is_same<T, T> = true;

}

int main() {
	std::cout << std::setprecision(20) << ns::pi<int> << '\n';
	std::cout << std::setprecision(20) << ns::pi<float> << '\n';
	std::cout << std::setprecision(20) << ns::pi<double> << '\n';
	std::cout << std::setprecision(20) << ns::pi<long double> << '\n';
	std::cout << '\n';

	std::cout << ns::fib<0> << '\n';
	std::cout << ns::fib<1> << '\n';
	std::cout << ns::fib<2> << '\n';
	std::cout << ns::fib<3> << '\n';
	std::cout << ns::fib<4> << '\n';
	std::cout << '\n';

	std::cout << ns::is_same<int, int> << '\n';
	std::cout << ns::is_same<int, double> << '\n';
	std::cout << ns::is_same<float, double> << '\n';
	std::cout << ns::is_same<bool, int> << '\n';

	return 0;
}


/************
 *	END OF FILE
 * **********/
