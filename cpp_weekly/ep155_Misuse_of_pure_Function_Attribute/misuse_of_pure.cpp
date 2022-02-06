/***********
 *	This example demonstrates how sometimes use of GNU pure attribute may lead to unexpected result.
 *
 *	In this case compiler may generate warning for those statements using pure function that have no effect. 
 *	Pay attention to compiler warnings.
 *
 *	Also compiler may ignore the optimization depending on the context in which the statements calling pure functions are used.
 *
 * ************/

#include <iostream>

struct St{ 
	int val = 0; 
	[[gnu::pure]] int increment_value() {
		return ++val;
	}
};

int main() {
	St s;

	// no optimization in this case all call will be effective
	int res = s.increment_value() + s.increment_value() + s.increment_value(); 

	s.increment_value();    // warning: statement has no effect
	s.increment_value();    // warning: statement has no effect

	// this wil return 4 in case [[gnu::pure]] is present and 6 in case [[gnu::pure]] is not present   
	// but we will also get compiler warning for statement that has no effect
	return s.increment_value();     
}

/*******
 *	END OF FILE
 * *********/
