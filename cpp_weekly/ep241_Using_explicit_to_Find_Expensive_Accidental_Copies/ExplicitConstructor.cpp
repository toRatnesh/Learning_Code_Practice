/*******
 *
 * 	This example demonstrates the use of explicit to find accidental expensive copy.
 *
 * 	Behaviour will be different in c++11 and c++17.
 * 	For more info visit:
 * 	https://www.youtube.com/watch?v=5wJ-jKK_Zy0&list=PLs3KjaCtOwSZ2tbuV1hx8Xz-rFZTan2J1&index=243
 *
 *
 * ******/

#include <utility>

struct S {
	S() = default;
	explicit S(const S & s) { }
	S(S &&) = default;

};

void func(S arg_s) {}

int main() {
	S s;

	// error: no matching function for call to 'S::S(S&)'
	//func(s);        // error for explicit copy constructor

	func(S(s));         // calls explicit copy constructor 
	func(S{});

	func(std::move(s));

	return 0;
}
/*****
 *	END OF FILE
 * *****/
