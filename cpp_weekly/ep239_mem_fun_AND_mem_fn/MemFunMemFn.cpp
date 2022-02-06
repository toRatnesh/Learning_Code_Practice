/******************
 *
 * 	This example demonstrates the use of mem_fun and mem_fn.
 * 	Both are used to careate member function wrapper object
 *
 * 	mem_fun is deprecaed in c++11 and removed in c++17
 * 	Possible rason for this could be because unary_functiona and binary_function were deprecated in c++11 and removed in c++17. So similar action were taken with mem_fun because it's return type mem_fun_t and mem_fun1_t are inheritaed from unary_functiona and binary_function.
 *
 * 	Limitation of mem_fun:
 * 		It can be used for only those member funcitona which takes only one argument.
 *
 *
 * 	mem_fn comes over both limitations of return type and no of arguments to member function.
 *
 * 	STUDY THE DIFF:
 * 	std::mem_fn vs std::bind vs std::invoke vs lambda
 *
 * 	For more info visit:
 * 	https://en.cppreference.com/w/cpp/utility/functional/mem_fn
 * 	https://en.cppreference.com/w/cpp/utility/functional/mem_fun
 *
 * *****************/

#include <iostream>
#include <functional>
using namespace std;


void printNonMember() {
	cout << "This is non member function" << '\n';
}

class Test {
	int m;
	std::string msg;

	public:
	Test(const int n, const string a_msg) : m(n), msg(a_msg) {
		// constructor
	}
	void set(const int n, const string a_msg) {
		m = n; msg = a_msg;
	}

	void printData() {
		cout << m << ' ' << msg << '\n';
	}
};

int main() {
	// mem_fun or mem_fn can not be used to call non-member function
	//auto lmf_nonmem = std::mem_fn(&printNonMember);	// error: no matching function for call to 'mem_fn(void (*)())'

	Test t(13, "Val is 13");
	// this creates compilation error because mem_fun is used for only one argument
	//auto lmf_set = std::mem_fun(&Test::set);        // error: no matching function for call to 'mem_fun(void (Test::*)(int, std::string))'
	//auto lmf_prt = std::mem_fun(&Test::printData);
	auto lmf_set = std::mem_fn(&Test::set);        
	auto lmf_prt = std::mem_fn(&Test::printData);
	lmf_prt(&t);

	lmf_set(&t, 11, "Val is 11");
	lmf_prt(&t);
	
	return 0;
}
/*********
 *	END OF FILE
 * ********/
