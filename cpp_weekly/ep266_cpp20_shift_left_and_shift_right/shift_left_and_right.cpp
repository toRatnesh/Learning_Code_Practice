/************
 *	This example demonstrates about the use of shift_left and shift_right algorithm.
 *	
 *	Shifts the elements in the range [first, last) by n positions.
 *
 *	For more info visit:
 *	https://en.cppreference.com/w/cpp/algorithm/shift
 *
 * ***********/

#include <iostream>
#include <vector>
#include <algorithm>

void display_vector(const auto fp_vector) {
		for(const auto elem : fp_vector) {
				std::cout << elem << ' ';
		}
		std::cout << '\n';
}

int main() {
		std::vector<int> lv {1,2,3,4,5,6,7};


		// NOTE : Elements moved from will be in unspecified state
		std::shift_left(lv.begin(), lv.end(), 0);   display_vector(lv);
		std::shift_left(lv.begin(), lv.end(), 7);   display_vector(lv);
		std::shift_left(lv.begin(), lv.end(), 2);   display_vector(lv);
		std::cout << '\n';
		std::shift_right(lv.begin(), lv.end(), 0);   display_vector(lv);
		std::shift_right(lv.begin(), lv.end(), 7);   display_vector(lv);
		std::shift_right(lv.begin(), lv.end(), 1);   display_vector(lv);

		return 0;
}


/********
 *	END OF FILE
 * *****/
