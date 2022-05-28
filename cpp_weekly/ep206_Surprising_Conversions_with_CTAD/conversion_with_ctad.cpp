/************
  This example demonstrates about unwanted implicit conversion when using CTAD


 **********/

#include <string>
#include <utility>
#include <tuple>

std::pair<std::string, std::string> getStringPair() {
	const std::string str1 = "this";
	const std::string str2 = "that";

	return {str1, str2};
}

int main () {

	const std::pair<std::string, std::string> p1 = getStringPair();
	const std::pair p2 = getStringPair();
	const auto p3 = getStringPair();

	const std::tuple<std::string, std::string> t1 = getStringPair();

	/* Following line compiles because tuple has an constructor taking pair as an argument, deduction guide for it 
	   the single parameter tuple constructor is not explicit and that's why it allows implicit conversion
	   */
	const std::tuple t2 = getStringPair();  // CTAD 

	return 0;
}

/********
  END OF FILE
 ******/
