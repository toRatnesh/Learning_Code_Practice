/*******
 * 	This examplde will demonstrate the use of CPP-17 [[fallthrough]] attribute. 
 * 	Indicates that the fall through from the previous case label is intentional and 
 * 	should not be diagnosed by a compiler that warns on fallthrough.
 *
 ***********/

#include <iostream>

int fun_1() { std::cout << "Inside fun_1\n"; return 0; }
int fun_2() { std::cout << "Inside fun_2\n"; return 0; }
int fun_3() { std::cout << "Inside fun_3\n"; return 0; }

int main() {
	int i = 2;
	switch(i) {
		case 1:
			fun_1();
			break;
		case 2:
			fun_2();
			[[fallthrough]];

			// warning: attribute 'fallthrough' not preceding a case label or default label
			// break;       // break after fallthrough will result in compiler warning
		case 3:
			fun_3();
			break;
		case 4: [[fallthrough]];
		case 5: [[fallthrough]];
		case 6:
			std::cout << "case 4, 5 and 6 \n";
			break;
		default:
			std::cout << "default case \n";
	}
	return 0;
}

/********
 * END OF FILE 
 * *********/
