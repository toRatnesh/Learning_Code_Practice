/******************
 *	This example demonstrates how overloaded logical AND(&&) and OR(||) operators change 
 *	the semantic behaviour of these operators and they do not perform short circuit anymore.
 *
 *
 *	BETTER APPROACH:
 *	In this case it is generated better to define an operator bool instead of overloading the logical operators. 
 *
 * ****************/


#include <iostream>

static int st_counter = 0;

struct St {
	bool value;
	St(const bool bval) : value(bval) {
		std::puts("parameterized constructor"); 
		++st_counter;
	}

	//explicit operator bool() const;    
};

/*
St::operator bool() const {
	std::puts("overloaded operator bool");
	return value;
}
*/

bool operator&&(const St & lhs, const St & rhs) {
	std::puts("non member overalod of &&");
	return lhs.value && rhs.value;
}

bool operator||(const St & lhs, const St & rhs) {
	std::puts("non member overalod of ||");
	return lhs.value || rhs.value;
}

St make_st(const bool bval) { 
	std::puts("make_st");
	return St(bval);
}

bool getBoolean(const bool bval) {
	std::puts("getBoolean");
	return bval;
}

int main() {

	// NO SHORT CIRCUIT WILL BE PERFORMED FOR OVERLOADED LOGICAL AND(&&) and OR(||) operators
	// COMMENT OVERLOADED VERSION AND DEFINE operator bool AND CHECK HOW IT BEHAVES AS EXPECTED

	std::puts("=== Logical OR ===");
	make_st(true) || make_st(false);

	std::puts("=== Logical AND ===");
	make_st(false) && make_st(true);

	std::cout << st_counter << '\n';

	return 0;
}





/*********
 *	END OF FILE
 * ********/
