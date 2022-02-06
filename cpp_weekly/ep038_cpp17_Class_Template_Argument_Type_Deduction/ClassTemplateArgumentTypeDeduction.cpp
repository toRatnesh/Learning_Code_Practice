/**************
 *	C++17's Class Template Argument Type Deduction
 *
 * 	NOTE:			
 * 	// this was menioned in the episode on youtube, but at the time of compilation behavior was different
 *	There is no deduction guide for user declared constructor. We need to use deduction guides for this.
 *	For more info regarding deduction guides check episode 039 deduction guides.
 *
 * ********/

#include <iostream>
#include <tuple>
#include <vector>
#include <string>
#include <functional>

void testDeduction () {
}

int main() {
	const std::tuple<int, std::string> ltp1{1, "tuple-1"};
	const auto  ltp2 = std::make_tuple(1, "tuple-2");
	const std::tuple  ltp3(3, "tuple");                 // c++17

	const std::vector<int> lv1{1,2,3,4,5};
	const std::vector lv2{1,2,3,4,5};                   // c++17


	std::function fb(&testDeduction);

	return 0;
}

/****
 *	END OF FILE
 * *****/
