/*******
 * 	This tutorial demonstrates the use of stateful lambda.
 *	Stateful Lambdas:
 *		
 *
 * *****/

#include <iostream>
#include <memory>

int main() {

	int j = 5;

	// error: increment of read-only variable 'i'
	//auto l = [i = 0, &r = j](const int g)  { std::cout << g << '\n'; ++r; return ++i;};

	auto l = [i = 0, &r = j](const int g) mutable { std::cout << g << '\n'; ++r; return ++i;};
	[[maybe_unused]] auto l2 = l;

	auto l3 = [i = 0, &r = j, p = std::make_unique<int>(2)] (const int g) mutable { std::cout << g << ' ' << *p << '\n'; ++r; return ++i;};  
	l3(13);
	// error: use of deleted function 'std::unique_ptr<_Tp, _Dp>::unique_ptr(const std::unique_ptr<_Tp, _Dp>&) [with _Tp = int; _Dp = std::default_delete<int>]'
	//auto l4 = l3;

	return l(5);
}

/****
 *	END OF FILE
 * ***/
