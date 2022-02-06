/************
 *
 *		This example demonstrates a few points about member access in virtual class.
 *
 * *********/

#include <iostream>
struct Base {
		uint32_t base_val = 33;
};
struct Intermediate1 : Base {
		uint32_t val = 43;
};
struct Intermediate2 : virtual Base {
		uint32_t val = 53;
};
struct Intermediate3 : virtual Base {
		uint32_t val = 63;
};
struct Derived : Intermediate1, Intermediate2, Intermediate3 {
		uint32_t drvd_val = 73;
};

int main() {
		Derived d;

		++d.drvd_val;
		std::cout << d.drvd_val << '\n';
		// error: request for member 'val' is ambiguous
		// NOTE: ambiguity because not sure which val to use i.e. from Intermediate1, Intermediate2 or Intermediate3
		//std::cout << d.val << '\n';

		++d.Intermediate1::val;
		++d.Intermediate2::val;
		++d.Intermediate3::val;
		std::cout << d.Intermediate1::val << '\n';
		std::cout << d.Intermediate2::val << '\n';
		std::cout << d.Intermediate3::val << '\n';

		++d.Intermediate1::base_val;
		++d.Intermediate2::base_val;
		++d.Intermediate3::base_val;
		// error: request for member 'base_val' is ambiguous
		// NOTE: ambiguity because not sure which way to get val to use i.e. through Intermediate1, Intermediate2 or Intermediate3
		//std::cout << d.base_val << '\n';
		std::cout << d.Intermediate1::base_val << '\n';
		std::cout << d.Intermediate2::base_val << '\n';
		std::cout << d.Intermediate3::base_val << '\n';

		return 0;
}

/*****
 *	END OF FILE
 * *********/
