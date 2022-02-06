/********
 * This examplde will demonstrate the use of CPP-17 [[nodiscard]] attribute.
 * If a function declared nodiscard or a function returning an enumeration or class declared nodiscard by value is 
 * called from a discarded-value expression other than a cast to void, the compiler is encouraged to issue a warning.
 * ***********/

#include <iostream>

// warning: attribute ignored in declaration of 'struct s' [-Wattributes]
//[[maybe_unused]] struct s 

struct [[nodiscard]] s 
{
	int m;
	[[nodiscard]] int getValue() {return m;}
};
struct s getVal_s() {struct s v{13};     return v;}

//[[nodiscard("Do not ignore return value of fun")]] int fun() { return 2;}  // since c++20 a msg can be argument to nodiscard
[[nodiscard]] int fun() { return 2;} 

int main() {
	// this will generate warning for discarding return value
	fun();

	// this will not generate warning for discarding return value because of cast to void
	static_cast<void>(fun());

	// this will generate warning for unused variable
	int m = fun();

	// this will not genarte warning for 
	// 1. discarding return value - because value is store in a varible
	// 2. unused variable   - because varibel is declared as [[maybe_unused]]
	[[maybe_unused]] int n = fun();

	// this will generate warning for discarding return type s which is declared as [[nodiscard]]
	getVal_s();

	// this will not generate warning for discarding return type s because its stored in a variable of the same type
	struct s sv2 = getVal_s();

	// this will generate warning for discarding return value
	sv2.getValue();

	// this will not genarte warning for 
	// 1. discarding return value - because value is store in a varible
	// 2. unused variable   - because varibel is declared as [[maybe_unused]]
	[[maybe_unused]] int p = sv2.getValue();

	return 0;
}

/*** 
 * END OF FILE 
 * *****/
