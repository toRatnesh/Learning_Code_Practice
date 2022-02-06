/***********
 *
 *	This example demonstrates how reinterpret_cast may lead to undefined behavior and how to avoid that using memcpy.
 *	It also explains about c++20 bit_cast.
 *	
 *	For more info visit:
 *	https://en.cppreference.com/w/cpp/numeric/bit_cast
 * ***************/

#include <iostream>
#include <string.h>

struct St {
	int i;
	int j;
};


void update_data(char * blob, const int new_val) {
	reinterpret_cast<St *>(blob)[2].j = new_val;
}

void update_data_ub(char * blob, const int new_val) {
	St obj[3];
	memcpy(&obj, blob, sizeof(obj));
	obj[2].j = new_val;
	memcpy(blob, obj, sizeof(obj));

	// std::bit_cast c++20
}

int main() {

	return 0;
}


/*****
 *	END OF FILE
 * *******/
