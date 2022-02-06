/*************
 *
 * 	This example demonstrated the use of 
 * 	1. nesting multiple namespace in one line 
 * 	2. use of std::clamp() algorithm
 *
 * 	both of above features are available since c++17.
 *
 * ***************/

#include <iostream>
#include <algorithm>
namespace org::project::team {
	void printMsg() {
		std::cout << "namespace org::project::team" << '\n';
	}
}

int main() {
	org::project::team::printMsg();

	std::cout << R"(std::clamp(14, 10, 18) )" << std::clamp(14, 10, 18) << '\n';
	std::cout << R"(std::clamp(12, 13, 15) )" << std::clamp(12, 13, 15) << '\n';
	std::cout << R"(std::clamp(13, 13, 15) )" << std::clamp(13, 13, 15) << '\n';
	std::cout << R"(std::clamp(14, 13, 15) )" << std::clamp(14, 13, 15) << '\n';
	std::cout << R"(std::clamp(15, 13, 15) )" << std::clamp(15, 13, 15) << '\n';
	std::cout << R"(std::clamp(16, 13, 15) )" << std::clamp(16, 13, 15) << '\n';

	return 0;        
}

/***
 * 	END OF FILE
 * **/
