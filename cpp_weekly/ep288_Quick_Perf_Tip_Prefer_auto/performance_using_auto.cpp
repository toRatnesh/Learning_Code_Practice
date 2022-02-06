/************
 *	This example demonstrates how uses of auto reuslts in better performance.
 *
 *
 *
 *	Key Details:
 *	-> 'auto' uses the exact same rules as template type parameters
 *	-> 'auto' will never deduce a '&'
 *	-> 'const'-ness will be deduced (for references and pointers)
 *	-> value types are always copies
 *	-> auto will never perform a conversion
 *	-> auto is better performing because it eliminates accidental conversion
 *
 *	NOTE:
 *	1. auto type deduction is usually the same as template type deduction, but auto type deduction assumes
 *	that a braced initializer represents a std::initializer_list, and template type deduction doesn't.
 *	2. auto in a function return type or a lambda parameter implies template type deduction, not auto type deduction.
 *	Refernce : Effective Modern C++
 *
 * ********/

#include <string>
#include <map>
#include <utility>

std::string g_str = "Global sample string-1";
std::string g_str2 = "Global sample string-2";

std::string get_s() { return std::string("sample string"); }

const std::string & get_scr() { return g_str; }
const std::string & get_scr2() { return g_str2; }

const char * get_cp() { return "A char pointer"; }

const std::map<std::string, std::string> & get_map() {
		static std::map<std::string, std::string> lv {
				{"key1", "value1"},
						{"key2", "value2"},
						{"key3", "value3"}
		}; 

		return lv;
}

int main() {
		auto ret = get_scr() + get_scr2();
		auto ret2 = get_cp();   // no conversion ret2 is a char *

		for(const std::pair<std::string, std::string> & elem : get_map()) 
		{
				// S-1

		}

		for(const std::pair<const std::string, std::string> & elem : get_map()) 
		{
				// S-2 better performance than S-1 
		}


		for(const auto & elem : get_map()) 
		{
				// S-3 better performance than S-1 because no conversion
		}

		for(const auto & [k , v] : get_map())       // c++17 structure binding
		{
				// S-3 better performance than S-1 because no conversion
		}
		return 0;
}

/*******
 *	END OF FILE
 * ******/
