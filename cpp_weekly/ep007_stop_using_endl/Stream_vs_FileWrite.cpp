/************************************
 *
 *	This example demonstrate the performance cost of writiing to file directly vs.
 *	writing to file using stream.
 *
 * **********************************/

#include <iostream>
#include <fstream>
#include <sstream>

void write_to_stream(std::ostream & osf) {

	osf << "Writing to an output stream" << std::endl;
	return ;	
}

int main(int argc, char * argv[]) {
	std::ofstream osf("output_write_to_stream.txt", std::ios_base::trunc);

	// case - 01
	for(uint64_t i = 0; i < 1000000; ++i) {
		write_to_stream(osf);
	}

	// case - 02
	/*
	   for(uint64_t i = 0; i < 1000000; ++i) {
	   std::stringstream ss;
	   write_to_stream(ss);
	   osf << ss.str();
	   }
	   */
	if(osf.is_open()) {
		osf.close();
	}

	return 0;

}

/*****************
 *	EOF
 * ******************/
