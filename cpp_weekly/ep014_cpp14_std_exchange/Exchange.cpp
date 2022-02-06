/************************************
 *
 * 	This example demonstrate the use od std::exchange
 * 	and how it may also be used to swap two values
 *
 * *********************************/

#include <iostream>
#include <utility>

int main() {

	int p = 4;
	int temp = 0;
	std::cout << "Before: " << '\n';
	std::cout << "p: " << p << '\n';
	std::cout << "temp: " << temp << '\n';
	temp = std::exchange(p, 9);
	std::cout << "After: " << '\n';
	std::cout << "p: " << p << '\n';
	std::cout << "temp: " << temp << '\n';
	std::cout << '\n';

	int x = 5;
	int y = 7;
	std::cout << "Before: " << '\n';
	std::cout << "x: " << x << '\n';
	std::cout << "y: " << y << '\n';
	y = std::exchange(x, y);
	std::cout << "After: " << '\n';
	std::cout << "x: " << x << '\n';
	std::cout << "y: " << y << '\n';
	std::cout << '\n';

	/*
	int * ptr = NULL;
	ptr = (int*)malloc(sizeof(int) * 1);
	if(ptr)		*ptr = 77;
	std::cout << *ptr << '\n';
	if(ptr)		free(std::exchange(ptr, NULL));
	if(!ptr)	std::cout << "Pointer is NULL" << '\n';
	*/

	int * ptr = nullptr;
	ptr = new int;
	if(ptr) *ptr = 87;
	std::cout << *ptr << '\n';
	if(ptr) 	delete std::exchange(ptr, nullptr);
	if(!ptr)		std::cout << "Pointer is now free" << '\n';

	return 0;
}

/**************
 *	EOF
 * ***********/
