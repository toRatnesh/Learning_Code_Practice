/*******************
 * 	If a function declared nodiscard or a function returning an enumeration or class declared nodiscard by value is called from a
 * 	discarded-value expression other than a cast to void, the compiler is encouraged to issue a warning.
 * ***************/

#include <iostream>
#include <string>

struct S {
	[[nodiscard]] size_t getsize(const std::string & msg) 
	//[[nodiscard("Do not ignore return value of getsize")]] size_t getsize(const std::string & msg) 	// valid since c++20
	{
		return msg.length();
	}
};

int main() {  
	S s;
	s.getsize("Learning");
	size_t l_len = s.getsize("Learning nodiscard");
	std::cout << R"(s.getsize("Learning nodiscard"))" << " : " << l_len << '\n';
	return 0;
}

/***********
 *	END OF FILE
 * *******/
