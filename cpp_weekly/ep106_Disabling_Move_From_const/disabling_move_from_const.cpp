/*************
 *	
 *	This example demonstrates how to diable move from const.
 *	Move from const can be achieved by deleting following two functions:
 *	St(const St && ) = delete; // delete construction using move from const
 *	St& operator=(const St &&) = delete; // delete assignment using move from const
 *
 * ****************/

#include <iostream>

struct St {
	int data = 13;

	St() { std::puts("constructor"); }
	St(int m) : data(m) { std::puts("parameterized constructor"); }

	St(const St & ) { std::puts("copy constructor"); }
	St(St && ) { std::puts("move constructor"); }
	St(const St && ) = delete; // delete construction using move from const

	St& operator=(const St & )  { std::puts("copy assignment"); return *this; }
	St& operator=(St &&) { std::puts("move assignment"); return *this; }
	St& operator=(const St &&) = delete; // delete assignment using move from const

	~St() { std::puts("destructor"); }
};

int main() {
	const St cs(3);

	// error: use of deleted function 'St::St(const St&&)'
	// in absence of 'St::St(const St&&)' it will use copy constructor
	// St s2 = std::move(cs);

	St s3;
	// error: use of deleted function 'St& St::operator=(const St&&)'
	// in absence of 'St& St::operator=(const St&&)' this will use move assignment
	//s3 = std::move(cs);

	return 0;
}


/************
 *	END OF FILE
 * ********/
