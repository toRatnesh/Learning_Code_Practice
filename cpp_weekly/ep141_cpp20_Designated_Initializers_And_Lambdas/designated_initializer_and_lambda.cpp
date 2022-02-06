/******************
 *	This example demonstrates the use of c++20 desiganted initializer and lambda.
 *	
 * ******************/
#include <string>

template<typename T>
struct St{
	T i;
	std::string j;
};

struct S {
	int i;
	std::string j;
};

int main() {
	S s1{1, R"(sample string-1)"};
	S s2{.i = 2, .j=R"(sample string-2)"};
	S s3{
		[]{return 3;}(),
			[](const std::string st){ return st;}(R"(sample string-3)")
	};
	S s4{
		.i = []{return 4;}(),
			.j= [](const std::string st){ return st;}(R"(sample string-4)")
	};

	St st1{31, R"(sample string-31)"};
	St st2{.i=32, .j=R"(sample string-32)"};
	St st3{
		[]{return 33;}, 
			[](const std::string st){ return st;}(R"(sample string-33)")
	};
	St st4{
		.i=[]{return 34;}, 
			.j=[](const std::string st){ return st;}(R"(sample string-34)")
	};

	return 0;
}

/**********
 *	END OF FILE
 * *******/
