/****************
 *	This example demonstrates the use of GNU function attribues.
 *	For more info visit:
 *	Function attribues:	https://gcc.gnu.org/onlinedocs/gcc/Function-Attributes.html
 *	Variable attributes:	https://gcc.gnu.org/onlinedocs/gcc/Variable-Attributes.html
 *
 * *****************/

#include <iostream>
#include <string>

	__attribute__((const)) __attribute__((always_inline)) 
int getDouble(const int num) 
{
	return num*2;
}

	__attribute__((nonnull))
int showChar(char * pc) 
{
	std::cout << *pc << '\n';
	return 0;
}

int main() {
	int num = 5;
	int res = getDouble(num);
	int res2 = getDouble(num);
	std::cout << res << '\n';
	std::cout << res2 << '\n';

	char ch = 'A';
	char * pch = &ch;
	showChar(pch);
	pch = nullptr;
	showChar(pch);

	return 0;
}


/***************
 *	END OF FILE
 * ************/
