/*************
  This example demonstrate about template instantiation and explicit template instantiation.

  For more info visit:
  Back to Basics: Compiling and Linking - Ben Saks - CppCon 2021
https://www.youtube.com/watch?v=cpkDQaYttR4&list=PLHTh1InhhwT4TJaHBVWzvBOYhp27UO7mI&index=7

 **************/

#include "header.hpp"
#include <string>
#include <iostream>

int main() {

	S<int> si;
	si.fun(2);

	S<double> sd;
    sd.fun(2.5);

    // function declaration defined in fun.cpp
    void swapString();
    swapString();

    std::string str1 = "Modern";
    std::string str2 = "C++";

    std::clog << "Before swap: \n" << str1 << ' ' << str2 << '\n';
    mySwap(str1, str2);
    std::clog << "After swap: \n" << str1 << ' ' << str2 << '\n';

	return 0;
}

/********
  END OF FILE
 *******/
