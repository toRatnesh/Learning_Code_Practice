/*****
  This example demonstrates about STL implementation difrrence by diffrent libraries

  For more info visit:
  C++ Insights - Episode 6: The little differences between the STL's 
https://www.youtube.com/watch?v=ZmD5AXN8lmI
 *****/

#include <vector>

int main() {
	std::vector<int> lv{1,2,3};

	/* with libstdc++
	   const int __list15[3]{1, 2, 3};
	   std::vector<int> lv = std::vector<int, std::allocator<int> >{std::initializer_list<int>{__list15, 3}, std::allocator<int>()};
	   */

	/* with libc++
	   const int __list15[3]{1, 2, 3};
	   std::vector<int> lv = std::vector<int, std::allocator<int> >{std::initializer_list<int>{__list15, 3}};
	   */


	return 0;
}

/******
  END OF FILE
 *****/
