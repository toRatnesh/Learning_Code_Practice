/*************
  This example demonstrates about the use of Lambdas in C++

  For more info visit:
https://www.youtube.com/watch?v=BvlKet2ykco
cpp weekly episodes about lambda
 ***************/

#include <iostream>

int main() {  
	int i = 25;
	[&] {std::cout << i << '\n';}();
	return 0;
}

/*******
  END OF FILE
 *******/
