/************
 *	This example demonstrates the use of cpp20 designated initializer.
 *
 *	For more info visit:
 *	Designated initializers: https://en.cppreference.com/w/cpp/language/aggregate_initialization#Designated_initializers
 *	Tutorial:		 https://www.youtube.com/watch?v=44rs_hX1dxE&list=PLs3KjaCtOwSZ2tbuV1hx8Xz-rFZTan2J1&index=129
 *
 * *************/

#include <iostream>
#include <string>

struct St {
	int ival;
	double dval;
	std::string sval;
};

void use_St(St st_arg) {

	return ;
} 

int main() {
	St so1{1, 5.6, R"(sample string)"};
	St so2{.ival=1, .dval=5.6, .sval=R"(sample string)"};
	St so3{.ival=1, .sval=R"(sample string)"};  // warning: missing initializer for member 'St::dval'
	//St so4{.dval=5.6, .ival=1, .sval=R"(sample string)"}; // CE: error: designator order for field 'St::ival' does not match declaration order in 'St'

	use_St(St{.ival=1, .dval=5.6, .sval=R"(sample string)"});

	return 0;
}

/***********
 *	END OF FILE
 * ********/
