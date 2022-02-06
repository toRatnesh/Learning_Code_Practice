/**************************************
 *
 * 	This example demonstrate the use of std::any 
 *
 * ***********************************/

#include <iostream>
#include <string>
#include <vector>
#include <any>
#include <typeinfo>

struct St{
	St(const St & orig) = default;
	St() = default;
};

int main(int argc, char * argv[]) {

	using namespace std::string_literals;

	//std::vector<std::any> v{13, 17.58, 'A', "Learning std any"s};
	std::vector<std::any> v{13, 17.58, 'A', "Learning std any"s, St()};
	try {
		std::cout << "v[0]: " << std::any_cast<int>(v[0]) << '\n';
		std::cout << "v[1]: " << std::any_cast<double>(v[1]) << '\n';
		std::cout << "v[2]: " << std::any_cast<char>(v[2]) << '\n';
		std::cout << "v[3]: " << std::any_cast<std::string>(v[3]) << '\n';
	}
	catch(const std::exception & e) {
		std::cout << "Exception: " << e.what() << std::endl;
	}

	return 0;
}

/***********
 *	EOF
 * ********/

