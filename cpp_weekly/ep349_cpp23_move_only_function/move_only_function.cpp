/**********
  This example demonstrates about C++23 move only function

  std::move_only_function
  C++23 introduces move_only_function which 
  can be used for those function objects which cannot be copied and can only be moved

  this comes over limitation of std::function which need only copyable funciton object

  For more info visit:
	episode: https://www.youtube.com/watch?v=OJtGOJI0JEw&list=PLs3KjaCtOwSZ2tbuV1hx8Xz-rFZTan2J1&index=349
	https://en.cppreference.com/w/cpp/utility/functional/move_only_function


 ***********/

#include <iostream>
#include <functional>
#include <memory>

auto fun(std::move_only_function<int (int)> callback, int m) {
	int retval = 0;
	if(callback) { 
		retval = callback(m); 
	}
	else {
		std::clog << "callback is empty\n";
	}
	return retval;
}

int main() {
	auto l = [up=std::make_unique<int>(2)](int m){ return *up+m;};
	return fun(std::move(l), 5);
}

/*******
  END OF FILE
 ********/
