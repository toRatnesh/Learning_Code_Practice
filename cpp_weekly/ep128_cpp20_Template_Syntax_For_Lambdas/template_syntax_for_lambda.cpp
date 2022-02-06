/***********
 *	This example demonstrates the use of cpp20 template syntax for lambda.	
 *
 * ***********/
#include <iostream>

struct St {
	int val = 5;
};

int main() {

	const auto lbd = []<typename T>(T targ){ return targ;};
	const auto lbd2 = []<typename T, typename U>(T targ, U uarg){ std::cout << targ << ' ' << uarg << '\n'; return 0; };

	std::cout << lbd(2) << '\n';
	std::cout << lbd("sample string") << '\n';
	std::cout << lbd(St{5}).val << '\n';
	std::cout << '\n';

	std::cout << lbd2(13, R"(another sample string)") << '\n';

	return 0;
}

/********
 *	END OF FILE
 * *****/
