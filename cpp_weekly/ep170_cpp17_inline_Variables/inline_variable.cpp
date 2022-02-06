/**********
 *	This example demonstrates the use of cpp17 inline variables.
 *
 *	For more info visit:
 *	https://en.cppreference.com/w/cpp/language/inline
 *
 * **************/

#include <iostream>
#include <string>
#include <string_view>

struct St {
	//const static std::string m_str;  

	inline const static std::string m_str1 = "sample string 01";
	constexpr static std::string_view m_str2 = "sample string 02"; // constexpr is implicitly an inline variable
	inline static std::string m_str3 = "sample string 03";
};

//const std::string St::m_str = "sample string";

int main () {
	St st;
	std::cout << st.m_str1 << '\n';
	std::cout << st.m_str2 << '\n';
	std::cout << st.m_str3 << '\n';
	st.m_str3 = "sample string 03 changed";
	std::cout << st.m_str3 << '\n';

	return 0;
}

/*******
 *	END OF FILE
 * *******/
