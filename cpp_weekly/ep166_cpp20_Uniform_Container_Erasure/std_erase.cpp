/*************
 *	This example demonstrates the use of std::erase method of std::vector.
 *
 * **********/

#include <iostream>
#include <vector>

void print_vector(const std::vector<int> & parm_vec) {
	for(const auto val : parm_vec) {
		std::cout << val << ' ';
	}
	std::cout << '\n';
}

int main() {

	std::vector<int> lvec{1,2,3,4,5,6,7,8,9,10,5,11,5,12,5};

	std::cout << "=== USING STD::ERASE ===\n";
	std::erase(lvec, 5);
	print_vector(lvec);
	std::erase_if(lvec, [](const int val){ return 0 == (val%2); });
	print_vector(lvec);

	std::cout << "=== USING STD::REMOVE ===\n";
	std::vector<int> lvec2{1,2,3,4,5,6,7,8,9,10,5,11,5,12,5};
	lvec2.erase(std::remove(lvec2.begin(), lvec2.end(), 5), lvec2.end());
	print_vector(lvec2);
	lvec2.erase(std::remove_if(lvec2.begin(), lvec2.end(), [](const int val){ return 0 == (val%2); }), lvec2.end());
	print_vector(lvec2);

	return 0;
}

/*********
 *	END OF FILE
 * *********/
