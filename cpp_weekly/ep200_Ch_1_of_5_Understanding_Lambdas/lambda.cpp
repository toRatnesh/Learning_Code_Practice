/***********
 *	This example demonstrates what is a lambda.
 *
 *	Also check previous episodes on lambda:
 *	ep152_Lambdas_The_Key_To_Understanding_CPP
 *	ep133_What_Exactly_IS_A_Lambda_Anyhow
 *	ep037_stateful_lambdas
 *	ep051_Advanced_Stateful_Lambdas
 *	ep040_Inheriting_From_Lambdas
 *	ep097_Lambda_To_Function_Pointer_Conversion
 *
 *
 *	Answer following questions:
 *	1. reason for wanting lambda to function pointer conversion
 *	Ans:	When we want to pass it to API in C language which takes a function pointer parameter
 *
 *	2. practical application for inheriting from lambda
 *	Ans:	Direct access to operator()()
 *
 *	3. implment following lambda using class/struct
 *		auto l = [n0=0, n1=1]() mutable  { n0 = std::exchange(n1, n0+n1); return n0; };
 *
 *	Ans:	implementation is below in code
 *
 * ************/

#include <iostream>
#include <utility>

class Fib {
	private:
		int n0=0;
		int n1=1;

	public:
		inline int operator()() noexcept {
			n0 = std::exchange(n1, n0+n1); 
			return n0;
		}
};

int main() {
	std::cout << "=== USING LAMBDA ===\n";
	auto l = [n0=0, n1=1]() mutable  { n0 = std::exchange(n1, n0+n1); return n0; };
	std::cout << l() << ' ' << l() << ' ' << l() << ' ' << l() << ' ' << l() << ' ' << l() << '\n';

	std::cout << "=== USING CLASS ===\n";
	Fib lfb;
	std::cout << lfb() << ' ' << lfb() << ' ' << lfb() << ' ' << lfb() << ' ' << lfb() << ' ' << lfb() << '\n';

	return 0;
}

/************
 *	END OF FILE
 * ***********/
