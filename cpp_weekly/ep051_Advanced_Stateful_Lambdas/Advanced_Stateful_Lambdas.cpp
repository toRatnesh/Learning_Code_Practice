/********
 *
 * 	This examplde demonstrates the use of advance stateful lambda.
 * 	This example will demonstrate how we can communicate with lambda and share information with lambda.
 *
 *
 * *******/


#include <utility>

int main() {

	auto l_fib = [a = 0, b = 1]() mutable {
		struct Result {
			int &a;
			int &b;
			Result next() {
				a = std::exchange(b, a+b);
				return *this;
			}
		};
		return Result{a, b}.next();
	};

	l_fib();
	l_fib().b = 8;
	return l_fib().a;
}

/********
 *	END OF FILE
 * *******/
