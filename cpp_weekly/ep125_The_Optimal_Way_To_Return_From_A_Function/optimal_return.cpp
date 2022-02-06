/***********
 *	This example demonstrates optimal way to return from a function.
 *
 *	For more info visit tutorial video:
 *	https://www.youtube.com/watch?v=9mWWNYRHAIQ&list=PLs3KjaCtOwSZ2tbuV1hx8Xz-rFZTan2J1&index=127
 *
 * *************/

#include <iostream>
#include <string>

std::string getValue(const bool arg) {

	/******************
	 * 	M-1	return using conditional assignment
	 * 	This is not optimal way to return because first retval is default constructed and then assigned 
	 * ********************/
	/*	//M-1
	std::string retval;
	if(arg) {
		retval = "sample string";
	} else {
		retval = "different string";
	}
	return retval;
	*/


	/************
	 *	M-2 return using ternary operator
	 *	This is not optimal way to return because implicit conversion from const char * to string
	 * *************/
	//return arg ? "sample string" : "different string";
	

	/************
	 *	M-3  Updated return using ternary operator
	 *	This method to return uses RVO so it is has performace benefit over M-2
	 * *************/
	//return arg ? std::string("sample string") : std::string("different string");

	/*********
	 *	M-4 using if condition instead of ternary
	 *	This method also uses RVO so has performance advantage over M-1
	 * ************/
	if(arg) {
		return std::string("sample string");
	}
	return std::string("different string");
}


int main() {
	std::string s = getValue(true);
	return 0;
}

/******
 *	END OF FILE
 * *******/
