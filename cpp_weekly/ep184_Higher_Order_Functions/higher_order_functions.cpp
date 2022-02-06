/*****************
 *	This example explains about higher order function.
 *
 *	Higher Order Function:
 *	In mathematics and computer science, a higher-order function is a function that does at least one of the following:
 *	takes one or more functions as arguments (i.e. procedural parameters),
 *	returns a function as its result.
 *
 *	For more info visit:
 *	https://en.wikipedia.org/wiki/Higher-order_function
 *	https://en.wikipedia.org/wiki/Higher-order_function#C++
 *	https://www.modernescpp.com/index.php/higher-order-functions
 *
 * ******************/

#include <iostream>
#include <utility>

template<typename F, typename G>
auto f_of_g(F && f, G && g) {
	return [f = std::forward<F>(f), g = std::forward<G>(g)] (int val) {
		f(g(val));
	};
}

int fun_square(int val) {
	std::puts("square function");
	return val * val;
}

int fun_half(int val) {
	std::puts("half function");
	return val / 2;
}

int main() {
	const auto callthis = f_of_g(fun_half, fun_square);
	callthis(2);

	return 0;
}

/**********
 *	END OF FILE
 * *********/
