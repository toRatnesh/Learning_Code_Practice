/********
  This example demonstrates about range based for loop

  For more info visit:
  C++ Insights - Episode 3: What is behind a range-based for-loop |
https://www.youtube.com/watch?v=YnhNgMJvQh0

Compile this example in https://cppinsights.io/ with C++11 and C++14 version and check the difference

 *******/

#include <iostream>
#include <vector>

int main() {

	char buffer[]{"Hello"};
	//for(const auto & c : buffer) 
	for(int lvar = 5; const auto & c : buffer) // c++20
	{
		std::clog << c;
	}
	std::clog << '\n';

	std::vector<char> lv {'a', 'e', 'i', 'o', 'u'};
	for(const auto & c: lv) {
		std::clog << c;
	}
	std::clog << '\n';
	return 0;
}

/*******
  END OF FILE
 ******/
