/********
  Back to Basics: Lambdas - Nicolai Josuttis - CppCon 2021

  This example demonstrates the concept demonstrated in the above cppcon conference video.
  For more info visit:
  Back to Basics: Lambdas - Nicolai Josuttis - CppCon 2021 | https://www.youtube.com/watch?v=IgNUBw3vcO4&list=PLHTh1InhhwT4TJaHBVWzvBOYhp27UO7mI&index=6
https://en.cppreference.com/w/cpp/language/lambda
https://www.fluentcpp.com/2021/12/13/the-evolutions-of-lambdas-in-c14-c17-and-c20/

 *******/

#include <iostream>
#include <set>

int main() {

    // 4. Named Generic Lambdas
    /*******
      -> Call argument may have a genric type
      . auto, const auto & ...
      -> Not possible in normal functions before C++20
     *******/
    auto twice = [](const auto & x){
		return x+x;
	};

	std::clog << twice(4) << '\n';
	std::clog << twice(4.3) << '\n';
	std::clog << twice(2.3f) << '\n';
	std::clog << twice(std::string("main ")) << '\n';
	//std::clog << twice("C++ ") << '\n'; // CE error: invalid operands of types 'const char [5]' and 'const char [5]' to binary 'operator+'


	// 5. Lambda without captures
	/***********
	  Lambda without captures
	  -> Can be used as ordinary function pointers
	  -> Can be used as sorting criterion
	  -> Can be used as hash function type (since C++20) 
	  (For more detail about this and lambda in C++20 check
	  C++ Weekly episode 149, 150 151)

	 **********/

	auto lbd = [](int m, double d){ return m*d;};
	std::clog << lbd(4,2.5) << '\n';

	// lambda without capture are compatible with function pointers
	double (*fun)(int, double) = lbd;
	std::clog << fun(8, 2.5) << '\n';

	using fp = double (*)(int, double);
	fp fp1 = lbd;
	std::clog << fp1(10, 2.5) << '\n';

	// lambda with capture
	auto lbd2 = [r=5](int m, double d){ return m*d*r;};
	std::clog << lbd2(4,2.5) << '\n';

	// lambda with captures are not compatible with function pointer
	//double (*fun2)(int, double) = lbd2; // error: cannot convert 'main()::<lambda(int, double)>' to 'double (*)(int, double  )' in initialization
	//fp fp2 = lbd2;  // error: cannot convert 'main()::<lambda(int, double)>' to 'fp' {aka 'double (*)(int, double)'} in ini  tialization

	// lambda as hash function
	struct St{ int data; };

	const auto lambda_comparator = [](const St & lhs, const St & rhs){
		return lhs.data < rhs.data;
	};

	// C++11
	std::set<St, decltype(lambda_comparator)> lset1{lambda_comparator};

	// C++17 auto template type deduction
	std::set lset2{ {St{5}}, lambda_comparator};

	// C++20 use of lambda default constructor
	std::set<St, decltype(lambda_comparator)> lset3;

	// C++20 use of lambda in UC and default constructor
	std::set< St,
		decltype([](const St & lhs, const St & rhs){ return lhs.data < rhs.data;})
			> lset4;


	return 0;
}

/*******
  END OF FILE
 ******/
