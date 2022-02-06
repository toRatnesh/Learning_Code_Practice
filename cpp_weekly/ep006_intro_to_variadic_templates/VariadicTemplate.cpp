
/*****************************************
 *
 *	This program demonstrates the use of variadic template
 *	Also check episode - 10
 *
 * **************************************/
#include <iostream>
#include <sstream>


template<typename T>
void x_print(const T & data_to_print) {
	
	std::ostringstream l_iss;
	l_iss << data_to_print;
	std::cout << l_iss.str() << '\n';

	return ;
}	

/*************************************************
 *        CASE 01 - BASIC VARIADIC TEMPLATE
 *
 *      ********************************************/

void variadic_template_print() {
	return ;
}

template<typename T, typename ... TV>
void variadic_template_print(const T & p1, const TV & ... params) {

	x_print(p1);

	variadic_template_print(params...);

	return ;
}

// *******************************************************/




/******************************************************
 *	CASE 02 - OPTIMIZED VARIADIC TEMPLATE 
 *
 *
 *	This causes infinite recersive call because it's uanble to create a boundary condition to stop the recursive call.
 *
 * **************************************************
template<typename T>
void variadic_template_print(const T & arg) {
	std::stringstream l_ss;
	l_ss << arg;
	std::cout << l_ss.str() << '\n';
	return ;
}

template<typename ... TV>
void variadic_template_print(const TV & ... params) {
	std::size_t l_size = sizeof...(params);
	std::cout << l_size << '\n';
	
	//variadic_template_print(params...);

	return ;
}


***********************************************/

int main() {

	std::cout << "=== SIMPLE TEMPLATE FUNCTION ===" << '\n';

	x_print("Learning variadic template");
	x_print('A');
	x_print(121);
	x_print(4.21);

	std::cout << "=== VARIADIC TEMPLATE FUNCTION ===" << '\n';
	variadic_template_print("Learning variadic template", 'A', 121, 4.21);

	return 0;
}

/************
 *	EOF
 * ********/

