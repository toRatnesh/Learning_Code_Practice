/*********
 *
 * 	This example demonstrates the use of std::invoke.
 * 	It is also like std::bind but invokes the callable immediately.
 *
 * *******/

#include <iostream>
#include <functional>
#include <memory>

void x_print(const int n, const std::string & msg) {
	std::cout << n << " -- " << msg << '\n';
	return;
}


template<typename T>
void tp_print(T t, const std::string & msg) {
	std::cout << t << " -- " << msg << '\n';
	return;
}

class CT {

	int m;
	std::string msg;
	public:
		CT(int n, std::string str) : m(n), msg(str) {	}
		void ct_print() {
			std::cout << m << " -- " << msg << '\n';
		}
};

int main() {

	auto fl = [](const int n, const std::string & msg) {
	        std::cout << n << " -- " << msg << '\n';
	};

	std::invoke(x_print, 13, "Learning invoke");
	std::invoke(fl, 17, "Learning invoking lambda");
	std::invoke(tp_print<std::string >, "Learning invoking lambda", "using template");
	std::invoke(tp_print<double>, 17.549, "Learning invoking lamda using template");
	std::invoke(tp_print<int>, 17.549, "Learning invoking lamda using template");

	CT ct(27, "Learning calling member function");
	std::invoke(&CT::ct_print, std::make_unique<CT>(ct));

	return 0;
}

/*******
 *	END OF FILE
 * ****/
