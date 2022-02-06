/**********
 *	This exmaple demonstrates what a lambda can capture and what could we do with that.
 *
 *	For more info visit tutorial:
 *	https://www.youtube.com/watch?v=9L9uSHrJA08&list=PLs3KjaCtOwSZ2tbuV1hx8Xz-rFZTan2J1&index=128
 *
 * ************/

#include <iostream>

int main() {
	const auto lbd = 
		[
			cap_val = []() {
				struct St {
					int val = 13; 
					St() { std::puts("default constructor"); }
					St(const St& arg) : val(arg.val) { std::puts("copy constructor"); }
					~St() { std::puts("destructor"); }
				};
				return St{};
			}      // lambda in capture list 
		]() { 
			return cap_val; // this will return captured lambda
		};

	std::cout << lbd()().val << '\n'; // lbd() will return a lambda

	return 0;
}

/***********
 *	END OF FILE
 * **********/
