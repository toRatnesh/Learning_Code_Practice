/***********
 *	This examplde demonstrates the use of generic lambda and how it may be used to replace inherited lambda.
 *
 * ***************/

#include <iostream>
#include <variant>
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

	std::vector<std::variant<int, double>> lv {13, 83.56, 15, 23.78};

	int total_int = 0;
	double total_double = 0;
	std::common_type_t<decltype(total_int), decltype(total_double)> total = 0;
	/*
	// CASE 1 - USING INHERITED LAMBDA
	Visitor li_visitor { [&total_int, &total](const int arg) { total_int += arg; total += arg; },
	[&total_double, &total](const double arg) { total_double += arg; total += arg;}
	};
	std::for_each(std::begin(lv), std::end(lv),
	[&li_visitor](const auto & elem) {std::visit(li_visitor, elem);} );
	*/

	// CASE 2 - USING GENERIC LAMBDA
	const auto lg_visitor = [&total_int, &total_double, &total](const auto  arg) {
		total += arg;

		if constexpr(std::is_same<double, std::decay_t<decltype(arg)>>::value) {
			total_double += arg;
		} 
		else {
			total_int += arg;
		}
	};
	std::for_each(std::begin(lv), std::end(lv),
			[&lg_visitor](const auto & elem) {std::visit(lg_visitor, elem); });

	std::cout << "total_int " << total_int << '\n';
	std::cout << "total_double " << total_double << '\n';
	std::cout << "total " << total << '\n';	

	return 0;
}

/********
 *	END OF FILE
 * ********/
