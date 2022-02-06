/**********
 *	This tutorial demonstrates the optimization of code using gcc and clang.
 *	This example shows that a small code may be more efficient than a large and bulky code.
 *
 *	For more info check:
 *	Tutorial:	https://www.youtube.com/watch?v=yRKRqzekLU4&list=PLs3KjaCtOwSZ2tbuV1hx8Xz-rFZTan2J1&index=60
 *	Comparison of assembly generated from gcc and clang:	https://gcc.godbolt.org/z/4xc98c
 *
 * ***************/

int xsum(const int count) {
	int result = 0;
	for(int i = 0; i <= count; ++i) {
		result += i;
	}
	return result;
}

int main() {
	return 0;
}

/********
 *	END OF FILE
 * *******/

