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

	// 10. Capturing in detail
	// For more info check https://en.cppreference.com/w/cpp/language/lambda#Lambda_capture
	/*******
	  -> Capturing is performed when lambda is created
	  . Local read-only copy (unless passed by reference)
	 *******/

	// 10.1 | capture by value
	// objects captured by value are by default read-only copies to make the lambda stateless (can't change it's behavior)

	int value = 10;
	auto lbd_capture_by_value = [value](){ 
		//std::clog << ++value << '\n';   // can't change value captured by copy, CE error: increment of read-only variable 'value'
		std::clog << value << '\n'; 
	};
	lbd_capture_by_value();
	value = 11;
	lbd_capture_by_value(); // no effect on value printed

	// 10.2 | Capture by reference
	auto lbd_capture_by_reference = [&value](){
		std::clog << ++value << '\n'; // can change value captured by reference
	};
	lbd_capture_by_reference();
	lbd_capture_by_reference(); // value changed


	// 10.3 | Lambda capture initializers
	/******
	  -> Since C++14, you can pass initializers to lambda captures
	  . enables adding local state
	  . enables capturing by const reference with std::as_const()
	 ****/
	auto lambda_initialier = [multiplier = 3] (const int val) { return val * multiplier;}; // initializes 'multiplier' with 3
	std::clog << "lambda_initialier(17): " << lambda_initialier(17) << '\n';

	// 10.4 | Mutable lambdas
	/*******
	  -> Lambdas are stateless by default 
	  . Not allowed to modified values captured by-value
	  -> mutable makes them stateful (modification allowed)
	 ******/
	auto lambda_mutable = [value]() mutable { 
		std::clog << ++value << '\n'; // capture by value but modification allowed
	};
	lambda_mutable();
	lambda_mutable();

	return 0;
}

/********
  END OF FILE  
 ******/
