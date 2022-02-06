/**********
 *
 * 	This exmaple demonstrates the use of cpp17 with cpp20 require clause
 *
 * 	For more info visit:
 * 	https://en.cppreference.com/w/cpp/keyword/requires
 * 	https://en.cppreference.com/w/cpp/language/constraints
 *
 * ***********/

#include <iostream>
#include <vector>
#include <array>

auto allocated_size(const auto & container) {

	if constexpr( requires {container.capacity(); }) {
		return container.capacity();
	}

	return container.size();
}

int main() {

	std::vector lv {1,2,3,4,5};
	std::array  la {1,2,3,4,5};

	std::cout << "Allocated size is " << allocated_size(lv) << '\n';
	std::cout << "Allocated size is " << allocated_size(la) << '\n';

	lv.push_back(6);
	std::cout << "Allocated size is " << allocated_size(lv) << '\n';
	std::cout << "Allocated size is " << allocated_size(la) << '\n';

	return 0;
}

/******
 *	END OF FILE
 * *******/
