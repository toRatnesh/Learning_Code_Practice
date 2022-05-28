/****************
  This example demonstrates about the uses of lambda

125: The optimal way to return from a function https://youtu.be/9mWWNYRHAIQ
132: Lambdas in Fold Expressions https://www.youtube.com/watch?v=QhY7Fx-YsGs
61: Storage Duration With Lambdas https://www.youtube.com/watch?v=WUvF4W98vq4
32: Lambdas For Free https://www.youtube.com/watch?v=_CbBfuQQQI8
93: Custom Comparators https://www.youtube.com/watch?v=sbiF1HDcG7U
94: Lambdas as Comparators https://www.youtube.com/watch?v=dvLKY-oWqn0
95: Transparent Comparators https://www.youtube.com/watch?v=BBUacofxOP8
96: Transparent Lambda Comparators https://www.youtube.com/watch?v=P6_6bXPGYy8

// exercise
// How and why are OPT_1 and OPT_2 so different?
Ans:    
OPT_1 
In this case one lambda will be deifned and same will be called for all elements.

OPT_2
In this case same lambda will be intantiated for each element passed to it and this will generate identical lambda for all elements.

NOTE:
In case one element is passed both scenarios will have same complexity as only one lambda will be present for both.

 **************/

#include <cstdio>
#include <string>

template <typename... Param>
void print_list(const std::string &c1, const Param &...params) {

#ifdef OPT_1

	auto print_element = [&](const auto &p) {
		std::puts((c1 + ": " + p).c_str());
	};

	(print_element(params), ...);

#endif

#ifdef OPT_2

	([&](const auto &p) { 
		std::puts((c1 + ": " + p).c_str()); 
	}(params), ...);

#endif

}

int main() { 
	print_list("Hello", "1", "2", "3", "4", "5", "6", "7", "8"); 
	return 0;
}

/****
  END OF FILE
 *****/
