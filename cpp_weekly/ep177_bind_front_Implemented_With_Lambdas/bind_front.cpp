/****************
 *	This example demonstrates how to write our own bind_front version which behaves like std::bind_front.
 *
 *	Also check ep181 which is a improved version of this.
 *
 * ***********/

#include <iostream>
#include <utility>
#include <functional>

struct St {
	static int fun(int a, int b) {
		std::cout << "St::fun " << a << ' ' << b << '\n';
		return a+b;
	}
};

namespace my_exp {
	template<typename F, typename ... Param_t>
		auto bind_front(F && f, Param_t && ... params) {

			return [f = std::forward<F>(f), ...bind_params = std::forward<Param_t>(params)]
				(auto && ... call_params) -> decltype(auto)
				{
					return f(bind_params ..., 
							std::forward<decltype(call_params)>(call_params) ...);
				};
		}
}

int my_sum(int a, int b) {
	return a+b;
}

int main() {
	auto l_f1 = std::bind_front(my_sum, 3);
	std::cout << l_f1(6) << '\n';
	auto l_f2 = std::bind_front(&St::fun, 5);
	std::cout << l_f2(7) << '\n';

	std::cout << '\n';

	auto l_f3 = my_exp::bind_front(my_sum, 3);
	std::cout << l_f3(6) << '\n';
	auto l_f4 = my_exp::bind_front(&St::fun, 5);
	std::cout << l_f4(7) << '\n';

	return 0;
}

/*****
 *	END OF FILE
 * *********/
