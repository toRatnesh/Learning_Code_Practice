/*********
 *
 * 	C++17
 * 	This example demonstrates the use of init statement for if and switch.
 *
 * 	In C++17 if init statement:
 * 		a simple declaration, typically a declaration of a variable with initializer, but it may declare arbitrary many variables or be a decomposition declaration
 *
 * 	In C++17 switch init statement:
 * 		a simple declaration, typically a declaration of a variable with initializer, but it may declare arbitrarily many variables or structured bindings
 * 	
 * *******/

#include <iostream>


int getValue() {
	return 15;
}


int main() {
	if(const int val = getValue();
			(1 <= val && 10 >= val)) {
		std::cout << "Value is 1 - 10" << '\n';
	}
	else if (11 <= val && 20 >= val) {
		std::cout << "Val is 11 - 20" << '\n';
	}
	else {
		std::cout << "val is greater than 20" << '\n';
	}

	switch(const int val = 6;
			0 == (val %2)) {
		case true:
			std::cout << "number is even" << '\n';
			break;
		case false:
			std::cout << "number is odd" << '\n';
			break;
	}

	return 0;
}

/****
 *	END OF FILE
 * ***/
