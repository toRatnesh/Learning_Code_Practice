/**********

References

    C++17 - The Complete Guide | Nicolai M. Josuttis
    https://en.cppreference.com/w/cpp/algorithm/search
    https://en.cppreference.com/w/cpp/header/functional#Searchers

Chapter 23 Substring and Subsequence Searchers

	C++17 therefore introduced the Boyer-Moore and Boyer-Moore-Horspool search algorithms
	
23.2 Using General Subsequence Searchers
	-> C++17 adopts Boyer-Moore and Boyer-Moore-Horspool algorithm as generic algorithms 
		so that you can use them to find a subsequence of elements in a container or range
	-> you can also use the function-call operator of the searcher
	
	-> To make this possible the elements have to be able to be used in a hash table 
		(i.e., a default hash function has to be provided and comparing two element with == has to be supported). 
	-> If this is not the case, you can use predicates
	
*************/

#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

int main() {
    std::cout << "=== Using General Subsequence Searchers ===\n";

    std::vector<int>    ivec_coll;
    for(int i = 0; i < 100000; ++i) {
        ivec_coll.insert(ivec_coll.end(), {9+i, 3*i, 2*(i+1)});
    }
    std::vector<int>    search_this{109, 300, 202};

    {
        std::cout << "\n=== using search() algorithm ===\n";
        auto pos = std::search(ivec_coll.begin(), ivec_coll.end(),
                                std::boyer_moore_searcher{search_this.begin(), search_this.end()});
        if(ivec_coll.end() == pos) {

        } else {
            std::cout << "Found subset at index " << (pos-ivec_coll.begin())  << '\n';
        }
    }

    {
        std::cout << "\n=== using operator() of boyer_moore_searcher ===\n";
        std::boyer_moore_searcher   bms{search_this.begin(), search_this.end()};
        for(auto [pos_b, pos_e] = bms(ivec_coll.begin(), ivec_coll.end());
                    ivec_coll.end() != pos_b;
                    std::tie(pos_b, pos_e) = bms(pos_e, ivec_coll.end())) {
                        std::cout << "Found subset at index " << (pos_b-ivec_coll.begin()) << '-' << (pos_e-ivec_coll.begin()) << '\n';
        }
    }

    return 0;
}

/**********
    END OF FILE
*************/


