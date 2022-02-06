/****************
 *	This example demonstrates the use of reference to pointer.
 *	reference to pointer is confusing and we should avoid its use.
 *
 *	You may experiment with this program.
 *
 *	To check meaning of your declaration visit:
 *	https://cdecl.org/
 *
 * ********************/

#include <iostream>


int main() {
	int val1 = 13;
	int val2 = 76;
	std::cout << "val1: " << val1 << " val2: " << val2 << '\n';

	// pointers
	std::cout << "=== pointer ===\n";
	int * iptr;     // no initializer
	iptr = &val1;
	std::cout << "val1: " << val1 << " val2: " << val2 << " *iptr: " << *iptr << '\n';
	*iptr = 34;
	std::cout << "val1: " << val1 << " val2: " << val2 << " *iptr: " << *iptr << '\n';
	iptr = &val2;   // now points to val2
	std::cout << "val1: " << val1 << " val2: " << val2 << " *iptr: " << *iptr << '\n';

	val1 = 13; 
	val2 = 76;
	// refernces
	std::cout << "=== reference ===\n";
	//int & iref;   // error: declaration of reference variable 'iref' requires an initializer
	int & iref = val1;
	std::cout << "val1: " << val1 << " val2: " << val2 << " iref: " << iref << '\n';
	iref = 34;
	std::cout << "val1: " << val1 << " val2: " << val2 << " iref: " << iref << '\n';
	iref = val2;    // does not points to val2 only assigns value of val2
	std::cout << "val1: " << val1 << " val2: " << val2 << " iref: " << iref << '\n';

	val1 = 13;
	val2 = 76;
	// refernce to pointer
	std::cout << "=== reference to pointer ===\n";
	int * ptr2 = &val1;
	int * & ref_iptr = ptr2;
	std::cout << "val1: " << val1 << " val2: " << val2 << " *ref_iptr: " << *ref_iptr << '\n';
	ref_iptr = &val2;
	std::cout << "val1: " << val1 << " val2: " << val2 << " *ref_iptr: " << *ref_iptr << '\n';

	return 0;
}

/***********
 *	END OF FILE
 * **********/
