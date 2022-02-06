/********
 *	This example demonstrates the used of inheriting from lambdas.
 *
 *
 * **********/

#include <iostream>

template<typename B1, typename B2>
struct Merged : B1, B2 
{
	Merged(B1 b1, B2 b2) : B1(std::move(b1)), B2(std::move(b2)) 
	{

	}

	// make all overloads of operator() in base class visible in derived class
	// Item 33: Avoid hiding inherited names | Effective C++ | Scott Meyers
	using B1::operator();
	using B2::operator();
};

int main() {
	const auto l_eo = [](const int num){std::cout << (0 == (num % 2) ? "Even" : "Odd") << '\n'; };
	const auto l_msg = [](const std::string & msg) { std::cout << msg << '\n'; };
	l_eo(17);
	l_msg("Simple lambda");

	Merged mrg(l_eo, l_msg);
	mrg(22);
	mrg("Inheritance from lambda");

	return 0;
}


/******
 *	END OF FILE
 * *****/
