/********
  Back to Basics: Lambdas - Nicolai Josuttis - CppCon 2021

  This example demonstrates the concept demonstrated in the above cppcon conference video.
  For more info visit:
  Back to Basics: Lambdas - Nicolai Josuttis - CppCon 2021 | https://www.youtube.com/watch?v=IgNUBw3vcO4&list=PLHTh1InhhwT4TJ  aHBVWzvBOYhp27UO7mI&index=6
https://en.cppreference.com/w/cpp/language/lambda
https://www.fluentcpp.com/2021/12/13/the-evolutions-of-lambdas-in-c14-c17-and-c20/

 *******/

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

int getTax(const int year) {

	int slab = 0;

	if(2020 == year) {
		slab = 1;
	}
	else if(2021 == year) {
		slab = 2;
	}
	else if(2022 == year) {
		slab = 3;
	}
	else {
		slab = 5;
	}

	return slab;
}

auto calculateTaxForYear(const int year) {
	auto tax = getTax(year);
	return [tax](int value){ return value * (1 + tax);};
}

void displayVector(const std::vector<int> & coll) {
	for(const auto & elem : coll) {
		std::clog << elem << ", ";
	}
	std::clog << '\n';
}

int main() {

	// 6. Lambdas are more than functions
	/*******
	  Lambdas are better than functions in many way
	  -> Can be used as local functions
	  -> Convient way to define functions at run time
	  . Functions with state
	 ******/
	std::clog << "=== LAMBDAS AS BETTER FUNCTIONS ===\n";


	// 7. Lambdas Captures
	/*******
	  -> Capture behavior parameters
	  . Functionality can depend on run-time parameters 
	  -> To deal with call parameters
	 ****/
	std::clog << "=== LAMBDAS CAPTURES ===\n";
	int max = 30;
	std::vector<int> int_coll{12, 15, 28, 35, 46, 51, 66, 77, 13, 10, 68};
	const auto res = std::count_if(int_coll.begin(), int_coll.end(), 
								   [max](const int elem){ return elem < max;});
	std::clog << res << " numbers are less than " << max << " in collection\n";

	// 8. Using Lambdas
	/*************
	  -> Lambdas can be used as objects
	  . Local functions(behavior defined at runtime)
	  . Type has to be auto (type name is platform dependent)
	  . Functions passed around (behavior defined at runtime)
	  . Multiple "functions" can co-exist
	 **********/
	std::clog << "=== USING LAMBDAS ===\n";
	auto chnageCharToUpper = [](const char ch) { return std::toupper(ch);};
	std::string lstr = "this will be changed to all uppercase letters";
	std::clog << "Before transform: " << lstr << '\n';
	std::transform(lstr.cbegin(), lstr.cend(), lstr.begin(), chnageCharToUpper);
	std::clog << "After transform: " << lstr << '\n';

	auto calculateTaxFor2021 = calculateTaxForYear(2021);
	auto calculateTaxFor2022 = calculateTaxForYear(2022);
	std::vector<int> value_coll{10,15, 1050, 2000, 5050, 6000, 2500, 5500, 6700, 8000};
	std::clog << "Value collection: "; 
	displayVector(value_coll);

	std::vector<int> tax_coll_2021; 
	std::transform(value_coll.cbegin(), value_coll.cend(), std::back_inserter(tax_coll_2021), calculateTaxFor2021); // will need to use std::back_inserter because destination size is less than source
	std::clog << "Tax collection for year 2021: "; 
	displayVector(tax_coll_2021);

	std::vector<int> tax_coll_2022(value_coll.size()); 
	std::transform(value_coll.cbegin(), value_coll.cend(), tax_coll_2022.begin(), calculateTaxFor2022);
	std::clog << "Tax collection for year 2022: "; displayVector(tax_coll_2022);


	return 0;
}

/********
  END OF FILE  
 ******/
