/***********
 *	This example demonstrates the use  of C++20 spaceship operator (or three-way comparison operator).
 *
 *	For more info visit tutorial video:
 *	https://en.cppreference.com/w/cpp/language/operator_comparison#Three-way_comparison
 *
 * *************/

#include <iostream>
#include <set>

struct St {
	int i;
	int j;

	auto operator<=>(const St & rhs) const = default;
	/*
	   auto operator<(const St & rhs) const {
	   return i < rhs.i
	   || (i == rhs.i && j < rhs.j);
	   }
	   */

};


int main() {
	std::set<St> lset;
	lset.insert(St{1, 2});
	lset.insert(St{2, 3});
	lset.insert(St{4, 3});
	lset.insert(St{5, 4});
	lset.insert(St{5, 5});

	std::cout << lset.size() << '\n';
	return 0;
}

/********
 *	END OF FILE
 * ********/
