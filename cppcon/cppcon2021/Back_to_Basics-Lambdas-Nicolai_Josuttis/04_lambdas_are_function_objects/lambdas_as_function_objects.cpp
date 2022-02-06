/********
  Back to Basics: Lambdas - Nicolai Josuttis - CppCon 2021

  This example demonstrates the concept demonstrated in the above cppcon conference video.
  For more info visit:
  Back to Basics: Lambdas - Nicolai Josuttis - CppCon 2021 | https://www.youtube.com/watch?v=IgNUBw3vcO4&list=PLHTh1InhhwT4TJ  aHBVWzvBOYhp27UO7mI&index=6
https://en.cppreference.com/w/cpp/language/lambda
https://www.fluentcpp.com/2021/12/13/the-evolutions-of-lambdas-in-c14-c17-and-c20/

 *******/

#include <iostream>
#include <string>

int main() {

	// 9. Lambdas are Function objects
	/******
	  -> Lambdas are function objects defined "on the fly"
	  . Simple way to define objects that can be used like functions
	  . Using operator()
	  -> Have a "unique, unnamed non-union class type"
	  . Closure type
	 *****/

	// For each lambda in the source code the compiler 
	//  . defines a class ("closure type")
	//  . and creates an object of this class 

	int min = 9, max = 100;
	auto in_between = [min, max](const int val){ return ((min < val) && (val < max)); }; 
	// above lambda in_between is a function object, it is defined by compiler by definning a class (check generated class and more info with the help of https://cppinsights.io/)
	std::clog << std::boolalpha << "in_between(99): " << in_between(99) << '\n';
	std::clog << std::boolalpha << "in_between(121): " << in_between(121) << '\n';


	// C++14 - Generic lambdas
	/******
	  -> Lambdas for generic parameter types
	  . Using auto
	  . Defines function template member
	  . Usual template deduction rule apply
	 *****/
	auto lambda_add = [](const auto a, const auto b){ return (a+b);};
	// above generic lambda lambda_add generates template memeber functions in the generated class by compiler (check generated class and more info with the help of https://cppinsights.io/)
	std::clog << "lambda_add(3,4): " << lambda_add(3,4) << '\n';
	std::clog << "lambda_add(4.7, 13.2): " << lambda_add(4.7, 13.2) << '\n';
	std::clog << "lambda_add(1.2f, 3.4f): " << lambda_add(1.2f, 3.4f) << '\n';
	std::clog << R"(lambda_add(std::string("hello "), std::string("world !!!")): )" << lambda_add(std::string("hello "), std::string("world !!!")) << '\n';

	return 0;
}

/********
  END OF FILE  
 ******/
