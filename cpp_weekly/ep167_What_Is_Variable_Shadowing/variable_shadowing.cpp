/*************
 *
 * 	This example demonstrates the use GCC warning flag -Wshadow to get warning about variable shadowing.
 *
 * 	Variable Shadowing (Name hiding)
 * 	It's possible to declare a variable with the same name as a variable from the outer scope.
 * 	The newly created variable will shadow the variable of the outer scope, that is, all uses within the inner scope will refer to the newly created variable.
 *
 * 	For more info about variable shadowing visit:
 * 	https://en.cppreference.com/book/intro/scope
 *
 *
 * 	-Wshadow
 * 	Warn whenever a local variable or type declaration shadows another variable, parameter, type, class member (in C++), or instance variable (in Objective-C) or whenever a built-in function is shadowed. 
 * 	Note that in C++, the compiler warns if a local variable shadows an explicit typedef, but not if it shadows a struct/class/enum. 
 * 	If this warning is enabled, it includes also all instances of local shadowing. This means that -Wno-shadow=local and -Wno-shadow=compatible-local are ignored when -Wshadow is used. Same as -Wshadow=global.
 *
 * ******************/

#include <iostream>

int main() {

	int i = 0;
	int sum = 0;

	for(int i = 0; i < 5; ++i) 
	{
		int sum = 5;
		sum = sum + i;
	}

	std::cout << sum << '\n';

	return 0;
}

/*******
 *	END OF FILE
 * ******/
