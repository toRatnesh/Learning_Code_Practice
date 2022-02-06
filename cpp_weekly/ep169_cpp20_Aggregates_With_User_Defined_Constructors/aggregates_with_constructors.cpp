/**************
 *	This example demonstrates the use of cpp20 aggregate initialization with use defined constructor.
 *
 *	Prior to C++20, C++ allows some types with user-declared constructors to be initialized via aggregate initialization, bypassing those constructors. CPP 20 fixes this bug.
 *
 *	For more info visit:	
 *	http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2018/p1008r1.pdf
 *
 *
 * ****************/


struct St {

	St() = delete;
	St(int p, int q) = delete;

	int x;
	int y;
};

int main () {

	St st1;	// CE error: use of deleted function 'St::St()'     
	St st2{};       // C++17 - compiles even if constrcutor is deleted
			// C++20 error: use of deleted function 'St::St()'
	St st3{1, 3};   // C++17 - compiles even if constrcutor is deleted
			// C++20 error: use of deleted function 'St::St(int, int)'
	return 0;
}



/******
 *	END OF FILE
 * **********/

