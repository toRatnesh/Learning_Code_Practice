/***************
  This example demonstrates about forwarding references template parameter

  While forwarding reference parameters generates multiple instantiation 
  for const, non-const and rvalue,
  template function with const reference generates only one instantiation

 ****************/

#include <iostream>

template<typename T>
auto fun_const_reference(const T & t) {
	return t*2;
}

template<typename T>
auto fun_forwarding_reference(T && t) {
	return t*2;
}

int main() {

	int i = 5;
	const int ci = 7;

	fun_forwarding_reference(i);
	fun_forwarding_reference(ci);
	fun_forwarding_reference(9);

	fun_const_reference(i);
	fun_const_reference(ci);
	fun_const_reference(9);

	return 0;
}

/*******
  END OF FILE
 *****/

