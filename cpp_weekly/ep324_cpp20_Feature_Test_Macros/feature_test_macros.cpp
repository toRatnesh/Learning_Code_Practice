/********
  This example demonstrates about use of cpp feature testing macros

  Feature testing (C++20)
  The standard defines a set of preprocessor macros 
  corresponding to C++ language and library features 
  introduced in C++11 or later. 
  They are intended as a simple and portable way 
  to detect the presence of said features.

  For more info visit:
https://en.cppreference.com/w/cpp/feature_test

 *******/

#include <iostream>
#include <cassert>

#ifdef __has_cpp_attribute                      // Check if __has_cpp_attribute is present
#   if __has_cpp_attribute(nodiscard)           // Check for an attribute
#       define NODISCARD_PRESENT true
#   else
#       define NODISCARD_PRESENT false
#   endif
#endif

#if __cpp_constexpr >= 201603L
#else
#endif

int main() {
	std::clog << std::boolalpha << "nodiscard present: " << NODISCARD_PRESENT << '\n'; 

	auto l = [](){return 5;};
	std::clog << "__cpp_constexpr : " << __cpp_constexpr << '\n';

#if (__cpp_constexpr >= 201603L) 
	std::clog << "lambda in constexpr context\n";
	static_assert(5 == l());
#else
	assert(5 == l());
#endif


	return 0;
}

/****
  END OF FILE
 ****/
