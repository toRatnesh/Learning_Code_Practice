/********************
 *	This example demonstrates the use of constexpre new supportd in c++20.
 *
 *	NOTE:
 *	we can allocate with new
 *	we must free allocated memory in the constexpr
 *	we must not access freed memory (UB)
 *
 *	For mroe info visit tutorial video:
 *	https://www.youtube.com/watch?v=FRTmkDiW5MM&list=PLs3KjaCtOwSZ2tbuV1hx8Xz-rFZTan2J1&index=189
 *
 * ****************/

#include <iostream>

constexpr auto get_ptr() {
	int * i_ptr = new int(13);
	return i_ptr;
}

constexpr auto release_ptr(auto ptr) {
	delete ptr;
	ptr = nullptr;
	return;
}

constexpr auto get_value() {
	auto lptr = get_ptr();
	auto res = *lptr;
	release_ptr(lptr);
	//auto res = *lptr;

	return res;
}

int main() {
	constexpr auto val = get_value();
	static_assert(13 == val);

	return 0;
}


/************
 *	END OF FILE
 * ********/
