/********
  Back to Basics: Lambdas - Nicolai Josuttis - CppCon 2021

  This example demonstrates the concept demonstrated in the above cppcon conference video.
  For more info visit:
  Back to Basics: Lambdas - Nicolai Josuttis - CppCon 2021 | https://www.youtube.com/watch?v=IgNUBw3vcO4&list=PLHTh1InhhwT4TJaHBVWzvBOYhp27UO7mI&index=6
https://en.cppreference.com/w/cpp/language/lambda
https://www.fluentcpp.com/2021/12/13/the-evolutions-of-lambdas-in-c14-c17-and-c20/

 *******/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

struct Person {
	std::string first_name;
	std::string last_name;

};
bool lessPerson(const Person & p1, const Person & p2) {
	return (p1.first_name < p2.first_name) ||
		((p1.first_name == p2.first_name) && (p1.last_name < p2.last_name));
}
void printPersonCollection(const std::vector<Person> & coll) {
	for(const auto & elem : coll) {
		std::clog << elem.first_name << ' ' << elem.last_name << '\n';
	}
	std::clog << "--------------------\n";
	return;
}

bool is_even(const int num) {
	return (0 == (num %2));
}

void printVectorCollection(std::vector<std::string> & coll) {
	for(const auto & elem : coll) {
		std::clog << elem << ", ";
	}
	std::clog << "\n";
	return;
}

int main() {
	// 1. Helper function and Lambda 
	std::vector<Person> person_coll_01{
		{"Ajay", "Garg"},
			{"Kishan", "Goyal"},
			{"Ajay", "Sahi"},
			{"Manjit", "Dubey"}
	};

	std::clog << "=== SORTING USING HELPER FUNCTION ===\n";
	printPersonCollection(person_coll_01);
	std::sort(person_coll_01.begin(), person_coll_01.end(), lessPerson); // using helper function for sorting
	printPersonCollection(person_coll_01);

	std::vector<Person> person_coll_02{
		{"Ajay", "Garg"},
			{"Kishan", "Goyal"},
			{"Ajay", "Sahi"},
			{"Manjit", "Dubey"}
	};
	std::clog << "=== SORTING USING LAMBDA ===\n";
	printPersonCollection(person_coll_02);
	// using lambda for sorting
	std::sort(person_coll_02.begin(), person_coll_02.end(), 
			  [](const Person & p1, const Person & p2) {
				  return (p1.first_name < p2.first_name) ||
					  ((p1.first_name == p2.first_name) && (p1.last_name < p2.last_name));
			  }
			 );
	printPersonCollection(person_coll_02);


	// 2. helper funciton and lambda with standard algorithm
	std::clog << "=== ALGORITHM USING HELPER FUNCTION ===\n";
	std::vector<int> number_coll{1,2,3,4,5,5,7,8,9,10,10,11,12,13,14};
	auto res = std::count_if(number_coll.begin(), number_coll.end(), is_even); // using helper function with standard algorithm
	std::clog << res << " even numbers are present in collection\n";

	// using lambda with standard algorithm
	std::clog << "=== ALGORITHM USING LAMBDA ===\n";
	auto res2 = std::count_if(number_coll.begin(), number_coll.end(), 
							  [](const int num ) {
								  return (0 == (num % 2));
							  }
							 );
	std::clog << res2 << " even numbers are present in collection\n";

	// 3. Combining lambdas with standard ranges algorithms
	std::vector<Person> person_coll_03{
		{"Ajay", "Garg"},
			{"Kishan", "Goyal"},
			{"Ajay", "Sahi"},
			{"Manjit", "Dubey"}
	};

	std::clog << "=== LAMBDA WITH STANDARD RANGE ALGORITHMS ===\n";
	printPersonCollection(person_coll_03);
	// using lambda with standard ranges algorithm
	std::ranges::sort(person_coll_03,
					  [](const Person & p1, const Person & p2) {
						  return (p1.first_name < p2.first_name) ||
							  ((p1.first_name == p2.first_name) && (p1.last_name < p2.last_name));
					  }
					 );
	printPersonCollection(person_coll_03);

	std::vector<std::string> str_coll_01{"you", "me", "him", "they", "them", "they", "her", "she", "she", "he"};
	printVectorCollection(str_coll_01);
	std::sort(str_coll_01.begin(), str_coll_01.end(), 
			  [](const std::string & s1, const std::string & s2){
				  return std::lexicographical_compare(s1.begin(), s1.end(),
													  s2.begin(), s2.end(),
													  [](const char c1, const char c2){
														  return std::toupper(c1) < std::toupper(c2);
													  });
			  });
	printVectorCollection(str_coll_01);

	std::vector<std::string> str_coll_02{"you", "me", "him", "they", "them", "they", "her", "she", "she", "he"};
	printVectorCollection(str_coll_02);
	std::ranges::sort(str_coll_02,
					  [](const std::string & s1, const std::string & s2) {

						  auto toUpper = [](const char ch) { return std::toupper(ch); };
                          /**************
                            Why toUpper as Lambda?
                           1. To demonstrates about how you can combine things.
                           2. std::toupper() is a C function by combining building blocks you may run into
                           problems with generic code.
                           
                           ************/

						  return std::ranges::lexicographical_compare(s1,
																	  s2,
																	  std::less{},
																	  toUpper,
																	  toUpper
																	 );
					  });
	printVectorCollection(str_coll_02);

	return 0;
}

/*******
  END OF FILE
 ******/
