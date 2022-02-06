/*********

  This example demonstrates about c++20 feature of starts_with and ends_with of string and string_view.

  For more info visit:
https://en.cppreference.com/w/cpp/string/basic_string/starts_with
https://en.cppreference.com/w/cpp/string/basic_string/ends_with

https://en.cppreference.com/w/cpp/string/basic_string_view/starts_with
https://en.cppreference.com/w/cpp/string/basic_string_view/ends_with

 *********/

#include <iostream>
#include <string>
#include <string_view>

template <typename PrefixType>
void test_prefix_print(const std::string& str, PrefixType prefix) {
	std::clog << '\'' << str << "' starts with '" << prefix << "'   : " << str.starts_with(prefix) << '\n';
}

template <typename SuffixType>
void test_suffix_print(const std::string& str, SuffixType suffix) {
	std::clog << '\'' << str << "' ends with '" << suffix << "': " << str.ends_with(suffix) << '\n';
}

int main() {
	std::boolalpha(std::cout);
	const std::string lstr = "Learning new feautres of string";
	test_prefix_print(lstr, std::string_view("Learning"));
	test_prefix_print(lstr, "Learning");
	test_prefix_print(lstr, 'L');
	test_prefix_print(lstr, std::string_view("Donotexist"));
	test_prefix_print(lstr, "Donotexist");
	test_prefix_print(lstr, 'D');
	std::clog << '\n';

	test_suffix_print(lstr, std::string_view("string"));
	test_suffix_print(lstr, "string");
	test_suffix_print(lstr, 's');
	test_suffix_print(lstr, std::string_view("Donotexist"));
	test_suffix_print(lstr, "Donotexist");
	test_suffix_print(lstr, 'D');  
	std::clog << "------------------------\n\n";

	const std::string lstr_view = "Learning new feautres of string";
	test_prefix_print(lstr_view, std::string_view("Learning"));
	test_prefix_print(lstr_view, "Learning");
	test_prefix_print(lstr_view, 'L');
	test_prefix_print(lstr_view, std::string_view("Donotexist"));
	test_prefix_print(lstr_view, "Donotexist");
	test_prefix_print(lstr_view, 'D');
	std::clog << '\n';

	test_suffix_print(lstr_view, std::string_view("string"));
	test_suffix_print(lstr_view, "string");
	test_suffix_print(lstr_view, 's');
	test_suffix_print(lstr_view, std::string_view("Donotexist"));
	test_suffix_print(lstr_view, "Donotexist");
	test_suffix_print(lstr_view, 'D');  

	return 0;
}


/***********
  END OF FILE
 ***********/
