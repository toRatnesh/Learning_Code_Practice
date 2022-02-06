/******************
  This example demonstrates about use of emplace_back and push_back uses.

emplace_back:   
Appends a new element to the end of the container. The element is constructed through std::allocator_traits::construct, which typically uses placement-new to construct the element in-place at the location provided by the container. The arguments args... are forwarded to the constructor as std::forward<Args>(args)....

If the new size() is greater than capacity() then all iterators and references (including the past-the-end iterator) are invalidated. Otherwise only the past-the-end iterator is invalidated.

push_back:
Appends the given element value to the end of the container.

1) The new element is initialized as a copy of value.
2) value is moved into the new element.
If the new size() is greater than capacity() then all iterators and references (including the past-the-end iterator) are invalidated. Otherwise only the past-the-end iterator is invalidated.

For more info visit:
https://en.cppreference.com/w/cpp/container/vector/emplace_back
https://en.cppreference.com/w/cpp/container/vector/push_back
 *******************/

#include <vector>
#include <string>

int main() {
	std::vector<std::string> vec;

	std::string lstr(10, 'A');
	vec.push_back(lstr);

	vec.emplace_back(10, 'B');

	// since c++17 emplace_back returns a reference to the inserted element
	vec.emplace_back(9, 'C').push_back('C');
	vec.emplace_back(11, 'D').pop_back();

	for(const auto & elem : vec) {
		std::puts(elem.c_str());
	}

	return 0;
}

/************
  END OF FILE
 ************/
