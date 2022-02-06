/************
 * 	This example demonstrates the use of CPP 20 parameter pack-expansions in lambda init-captures.
 *
 * 	For more info visit:
 * 	https://en.cppreference.com/w/cpp/language/lambda#Lambda_capture
 *
 * **************/

#include <iostream>
#include <utility>

template<typename Callable, typename ... Params>
auto bind_vals(Callable p_callable, Params ... p_params) {
	/*
	   return [=](){
	   return p_callable(p_params ...);
	   };
	   */

	return [callable = std::move(p_callable), ...params = std::move(p_params)](){
		return callable(params ...);
	};
}

int my_sum(int m, int n) {
	return m+n;
}

int main() {
	const auto bound = bind_vals(my_sum, 5, 6);
	std::cout << bound() << '\n';

	return 0;
}

/*********
 *	END OF FILE
 * ********/
