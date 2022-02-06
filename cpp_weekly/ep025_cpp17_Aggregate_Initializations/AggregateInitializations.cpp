/**********
 *	This example demonstarates the use of features available for aggregate initialization in c++ 17.
 *	For more detail check: https://en.cppreference.com/w/cpp/language/aggregate_initialization
 *
 * *********/

#include <iostream>
struct S {
	uint32_t m;
	uint32_t n;
	struct S_N {
		uint32_t m;
		uint32_t n;
	}s_n;
};
struct base1 {
	uint32_t m_b1;
};
struct base2 {
	uint32_t m_b21;
	uint32_t m_b22;
};
struct der :  base1,  base2 {
	uint32_t m_d;
};
int main() {
	S s {13, 17, {23, 27}};
	auto [x, y, z] = s;
	auto [z1, z2] = z;
	std::cout << x << ' ' << y << ' ' << z1 << ' ' << z2 << '\n';

	der d{ {11}, {21, 22}, 78 };
	// CE cannot decompose class type 'der': both it and its base class 'base1' have non-static data members
	//auto [p, q, r] = d;     

	//auto [q1, q2] = q;
	//std::cout << p << ' ' << q1 << ' ' << q2 << ' ' << r << '\n';

	return 0;
}

/****
 *	END OF FILE
 * ***/
