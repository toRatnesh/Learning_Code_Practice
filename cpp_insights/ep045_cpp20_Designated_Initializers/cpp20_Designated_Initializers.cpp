/*****

    This example demonstrates the use of c++20 desiganted initializer and lambda.

    For more info visit
    C++ weekly episode 127 and 141
    https://github.com/toRatnesh/Learning_Code_Practice/blob/main/cpp_weekly/ep127_cpp20_Designated_Initializers/designated_initializers.cpp
    https://github.com/toRatnesh/Learning_Code_Practice/blob/main/cpp_weekly/ep141_cpp20_Designated_Initializers_And_Lambdas/designated_initializer_and_lambda.cpp
    
    https://www.cppstories.com/2021/designated-init-cpp20/

    https://en.cppreference.com/w/cpp/language/aggregate_initialization#Designated_initializers

    Designated initializers
    T object = { .des1 = arg1 , .des2 { arg2 } ... };	(3)	(since C++20)
    T object { .des1 = arg1 , .des2 { arg2 } ... };     (4)	(since C++20)
    The syntax forms (3,4) are known as designated initializers: each designator must name a direct non-static data member of T, 
        and all designators used in the expression must appear in the same order as the data members of T.

*****/

#include <string>
#include <iostream>

template<typename T>
struct St{
	T i;
	std::string j;

    void display() {
        std::cout << "i " << i << " j " << j << '\n';
    }
};

struct S {
	int i;
	std::string j;

    void display() {
        std::cout << "i " << i << " j " << j << '\n';
    }
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
    s1.display();
    s2.display();
    s3.display();
    s4.display();

    std::cout << '\n';

	St st1{31, R"(sample string-31)"};
	St st2{.i=32, .j=R"(sample string-32)"};
	St st3{
		[]{return 33;}(), 
			[](const std::string st){ return st;}(R"(sample string-33)")
	};
	St st4{
		.i=[]{return 34;}(), 
			.j=[](const std::string st){ return st;}(R"(sample string-34)")
	};
    st1.display();
    st2.display();
    st3.display();
    st4.display();

	return 0;
}

/**********
 *	END OF FILE
 * *******/


