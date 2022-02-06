/*************
 *	This example demonstrates the use of nodiscard attribute for constructor.
 *
 *	For more info visit:
 *	https://en.cppreference.com/w/cpp/language/attributes/nodiscard
 *	http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2019/p1771r1.pdf
 *
 * ************/

#include <iostream>

struct [[nodiscard]]  St {
	int data;

	[[nodiscard]] 
		St(int val) : data(val) {}

};

St get_st() {
	return St{13};
}

int main() {

	St{5};		// warning because of [[nodiscard]] constructor
	get_st();	// warning because of [[nodiscard]] type

	auto val = St{2};
	auto val2 = get_st();
	std::cout << val.data << '\n';
	std::cout << val2.data << '\n';

	return 0;
}

/*******
 *	END OF FILE
 * ********/
