/**************
 *	This example demonstrates the use of GNU pure function attribute.
 *	pure:
 *	The pure attribute prohibits a function from modifying the state of the program that is 
 *	observable by means other than inspecting the function.s return value. 
 *	However, functions declared with the pure attribute can safely read any non-volatile objects, 
 *	and modify the value of objects in a way that does not affect their return value or the observable state of the program.
 *
 *
 * ***************/

#include <iostream>

//__attribute__ ((pure))
[[gnu::pure]]
[[nodiscard]] constexpr int get_square(const int num) noexcept
{
	return num*num;
}

int main() {
	int val1 = 10;
	int res = get_square(val1) + get_square(val1);
	std::cout << res << '\n';

	return 0;
}

/*****
 *	END OF FILE
 * ******/
