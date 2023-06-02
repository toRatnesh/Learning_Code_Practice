/**********

References

    C++17 - The Complete Guide | Nicolai M. Josuttis
    https://en.cppreference.com/w/cpp/algorithm/sample    

Chapter 24 Other Utility Functions and Algorithms
	C++17 provides a couple of new utility functions and algorithms

24.4 sample()
    extracts a random subset (sample) from a given range of values (the population). 
    This is sometimes called reservoir sampling or selection sampling.
    returns the position after the last copied element.

    the order of the elements is stable (matches their order in coll). 
    However, this is only guaranteed if the iterators for the passed range are at least forward iterators.

    iterators for the source range must be at least input iterators and 
        the iterators of the destination range must be at least output iterator
    As usual the destination iterator overwrites, which causes undefined behavior 
        if the are not enough elements to overwrite and no inserter is used.
    destination iterator must not be in the passed source range
    The order of the extracted elements is stable unless the iterators in the source range are pure input iterators



*************/

#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
#include <random>

int main() {
    std::cout << "=== std::sample() ===\n";

    std::vector<std::string>     lvec;
    for(int i = 0; i < 10000; ++i) {
        lvec.push_back("sample string-" + std::to_string(i));
    }

    std::sample(lvec.begin(), lvec.end(),
                std::ostream_iterator<std::string>{std::cout, "\n"},
                10,
                std::default_random_engine{});

    std::cout << "=== std::sample() in a subset collection ===\n";
    std::random_device  rd;
    std::mt19937        eng{rd()};
    std::vector<std::string>    subset;
    subset.resize(1000);
    auto ss_end = std::sample(lvec.begin(), lvec.end(),
                                subset.begin(),
                                10,
                                eng);

    std::for_each(subset.begin(), ss_end, [](const auto & elem ) {
            std::cout << elem << '\n';
        });


    return 0;
}

/**********
    END OF FILE
*************/


