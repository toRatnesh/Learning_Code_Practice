/**********
 *	In this tutorial Jason talks about how an analyzer may suggest to use constexpr and noexcept and other specifiers
 *	to improve our code.
 *
 *	For more info visit tutorial video:
 *	https://www.youtube.com/watch?v=1FAcPvb0ZjU&list=PLs3KjaCtOwSZ2tbuV1hx8Xz-rFZTan2J1&index=146
 *
 * ***********/

#include <iostream>

// int get_square(const int num)
[[nodiscard]] constexpr int get_square(const int num)  noexcept
{
	return num*num;
}

// int get_sum(const int num1, const int num2)
[[nodiscard]] constexpr int get_sum(const int num1, const int num2) noexcept
{
	return num1 + num2;
}

int main() {
	int val1 = 10;
	int val2 = 23;
	int res_sum = get_sum(val1, get_square(val2));
	std::cout << res_sum << '\n';

	return 0;
}

/*********
 *	END OF FILE
 * *********/
