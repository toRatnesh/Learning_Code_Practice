/****
 *	In CPP17 emplace_back method for sequence contaners returns reference to the inserted element.
 *
 * ****/

#include <iostream>
#include <vector>

int main() {

	std::vector<std::vector<int>> v;
	v.emplace_back(3, 1).push_back(4);
	v.emplace_back(7, 9).pop_back();

	for(const auto & lv : v) {
		for(const auto val : lv) {
			std::cout << val << ' ';
		}
		std::cout << '\n';
	}


	return 0;
}

/****
 *	END OF FILE
 * ****/
