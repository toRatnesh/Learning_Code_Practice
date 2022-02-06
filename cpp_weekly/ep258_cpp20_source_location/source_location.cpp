/**************
  This example demonstrates about use of C++20 std::source_location.

  The source_location class represents certain information about the source code, such as file names, line numbers, and function names. Previously, functions that desire to obtain this information about the call site (for logging, testing, or debugging purposes) must use macros so that predefined macros like __LINE__ and __FILE__ are expanded in the context of the caller. The source_location class provides a better alternative.

  For more info visit:
https://en.cppreference.com/w/cpp/utility/source_location

 ************/

#include <iostream>
#include <string_view>
#include <source_location>

void log(const std::string_view message,
		 const std::source_location location = 
		 std::source_location::current())
{
	std::clog << "["
		<< location.file_name() << " "
		<< location.line() << " "
		<< location.column() << " "
		<< location.function_name() << "] : "
		<< message << '\n';
}

template <typename T> 
void fun(T x) {
	log(x);
}

int main(int, char*[]) {
	log("Hello world!");
	fun("Hello C++20!");
	return 0;
}


/*********
  END OF FILE
 ********/
