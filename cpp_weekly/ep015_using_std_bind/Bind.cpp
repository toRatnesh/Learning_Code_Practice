/*******************************
 *	Bind 
 *
 * ****************************/

#include <iostream>
#include <string>
#include <functional>
#include <memory>

template<typename T1, typename T2> 
void tp_print(T1 t1, T2 t2) {
	std::cout << t1 << ' ' << t2 << '\n';
	return;
}

void x_print(const int arg1, const std::string & arg2) {

	std::cout << arg1 << " -- " << arg2 << '\n';
	return;	
}

int x_print_02(const int arg1) {
	std::cout << arg1 << '\n';
	return arg1;
}

struct ST {
	int m;
	int n;
	int x_multiply() {return m*n;}
};

class CT {
	private:
		int m;
		int n;
	public:
		CT(int a, int b) : m(a), n(b) {}
		int x_multiply() {return m*n;}
		int get_m() {return m;}
		int get_n() {return n;}
};

int main() {
	std::string l_str = "Learning bind";
	const auto fb_01 = std::bind(x_print, 1, l_str);
	const auto fb_02 = std::bind(x_print, 1, std::cref(l_str));
	fb_01();
	fb_02("This is ignored");	// Swallow extra arguments
	std::cout << '\n';

	l_str = "Learning bind modified";
	fb_01();
	fb_02();
	std::cout << '\n';

	fb_01(1, 25);

	const auto fb_03 = std::bind(tp_print<double, std::string>, 3.15, "Learning bind using template");
	fb_03();
	std::cout << '\n';

	//const auto fb_04 = std::bind(x_print, 13);	// CE: static assertion failed: Wrong number of arguments for function	
	//fb_04();					// CE: no match for call to

	const auto fb_05 = std::bind(x_print, std::bind(x_print_02, 13), l_str);
	fb_05();
	std::cout << '\n';

	ST l_st {7, 4};
	const auto fb_06 = std::bind(&ST::x_multiply, std::make_unique<ST>(l_st));
	std::cout << fb_06() << '\n';

	const auto fb_07 = std::bind(&ST::m, std::make_unique<ST>(l_st));
	std::cout << fb_07() << '\n';
	std::cout << '\n';

	CT l_ct(3, 6);
	const auto fb_08 = std::bind(&CT::x_multiply, std::make_unique<CT>(l_ct));
	std::cout << fb_08() << '\n';

	const auto fb_09 = std::bind(&CT::get_m, std::make_unique<CT>(l_ct));
	std::cout << fb_09() << '\n';

	return 0;
}

/*************
 *	EOF
 * ***********/
