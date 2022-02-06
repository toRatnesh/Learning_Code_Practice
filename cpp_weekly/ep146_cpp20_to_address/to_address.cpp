/************
 *	This examplde demonstrates the use of std::to_address.
 *	std::to_address
 *	Obtain the address represented by p without forming a reference to the object pointed to by p.
 *
 *	For more info visit:
 *	https://en.cppreference.com/w/cpp/memory/to_address
 *
 * ***********/

#include <iostream>
#include <memory>
#include <vector>

int main() {

	const auto lbd = [](const auto & ptr) {
		std::cout << std::to_address(ptr) << '\n';
	}; 

	int val1 = 10;
	int val2 = 12;
	auto iuptr1 = std::make_unique<int>(14);
	auto iuptr2 = std::make_unique<int>(16);
	std::vector lvec = {18, 20, 22, 24};

	lbd(&val1);
	lbd(&val2);
	lbd(iuptr1);
	lbd(iuptr2);
	lbd(lvec.begin());
	lbd(lvec.begin() + 1);
	lbd(lvec.end());

	return 0;
}

/********
 *	END OF FILE
 * ********/
