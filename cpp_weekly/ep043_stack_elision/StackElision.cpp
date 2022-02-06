/********
 *	STACK ELISION:
 *		This example demonstrates the stack elision (madeup name) feature.
 *		In this case compiler optimizes the stack and unused variables dissapear from stack.
 *
 *		For more information check tutorial video:
 *			https://www.youtube.com/watch?v=5e3m2cppQ6M&list=PLs3KjaCtOwSZ2tbuV1hx8Xz-rFZTan2J1&index=45
 *
 * *******/

int main() {
	int arr[1000000];
	arr[0]		= 5;
	arr[1000]	= 50;
	arr[1000000]	= 50;
	return arr[0] +  arr[1000] + arr[1000000];
}


/*****
 *	END OF FILE
 * ****/
