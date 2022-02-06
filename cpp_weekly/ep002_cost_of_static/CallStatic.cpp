/***************************************
 *	This example is to show how calling a static member cost performance than calling non-static member.
 *
 *	NOTE:
 *	since C++11 static memebers are initialized in thread-safe manner
 *
 *	Reference:
 *	https://en.cppreference.com/w/cpp/language/storage_duration#Static_local_variables
 *
 * ***************************************/

#include <iostream>
#include <string>

struct TestStatic {

	static const std::string & get_static() {
		static const std::string str = "Static string";
		return str;
	}

	const std::string & str = get_static();

	const std::string & get_string_ref() {
		return str;
	}

};

int main() {
	/*
	   TestStatic::get_static().size();
	   TestStatic::get_static().size();
	   TestStatic::get_static().size();
	   TestStatic::get_static().size();
	   return TestStatic::get_static().size();
	   */

	TestStatic t;

	size_t totalSize = 0;
	for(size_t i = 0; i < 100000; ++i) {
		totalSize += (t.get_string_ref().size() + i);
	}

	fprintf(stdout, "total size : %zu\n", totalSize);


	t.get_string_ref().size();
	t.get_string_ref().size();
	t.get_string_ref().size();
	t.get_string_ref().size();
	return t.get_string_ref().size();

}


/*******
 *	END OF FILE
 * ******/
