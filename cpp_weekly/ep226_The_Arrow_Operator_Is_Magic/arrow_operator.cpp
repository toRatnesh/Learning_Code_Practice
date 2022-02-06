/***********
 *	This example demonstrates the use of overloaded arrow operator ->.
 *
 *	For more info visit:
 *	https://www.youtube.com/watch?v=mAHHKDyLmCI&list=PLs3KjaCtOwSZ2tbuV1hx8Xz-rFZTan2J1&index=228
 * **********/

#include <iostream>
#include <string>

struct T_Pointer {
	std::string * ptr;

	auto * operator->() {
		std::puts("overloaded operator->");
		return ptr;
	}

	auto * operator->() const {
		std::puts("const overloaded operator->");
		return ptr;
	}

};

int main() {
	std::string lstr = "sample string";

	T_Pointer tp{&lstr};
	std::cout << tp->size() << '\n';
	std::cout << tp->data() << '\n';
	std::cout << tp.operator->()->size() << '\n';
	std::cout << tp.operator->()->data() << '\n';
	std::cout << '\n';

	const T_Pointer tp2{&lstr};
	std::cout << tp2->size() << '\n';
	std::cout << tp2->data() << '\n';
	std::cout << tp2.operator->()->size() << '\n';
	std::cout << tp2.operator->()->data() << '\n';

	return 0;
}

/**********
 *	END OF FILE
 * **********/
