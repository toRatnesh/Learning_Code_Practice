/*****************
 *	This example demonstrates the use of default member initializer.
 * 	Compare assembly code in different scenario with and wothout optimization.
 *
 * ****************/

struct S {
	int val = 5;
};

/*
   struct S {
   int val;
   S(int m) : val(m) {}
   };
   */
int main() {
	S s;     // CASE - 1
	//S s(5);
	return s.val;
}

/*****
 *	END OF FILE
 * *****/
