/**********

References

    C++17 - The Complete Guide | Nicolai M. Josuttis
    https://en.cppreference.com/w/cpp/algorithm/for_each_n

Chapter 24 Other Utility Functions and Algorithms
	C++17 provides a couple of new utility functions and algorithms

24.5 for_each_n()
	it takes an integral parameter to apply the passed callable to n elements of a given range
	non.parallel version of for_each_n() guarantees that the passed callable is called for each element in order
	returns as an iterator the position behind the last processed element
	Any return value of the passed callable is ignored
	
	This algorithm is also available as a parallel STL algorithm, which allows us 
		to apply any function to the first n elements without any order guaranteed.
	
*************/

#include <iostream>
#include <algorithm>
#include <vector>

auto display_coll = [](const auto & coll) {
    std::cout << "Collection elements: \n";
    for(const auto & elem : coll)  {
        std::cout << elem << ' ';
    }
    std::cout << '\n';
};

int main() {
    std::cout << "=== std::for_each_n() ===\n";

    std::vector     lvec{-4, -3, -6, -9, 0, 3, 5, 8, 1, 9, 6, 4};
    display_coll(lvec);
    
    std::for_each_n(lvec.begin(), 7, [](auto & elem){ elem = elem * 2;});
    display_coll(lvec);

    std::for_each_n(lvec.begin(), lvec.size(), [](auto & elem){ std::cout << elem << ' '; });
    std::cout << '\n';

    return 0;
}

/**********
    END OF FILE
*************/


