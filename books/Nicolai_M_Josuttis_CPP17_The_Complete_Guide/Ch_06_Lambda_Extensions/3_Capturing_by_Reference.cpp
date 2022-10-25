/************

  References
  C++17 - The Complete Guide | Nicolai M. Josuttis

  Lambda
  C++11   Lambda
  C++14   Generic lambdas
  C++17   In constant expression
  In places where you need a copy of the current object

  3. Capturing by Reference
	use std::as_const to capture by const reference

 *************/

#include <iostream>
#include <utility>

int main() {
	int val = 5;
	const int cval = 6;

	auto l1 = [&val = std::as_const(val)]() {
		std::clog << val << ' ' << cval << '\n';
		//++val; // CE: error: increment of read-only reference 'val'
		std::clog << val << ' ' << cval << '\n';
	};
	l1();

	auto l2 = [&]() {
		std::clog << val << ' ' << cval << '\n';
		++val;
		//++cval; // CE: error: increment of read-only reference 'cval'
		std::clog << val << ' ' << cval << '\n';
	};
	l2();

	return 0;
}

/************
  END OF FILE
 ***********/

