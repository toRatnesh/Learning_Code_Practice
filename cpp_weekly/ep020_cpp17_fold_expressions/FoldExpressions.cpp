/*************
 *	
 *	This example demonstrates the use of fold expressions in CPP-17.
 *
 * **************/

#include <iostream>
using namespace std;

template<typename ... T>
auto my_print(T ... t) {
	(cout << ... << t) << '\n';
}

int main() {
	my_print(1, 5.6, std::string("Learning any"));
	return 0;
}

/******
 *	END OF FILE
 * ***/
