/************
 *	This example demonstrates the use of c++20 std::midpoint and std::lerp library features.
 *
 *	For more info visit:
 *	https://en.cppreference.com/w/cpp/numeric/midpoint
 *	https://en.cppreference.com/w/cpp/numeric/lerp
 *
 * ***********/

#include <iostream>
#include <numeric>
#include <cmath>

int main() {

	std::uint32_t a = std::numeric_limits<std::uint32_t>::max();
	std::uint32_t b = std::numeric_limits<std::uint32_t>::max() - 2;

	std::cout << "a: " << a << '\n'
		<< "b: " << b << '\n'
		<< "Incorrect (overflow and wrapping): " << (a + b) / 2 << '\n'
		<< "Correct: " << b + ((a-b)/2) << '\n'
		<< "Correct using midpoint: " << std::midpoint(a, b) << "\n\n";


	auto on_pointers = [](int i, int j) {
		char const* text = "0123456789ABCDEF";
		char const* p = text + i;
		char const* q = text + j;
		std::cout << "std::midpoint('" << *p << "', '" << *q << "'): '"
			<< *std::midpoint(p, q) << "'\n";
	};

	on_pointers(2, 4);
	on_pointers(5, 2);
	on_pointers(2, 6);
	on_pointers(2, 10);
	on_pointers(2, 11);
	on_pointers(2, 12);
	on_pointers(10, 15);
	std::cout << '\n';

	float m=10.0f, n=20.0f;
	std::cout << "m=" << m << ", " << "n=" << n << '\n'
		<< "mid point=" << std::lerp(m,n,0.5f) << '\n'
		<< std::boolalpha << (m == std::lerp(m,n,0.0f)) << ' '
		<< std::boolalpha << (n == std::lerp(m,n,1.0f)) << '\n';

	return 0;
}

/********
 *	END OF FILE
 * **********/
