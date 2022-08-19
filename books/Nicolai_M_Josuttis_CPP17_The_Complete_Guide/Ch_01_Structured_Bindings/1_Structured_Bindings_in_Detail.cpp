/********
Reference:  C++17 - The Complete Guide | Nicolai M. Josuttis

Structured Bindings
Structured bindings allow you to initialize multiple entities by the elements or members of an object.

1.1 Structured Bindings in Detail

Important Points:
1. 
There is a new anonymous variable involved. 
The new names introduced as structure bindings refer to members/elements of this anonymous variable.

2.
The qualifiers apply to the new anonymous entity. 
They don.t necessarily apply to the new names introduced as structured bindings.

For the same reason, structured bindings do not decay2 although auto is used.
This also makes a difference when specifying an alignment.

 **********/

#include <iostream>
#include <type_traits>

struct S {
	int m = 1;
	const int n = 7;
	std::string msg{};
};

int main() {

	int val = 7;
	const auto & refval = val;
	auto val2 = refval;
	static_assert(std::is_same_v<decltype(val), int>);
	static_assert(std::is_same_v<decltype(refval), const int &>);
	static_assert(std::is_same_v<decltype(val2), int>);

	S s1;
	const auto & [m, n, s] = s1;
	const auto m2 = m;
	static_assert(std::is_same_v<decltype(m), const int>);
	static_assert(std::is_same_v<decltype(n), const int>);
	static_assert(std::is_same_v<decltype(s), const std::string>);
	static_assert(std::is_same_v<decltype(m2), const int>); // no type decay like val2 above

	return 0;
}

/*****
  END OF FILE
 ******/
