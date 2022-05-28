/*********
  This example demonstrates about C++23's auto{} and auto()

  The auto specifier is replaced with the deduced type of the invented variable x declared with auto x(expression); 
  (which is never interpreted as a function declaration) or auto x{expression}; respectively. 
  The result is always a prvalue of an object type.


  For more info visit:
https://www.youtube.com/watch?v=5zVQ50LEnuQ&list=PLs3KjaCtOwSZ2tbuV1hx8Xz-rFZTan2J1&index=324
https://en.cppreference.com/w/cpp/language/explicit_cast
 *********/
#include <iostream>
#include <vector>
#include <string>

void printContainer(auto & container) {
	for(const auto & val : container) {
		std::clog << val << ' ';
	}
	std::clog << '\n';
}

void erase_all_like_first(auto & container) {
	std::erase(container, container.front());    
}

void erase_all_like_first2(auto & container) {
	std::erase(container, auto(container.front()));    
}

int main() {
	std::vector<std::string> lvec{"erase", "this", "is", "a", "sample", "for", "erase", "to", "erase", "first", "value", "and", "print", "this"};
	std::vector<std::string> lvec2{"erase", "this", "is", "a", "sample", "for", "erase", "to", "erase", "first", "value", "and", "print", "this"};

	printContainer(lvec);
	erase_all_like_first(lvec);
	printContainer(lvec);

	std::clog << "---------------\n";

	printContainer(lvec2);
	erase_all_like_first2(lvec2);
	printContainer(lvec2);

	return 0;
}


/*******
  END OF FILE
 *******/
