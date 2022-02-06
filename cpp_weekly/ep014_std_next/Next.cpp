/***************************************
 *	This example demonstrates the use of std::next
 *
 * *************************************/

#include <iostream>
#include <list>
#include <vector>

int main(void) {
	//std::list<int> l_val{1, 2, 3, 4, 5};
	std::vector<int> l_val{1, 2, 3, 4, 5};


	std::cout << *(std::next(std::begin(l_val), 2)) << '\n';
	std::cout << '\n';

	for(auto it = std::begin(l_val); it != std::end(l_val); ++it) {
		std::cout << *it << '\n';
	}
	std::cout << '\n';

	for(auto it = std::begin(l_val); it != std::end(l_val); it = std::next(it)) {
		std::cout << *it << '\n';
	}
	std::cout << '\n';

	for(auto it = l_val.cbegin(); it != l_val.cend(); ++it) {
		std::cout << *it << '\n';
	}

	return 0;
}

/************
 *	EOF
 * *********/

