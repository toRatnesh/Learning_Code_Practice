/**************
 *
 *	This example demonstrates the use of inheritance from lambda.
 *	Also check episode 134 ep134_Best_Possible_Way_To_Create_A_Visitor which demonstrates improvement of visitor code.
 *
 * ***********/

#include <iostream>
#include <variant>
#include <string>
#include <vector>
#include <algorithm>

template<typename ... B>
struct Visitor : B...
{
	template<typename ... T>
		Visitor(T && ... t) : B(std::forward<T>(t))...
	{ }
	using B::operator()...;
};

// deduction guide
template<typename ... T>
Visitor(T ...) -> Visitor<std::decay_t<T>...>;

int main() {

	std::vector<std::variant<int, long, double, std::string>> lv {13, 15l, 13.56, R"(A variant)"};

	int total_int = 0;
	int total_double = 0;

	Visitor l_visitor { [](const auto & arg) { std::cout << arg << '\n'; },
		[&total_int](const int arg) { total_int += arg; std::cout << "int " << arg << '\n';},
		[&total_double](const double arg) { total_double += arg; std::cout << "double " << arg << '\n';}
		//[](const long arg) { std::cout << "long " << arg << '\n'; } 
	};

	std::for_each(std::cbegin(lv), std::cend(lv), 
			[&l_visitor](const auto & elem) {std::visit(l_visitor, elem);} );

	return 0;
}


/*******
 *	END OF FILE
 * ******/
