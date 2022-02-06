/****************
 *	This example demonstrates the use of following C++20 lambda features:
 *	Lambdas in unevaluated contexts
 *	Default constructible and assignable stateless lambdas
 *
 * ***************/

#include <iostream>
#include <set>

int main() {

	auto lbd = [](const int num){return num*num;};
	auto lbd_copy = lbd;        // copy lambda 
	decltype(lbd) lbd2;         // C++20 default constructible
	lbd = lbd_copy;             // C++20 copy assignment operator

	decltype([]{}) lbd_uc;      // C++20 lambda-expression in unevaluated context

	struct myData {
		int data;
	};

	const auto myDataComparator = [](const myData & lhs, const myData & rhs) {
		return lhs.data < rhs.data;
	};
	std::set<myData, decltype(myDataComparator)> lset;  // use of C++20 default constructible

	return 0;
}

/*********
 *	END OF FILE
 * *********/
