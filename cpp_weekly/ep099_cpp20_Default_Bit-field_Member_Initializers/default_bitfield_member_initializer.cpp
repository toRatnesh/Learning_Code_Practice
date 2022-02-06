/********
 *	This example demonstrated the use of cpp20 default bit field member initializer.
 *
 * ***********/

#include <iostream>

struct S {
	int i:3 = 2;
	int j:5 = 5;

};

int main() {
	std::cout << sizeof(S) << '\n';
	S s;
	std::cout << s.i << ',' << s.j << '\n';

	return 0;
}

/*********
 *	END OF FILE
 * ********/
