/*****************
 *	This example demonstrates the effect of short circuit in logical operators.
 *
 *	Short-circuit:
 *	Builtin operators && and || perform short-circuit evaluation 
 *	(do not evaluate the second operand if the result is known after evaluating the first), 
 *	
 *	NOTE:	overloaded operators behave like regular function calls and always evaluate both operands
 *	NOTE:	bitwise logic operators do not perform short-circuiting.
 *
 * **************/
#include <iostream>

bool this_will_return_true() {
	std::cout << "this will return true\n";
	return true;
}

bool this_will_return_false() {
	std::cout << "this will return false\n";
	return false;
}

int main() {
	std::cout << "=== LOGICAL AND ===\n";
	if(this_will_return_true() && this_will_return_false()) {
		std::cout << "Logical AND - second will be checked if first is true otherwise not\n";
	}

	if(this_will_return_false() && this_will_return_true()) {
		std::cout << "Logical AND - second will be checked if first is true otherwise not\n";
	}

	std::cout << "=== LOGICAL OR ===\n";
	if(this_will_return_true() || this_will_return_false()) {
		std::cout << "Logical OR - second will be checked if first is false otherwise not\n";
	}

	if(this_will_return_false() || this_will_return_true()) {
		std::cout << "Logical OR - second will be checked if first is false otherwise not\n";
	}

	std::cout << "=== BITWISE AND ===\n";
	if(this_will_return_true() & this_will_return_false()) {
		std::cout << "bitwise logic operators do not perform short-circuiting\n";
	}

	if(this_will_return_false() & this_will_return_true()) {
		std::cout << "bitwise logic operators do not perform short-circuiting\n";
	}

	std::cout << "=== BITWISE OR ===\n";
	if(this_will_return_true() | this_will_return_false()) {
		std::cout << "bitwise logic operators do not perform short-circuiting\n";
	}

	if(this_will_return_false() | this_will_return_true()) {
		std::cout << "bitwise logic operators do not perform short-circuiting\n";
	}

	return 0;
}

/************
 *	END OF FILE
 * ************/
