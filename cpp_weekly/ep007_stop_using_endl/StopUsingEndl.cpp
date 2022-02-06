/************************************
 *
 *	This example demonstrate the performance cost of using std::endl
 *
 *	NOTE:
 *	std::endl inserts a newline character into the output sequence os and flushes it as if by calling 
 *	os.put(os.widen('\n')) followed by os.flush().
 *
 *	This is an output-only I/O manipulator, it may be called with an expression such as out << std::endl 
 *	for any out of type std::basic_ostream.
 *
 *	Reference:	https://en.cppreference.com/w/cpp/io/manip/endl			
 *
 * **********************************/

#include <iostream>
#include <fstream>

void write_to_ofstream(std::ofstream & osf, const std::string & msg) {
	if(osf.is_open()) {
		osf << msg << std::endl;	// case - 01
		//osf << msg << "\n";		// case - 02
		//osf << msg << '\n';		// case - 03
	}

}

int main(int argc, char * argv[]) {
	std::ofstream osf("osf_stop_using_endl.txt", std::ios_base::trunc);
	for(uint64_t i = 0; i < 1000000; ++i) {
		write_to_ofstream(osf, "Stop using endl");
	}

	if(osf.is_open()) {
		osf.close();
	}

	return 0;

}

/*****************
 *	EOF
 * ******************/
