/***********
 *	In this tutorial Jason talks about how cppCheck and clag-tidy suggest us to improve our code by 
 *	changing them as static, const and so on.
 *
 *	He also talks about advantage of constexpr.
 *
 * ***********/
#include <iostream>

struct St {
	int data = 23;
	static int st_data;

	// in C++11 : error: 'int St::fun() const' cannot be overloaded with 'constexpr int St::fun() const'
	// NOTE: 'constexpr' non-static member function will not be implicitly 'const' in C++14
	constexpr int fun() {
		return ++data;
	}

	// const fun becoz it does not modify any data member
	constexpr int fun() const {        
		//return ++data; // error: increment of member 'St::data' in read-only object
		return data;
	}

	// static fun becoz it does not use any non-static data member
	static int static_fun() {
		//return data; // error: invalid use of member 'St::data' in static member function
		return ++st_data;
	}
};

int St::st_data = 13;

int main() {
	St s;
	std::cout << s.fun() << '\n';

	const St s2;
	std::cout << s2.fun() << '\n';

	std::cout << St::static_fun() << '\n';
	// static member func can be call with object also
	std::cout << s.static_fun() << '\n';     
	std::cout << s2.static_fun() << '\n';

	return 0;
}

/*******
 *	END OF FILE
 * *******/
