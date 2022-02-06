/****************
 *	This example demonstrates use of C++ operator overloading feature.
 *
 *	For more info visit:
 *
 * ***************/

#include <iostream>

struct Complex {

	Complex(int p_i) : i(p_i), j(0) { }     // // converting constructor
	//explicit Complex(int p_i) : i(p_i), j(0) { }
	Complex(int p_i, int p_j) : i(p_i), j(p_j) { }

	/*	
		Complex operator+(Complex rhs) {
		std::puts("member operator+");
		return Complex{i + rhs.i, j + rhs.j};
		}
		*/

	//private:
	int i;
	int j;
};

Complex operator+ (Complex lhs, Complex rhs) {
	std::puts("non member operator+");
	return Complex{lhs.i + rhs.i, lhs.j + rhs.j};
}

int main() {
	Complex c1{2,5};
	Complex c2{1,3};

	Complex c3 = c1 + c2;	// uses overloaded operator+, ambiguous call in case both member and non-member operator+ are present
	Complex c4 = c1 + 4;	// uses converting constrcutor and then calls overloaded operator+, ambiguous call in case both member and non-member operator+ are present
	Complex c5 = 5 + c2;	// uses converting constructor and non member operaot+ overload
	Complex c6 = 5 + 4;	// performs addition of integers and then use converting constrcutor to convert it to Complex type

	return 0;
}

/*********
 *	END OF FILE
 * *********/
