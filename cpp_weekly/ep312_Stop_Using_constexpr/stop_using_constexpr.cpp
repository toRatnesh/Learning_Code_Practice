/***********
  This example demonstrates about how we might misuse 'constexpr' and that's why its use ahould be avoided

  For more info visit:
https://www.youtube.com/watch?v=4pKtPWcl1Go&list=PLs3KjaCtOwSZ2tbuV1hx8Xz-rFZTan2J1&index=313
 *********/

#include <array>

constexpr int getDoubleValue(int val) {
	return 2 * val;
}

constexpr std::array<int, 1000> getArrayValues() {
	std::array<int, 1000> arr{};
	int count = 0;
	for(auto & val : arr) {
		val = (count++) * 2;
	}
	return arr;
}

int main() {

	[[maybe_unused]] int res1 = getDoubleValue(2);           
	[[maybe_unused]] const int res2 = getDoubleValue(2);
	[[maybe_unused]] constexpr int res3 = getDoubleValue(2);

	/********
	  - GCC is very aggressive with constexpr
	  - LLVM is somewhere aggressive and lazy
	  - MSVC is lazy
	 *****/

	const int * iptr = nullptr;
	{
		[[maybe_unused]] constexpr auto larr = getArrayValues();    // use static to eliminate the problem of stack use after scope
		static_assert(10 == larr[5]);

		iptr = &larr[10];
	}

	return (*iptr);
}

/***
  END OF FILE
 ***/
