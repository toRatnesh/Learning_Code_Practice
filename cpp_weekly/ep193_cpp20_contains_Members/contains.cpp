/*************
 *	This example demonstrates use of 'contains()' member functions introduced in c++20 for containers.
 *
 *	contains() member function is used to check for existence of a key in the container.
 * ************/

#include <iostream>
#include <set>
#include <map>
#include <string>

int main() {
	std::multiset lmset{1,2,5,9,5,2,8,6};
	for(auto x : {2, 5, 4, 6, 3}) {
		if(lmset.contains(x)) {
			std::cout << x << "- present in multiset\n";
		}
		else {
			std::cout << x << "- not present in multiset\n";
		}
	}
	std::cout << '\n';

	std::multimap<std::string, int> lmmap{{"one", 1}, {"two", 2}, {"three", 3}, {"one", 1}, {"five", 5}, {"two", 2}};
	for(auto x : {"one", "two", "three", "four", "five", "six"}) {
		if(lmmap.contains(x)) {
			std::cout << x << "- present in multimap\n";
		}
		else {
			std::cout << x << "- not present in multimap\n";
		}
	}

	return 0;
}


/*******
 *	END OF FILE
 * ********/
