/*************
 *	This example demonstrates the impact of integer conversion on performance.
 *	Suggestion:	Avoid code which results in integer type conversion to improve performance
 *
 *	For more info visit:
 *	Tutorial:	https://www.youtube.com/watch?v=jKpIZ4UcaNw&list=PLs3KjaCtOwSZ2tbuV1hx8Xz-rFZTan2J1&index=278
 *
 ************/

#include <iostream>
#include <vector>

int main() {
	std::vector<uint32_t> lv{1,3,5,7,9,11};

	// integer type conversion (compiler may generate warning for this)
	for(int i = 0; i < lv.size(); i++) {
		std::cout << lv[i] << ' ';
	}
	std::cout << '\n';

	// no integer type conversion
	for(std::vector<uint32_t>::size_type i = 0; i < lv.size(); i++) {
		std::cout << lv[i] << ' ';
	}
	std::cout << '\n';

	return 0;
}

/*******
 *	END OF FILE
 ********/
