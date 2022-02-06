/************
 *
 * 	This example demonstrates about use of execution policy for parallel algorithms.
 *
 * 	For more info visit:
 * 	Tutorial video: https://www.youtube.com/watch?v=NSamMd17Csk&list=PLs3KjaCtOwSZ2tbuV1hx8Xz-rFZTan2J1&index=282
 *
 * 	https://en.cppreference.com/w/cpp/algorithm/execution_policy_tag
 * 	https://en.cppreference.com/w/cpp/algorithm/execution_policy_tag_t
 *
 *
 * **********/

#include <iostream>
#include <string>
#include <algorithm>
#include <execution>

int main() {
	std::vector<uint32_t> lv{1,4,9,53,17,29,23,16,28,36,66,46};

	//std::sort(lv.begin(), lv.end());
	//std::sort(std::execution::par, lv.begin(), lv.end());
	std::sort(std::execution::par_unseq, lv.begin(), lv.end());

	for(const auto elem: lv) {
		std::cout << elem << ' ';
	}
	std::cout << '\n';

	return 0;
}

/*******
 *	END OF FILE
 * *******/
