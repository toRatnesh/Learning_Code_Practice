/**********
 *	This example demonstartes the nth fibinacci number generator using:
 *	1. Using Recusrsive method
 *	2. Using template metaprogramming  [Reuirement should be known at compile time]
 *	3. Using formula to calculate fibonacci number
 *	4. Use of template metaprogramming and recursive both
 *
 *	For more info check tutorial:
 *	https://www.youtube.com/watch?v=hErD6WGqPlA&list=PLs3KjaCtOwSZ2tbuV1hx8Xz-rFZTan2J1&index=13
 *
 * *************/

#include <iostream>
#include <cmath>

// Method-1 | using recursive function
// in this case performance decreases as we move away from 1st position to next position and so on
int fib_by_position(const int pos) {
	if(0 == pos) return 0;
	if(1 == pos) return 1;

	return fib_by_position(pos-1) + fib_by_position(pos-2);
}

// Method-2 | using template | in this case calculation is done at compile time
template<int I>
struct Fib_by_template {
	static const int val = Fib_by_template<I-1>::val + Fib_by_template<I-2>::val;
};

template<>
struct Fib_by_template<0> {
	static const int val = 0;
};
template<>
struct Fib_by_template<1> {
	static const int val = 1;
};

// Method-3 | using Binet's fibonacci number formula
int fib_by_formula(const int pos) {
	constexpr static auto sqrt_5 = std::sqrt(5);

	if(0 == pos) return 0;
	if(1 == pos) return 1;

	auto res = (std::pow(1+sqrt_5, pos) - std::pow(1-sqrt_5, pos)) / (std::pow(2, pos) * sqrt_5);
	return static_cast<int>(res);
}

int main() {
	std::cout << fib_by_position(10) << '\n';   // 10th number is fibonacci series
	std::cout << Fib_by_template<45>::val << '\n'; // using tempalte calculation is done at compile time
	std::cout << fib_by_formula(45) << '\n';   
	return 0;
}

/********
 *	END OF FILE
 * ******/
