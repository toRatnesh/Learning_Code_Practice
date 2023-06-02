/**********

References

    C++17 - The Complete Guide | Nicolai M. Josuttis
    https://en.cppreference.com/w/cpp/iterator/size
    https://en.cppreference.com/w/cpp/iterator/empty
    https://en.cppreference.com/w/cpp/iterator/data
    
Chapter 24 Other Utility Functions and Algorithms
	C++17 provides a couple of new utility functions and algorithms

24.1 size(), empty(), and data()
	C++ standard library provides three new helper functions: size(), empty(), and data()
	
24.1.1 Generic size() Function
	for the size of any range as long as it has an iterator interface or is a raw array
	this code doesn’t work for forward_list<>, because forward lists don’t have a member function size()

24.1.2 Generic empty() Function
	to check, whether a container, a raw C array, or a std::initializer_list<> is empty
	also works for forward lists
	
24.1.3 Generic data() Function
	to give access to the raw data of containers that have a data() members and raw arrays, 
		a container, a raw C array, or a std::initializer_list<>
	
*************/

#include <iostream>
#include <vector>
#include <array>
#include <forward_list>
#include <string>

int main() {

    std::vector lvec{2, 6, 3, 7, 9, 2, 5};
    std::array  larr{3, 5, 6, 7, 3, 4};
    int         rarr[]{3, 5, 6, 7, 3, 4};
    std::forward_list   lflst{3, 5, 6, 5, 7, 3, 2, 4, 6, 8, 4, 3, 1, 7, 3, 6, 9};
    const char *cptr = "sample char pointer";

    std::cout << "=== Generic std::size() ===\n";
    std::cout << "std::size(lvec): " << std::size(lvec) << '\n';
    std::cout << "std::size(larr): " << std::size(larr) << '\n';
    std::cout << "std::size(rarr): " << std::size(rarr) << '\n';
    // CE error: no matching function for call to 'size(std::forward_list<int, std::allocator<int> >&)'
    //std::cout << "std::size(lflst): " << std::size(lflst) << '\n'; 
    // CE error: no matching function for call to 'size(const char*&)'
    //std::cout << "std::size(cptr): " << std::size(cptr) << '\n';

    std::cout << "=== Generic std::empty() ===\n";
    std::cout << std::boolalpha << "std::empty(lvec): " << std::empty(lvec) << '\n';
    std::cout << std::boolalpha << "std::empty(larr): " << std::empty(larr) << '\n';
    std::cout << std::boolalpha << "std::empty(rarr): " << std::empty(rarr) << '\n';
    std::cout << std::boolalpha << "std::empty(lflst): " << std::empty(lflst) << '\n';  
    // CE error: no matching function for call to 'empty(const char*&)'
    //std::cout << std::boolalpha << "std::empty(cptr): " << std::empty(cptr) << '\n';
    {
    std::vector<int> lvec;
    std::array<int, 0>  larr;
    int         rarr[1];
    std::forward_list<int>   lflst;

    std::cout << std::boolalpha << "std::empty(lvec): " << std::empty(lvec) << '\n';
    std::cout << std::boolalpha << "std::empty(larr): " << std::empty(larr) << '\n';
    // NOTE: std::empty() can not be called with 0 size array
    std::cout << std::boolalpha << "std::empty(rarr): " << std::empty(rarr) << '\n';
    std::cout << std::boolalpha << "std::empty(lflst): " << std::empty(lflst) << '\n';         
    }

    std::cout << "=== Generic std::data() ===\n";
	std::cout << "*std::data(lvec): " << *std::data(lvec) << ", *(std::data(lvec)+2): " << *(std::data(lvec)+2) << '\n';
	std::cout << "*std::data(larr): " << *std::data(larr) << ", *(std::data(larr)+2): " << *(std::data(larr)+2) << '\n';
	std::cout << "*std::data(rarr): " << *std::data(rarr) << ", *(std::data(rarr)+2): " << *(std::data(rarr)+2) << '\n';
	// CE error: no matching function for call to 'data(std::forward_list<int, std::allocator<int> >&)'
    //std::cout << "*std::data(lflst): " << *std::data(lflst) << ", *(std::data(lflst)+2): " << *(std::data(lflst)+2) << '\n';
	// CE error: no matching function for call to 'data(const char*&)'
    //std::cout << "*std::data(cptr): " << *std::data(cptr) << ", *(std::data(cptr)+2): " << *(std::data(cptr)+2) << '\n';

    return 0;
}

/**********
    END OF FILE
*************/


