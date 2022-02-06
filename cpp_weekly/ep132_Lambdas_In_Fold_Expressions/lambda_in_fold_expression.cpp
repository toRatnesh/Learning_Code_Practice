/*************
 *	This example demonstrates the use of lambda in fold expressions.
 *
 * *******************/

#include <iostream>

template<typename ... T>
void fun(T ... t) {
	((std::cout <<  t << ' '), ...);    // using simple print

	std::cout << '\n';

	// lambda in fold expression
	([t](){ std::cout << t << ' ';}(), ...);   // using lambda

	return ;
}

int main()
{
	fun(1, 5.6, 7.8f, "sample string");

	return 0;
}

/******
 *	END OF FILE
 * ********/
