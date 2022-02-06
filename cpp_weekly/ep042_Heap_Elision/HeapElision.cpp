/*****
 *	HEAP ELISION:
 *		This example demonstrates the heap elision feature.
 *
 *		Optimizer optimize heap space in case they find that a variale has been allocated space but 
 *		they have never been used furhther.
 *
 *		This optimization depends on the compiler used and lib used to compile the program.
 *
 *
 *		Drawback:
 *			This may hide the memory leak in program.
 *
 *
 *		Compile this program with different compiler and lib and check the generated assembly code to check the behavior.
 *
 *		For more information check tutorial video:
 *			https://www.youtube.com/watch?v=FWD1msG8YU4&list=PLs3KjaCtOwSZ2tbuV1hx8Xz-rFZTan2J1&index=44&t=31s
 *
 *
 * ****/

int main() {
	int * p = new int(5);
	delete p;
	return 0;
}

/*****
 *	END OF FILE
 * *****/
