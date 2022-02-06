/*************
 *	This example demonstrates the use of c++20 using enum declaration.
 *
 *	For more info visit:
 *	https://en.cppreference.com/w/cpp/language/enum#Using-enum-declaration
 *
 * ***********/

#include <iostream>

enum class colors_t{
	RED,
	GREEN,
	BLACK,
	WHITE
};

int main() {
	colors_t l_color = colors_t::GREEN;

	switch(l_color) {
		case colors_t::RED:
			std::puts("RED"); break;
		case colors_t::GREEN:
			std::puts("GREEN"); break;
		case colors_t::BLACK:
			std::puts("BLACK"); break;
		case colors_t::WHITE:
			std::puts("WHITE"); break;
		default:
			std::puts("NOT A VALID COLOR");
	}

	// since C++20
	using enum colors_t;
	switch(l_color) {
		case RED:
			std::puts("RED"); break;
		case GREEN:
			std::puts("GREEN"); break;
		case BLACK:
			std::puts("BLACK"); break;
		case WHITE:
			std::puts("WHITE"); break;
		default:
			std::puts("NOT A VALID COLOR");
	}

	return 0;
}

/*********
 *	END OF FILE
 * *********/
