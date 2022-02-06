/*************
 *
 *	This examplde demonstrates the use of C++17
 *	Variadic using declaration with
 *	C++17 Class template type deduction
 *	C++17 template type deduction guide
 *
 * ************/

#include <iostream>
#include <utility>

template<typename ... B>
struct Merged : B...
{
	template<typename ... T>
		Merged(T && ... t) : B(std::forward<T>(t))... 
	{ }
	using B::operator()...;
};

template<typename ... T>
Merged(T ...) -> Merged<std::decay_t<T>...>;

int main() {

	const auto l_eo = [](const int num){std::cout << (0 == (num % 2) ? "Even" : "Odd") << '\n'; };
	const auto l_msg = [](const std::string & msg) { std::cout << msg << '\n'; };
	l_eo(17);
	l_msg("Simple lambda\n");

	Merged mrg(l_eo, l_msg);
	mrg(22);
	mrg("Inheritance from lambda\n");

	Merged mrg2(l_eo, l_msg, 
			[](const int count, const std::string & msg) {
			for(uint8_t i = 0; i < count; ++i) {
			std::cout << msg << '\n';
			}
			} );
	mrg2(30);
	mrg2("Inheritance from lambda 02\n");
	mrg2(3, "Inheritance from lambda 03\n");

	return 0;
}


/*********
 *	END OF FILE
 * *********/

