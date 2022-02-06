/************
 *	This example demonstrates overloading in C by using generic selection.
 *	For more info visit tutorial video:
 *	https://en.cppreference.com/w/c/language/generic
 *
 * ****************/

#include <stdio.h>

#define my_square(num) _Generic((num), 	int: my_square_i, \
					double: my_square_d)(num)

int my_square_i(int num) {
	puts("int version");
	return num * num;
}

double my_square_d(double num) {
	puts("double version");
	return num * num;
}

int main() {
	printf("%d\n", my_square(5));
	printf("%f\n", my_square(1.1));

	return 0;
}



/*********
 *	END OF FILE
 * *******/
