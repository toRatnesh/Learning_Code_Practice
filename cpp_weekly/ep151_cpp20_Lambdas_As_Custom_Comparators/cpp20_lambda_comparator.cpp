/**************
 *	This example demonstrates the use of following c++20 lambda features for comparator.
 *	Lambdas in unevaluated contexts
 *	Default constructible and assignable stateless lambdas
 *
 * *************/
#include <iostream>
#include <set>

struct St{ int data; };

int main() {

	const auto lambda_comparator = [](const St & lhs, const St & rhs){
		return lhs.data < rhs.data;
	};

	// C++17
	std::set<St, decltype(lambda_comparator)> lset1{lambda_comparator};

	// C++17 auto template type deduction
	std::set lset2{ {St{5}}, lambda_comparator};

	// C++20 use of lambda default constructor
	std::set<St, decltype(lambda_comparator)> lset3;    

	// C++20 use of lambda in UC and default constructor
	std::set<
		St, 
		decltype([](const St & lhs, const St & rhs){ return lhs.data < rhs.data;})
			> lset4;


	return 0;
}

/********
 *	END OF FILE
 * **********/
