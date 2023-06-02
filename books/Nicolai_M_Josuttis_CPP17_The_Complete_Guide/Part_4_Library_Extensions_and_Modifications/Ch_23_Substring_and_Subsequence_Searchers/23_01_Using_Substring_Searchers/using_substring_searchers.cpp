/**********

References

    C++17 - The Complete Guide | Nicolai M. Josuttis
    https://en.cppreference.com/w/cpp/algorithm/search
    https://en.cppreference.com/w/cpp/header/functional#Searchers

Chapter 23 Substring and Subsequence Searchers

	C++17 therefore introduced the Boyer-Moore and Boyer-Moore-Horspool search algorithms
	
23.1 Using Substring Searchers

23.1.1 Using Searchers with search()

	options to search a substring sub in a string text:

	1. String member find()
	2. Algorithm search()
	3. Parallel algorithm search()
	4. Using a default_searcher
	5. Using a boyer_moore_searcher
	6. Using a boyer_moore_horspool_searcher

	Boyer-Moore and the Boyer-Moore-Horspool searchers 
		-> require random access iterators (instead of forward iterators, which is enough for a naive search())
		-> precompute tables (of hash values) before the search starts to improve the speed of the search 
			if the search covers a text and/or substring of significant size
			
	Performance of Searchers
		-> Just using (non-parallel) search() is usually the slowest, 
			because for each character in text we start to find out whether a substring matches
		-> Using the default_searcher should be equivalent to that
		-> Using find() might be faster
		-> For texts and substrings of significant size, the boyer_moore_searcher should be the fastest
		-> The boyer_moore__horspool_searcher trades space for time. 
			It is usually slower than the boyer_moore_searcher, but should not use that much memory
		-> Using the parallel search() might be better than ordinary search()
		
	Suggestion: Test the typical scenarios on your target platforms


23.1.2 Using Searchers Directly
	use the function-call operator of the searcher, which returns a pair of both the begin and the end of a found subsequence
	use if with initialization and structured bindings for finding the only first occurrence of a substring using the searchers
	
*************/

#include <iostream>
#include <string_view>
#include <algorithm>
#include <iomanip>
#include <execution>

int main() {

    constexpr std::string_view str = R"(default_searcher
        A class suitable for use with Searcher overload of std::search that delegates the search operation to the pre-C++17 standard library's std::search. 
        std::default_searcher is CopyConstructible and CopyAssignable.
        
        boyer_moore_searcher
        A searcher suitable for use with the Searcher overload of std::search that implements the Boyer-Moore string searching algorithm. 
        std::boyer_moore_searcher is CopyConstructible and CopyAssignable. 
        RandomIt1(Iterator) must meet the requirements of LegacyRandomAccessIterator.
        
        boyer_moore_horspool_searcher
        A searcher suitable for use with the Searcher overload of std::search that implements the Boyer-Moore-Horspool string searching algorithm. 
        std::boyer_moore_horspool_searcher is CopyConstructible and CopyAssignable. 
        RandomIt1 must meet the requirements of LegacyRandomAccessIterator.
    )";

    constexpr std::string_view search_this = "CopyConstructible and CopyAssignable";

    {
    std::cout << "=== Using Searchers with search() ===\n\n";
    {
        std::cout << "=== using member funciton find() ===\n";
        constexpr auto pos = str.find(search_this);
        static_assert(207 == pos);
        if(std::string::npos == pos) {
            std::cout << "Could not find " << std::quoted(search_this) << '\n';
        } else {
            std::cout << "Found " << std::quoted(search_this) << " at index " << pos << '\n';
        }
    }
    {
        std::cout << "=== using member funciton find() in for loop ===\n";
        for(auto pos = str.find(search_this);
            std::string::npos != pos;
            pos = str.find(search_this, pos+1)) {
            if(std::string::npos == pos) {
                std::cout << "Could not find " << std::quoted(search_this) << '\n';
            } else {
                std::cout << "Found " << std::quoted(search_this) << " at index " << pos << '\n';
            }
        }

    }    
    {
        std::cout << "=== using search() algorithm ===\n";
        constexpr auto pos = std::search(str.begin(), str.end(), 
                                search_this.begin(), search_this.end());
        static_assert(207 == (pos - str.begin()));
        if(str.end() == pos) {
            std::cout << "Could not find " << std::quoted(search_this) << '\n';
        } else {
            std::cout << "Found " << std::quoted(search_this) << " at index " << (pos - str.begin()) << '\n';
        }
    }    
    {
        std::cout << "=== using parallel search() algorithm ===\n";
        auto pos = std::search(std::execution::par,
                                str.begin(), str.end(), 
                                search_this.begin(), search_this.end());
        //static_assert(207 == (pos - str.begin()));
        if(str.end() == pos) {
            std::cout << "Could not find " << std::quoted(search_this) << '\n';
        } else {
            std::cout << "Found " << std::quoted(search_this) << " at index " << (pos - str.begin()) << '\n';
        }
    }     
    {
        std::cout << "=== using search() algorithm with binary predecate ===\n";
        constexpr std::string_view search_this = "COPYCONSTRUCTIBLE AND COPYASSIGNABLE";
        
        {
        constexpr auto pos = std::search(str.begin(), str.end(), 
                                search_this.begin(), search_this.end());
        //static_assert(207 == (pos - str.begin()));
        if(str.end() == pos) {
            std::cout << "Could not find " << std::quoted(search_this) << '\n';
        } else {
            std::cout << "Found " << std::quoted(search_this) << " at index " << (pos - str.begin()) << '\n';
        }             
        }    

        auto pos = std::search(str.begin(), str.end(), 
                                search_this.begin(), search_this.end(),
                                [](const char c1, const char c2){
                                    return std::toupper(c1) == std::toupper(c2);
                                });
        //static_assert(207 == (pos - str.begin()));
        if(str.end() == pos) {
            std::cout << "Could not find " << std::quoted(search_this) << '\n';
        } else {
            std::cout << "Found " << std::quoted(search_this) << " at index " << (pos - str.begin()) << '\n';
        }
    }
    {
        std::cout << "=== using parallel search() algorithm with binary predecate ===\n";
        constexpr std::string_view search_this = "COPYCONSTRUCTIBLE AND COPYASSIGNABLE";
        
        {
        auto pos = std::search(std::execution::par,
                                str.begin(), str.end(), 
                                search_this.begin(), search_this.end());
        //static_assert(207 == (pos - str.begin()));
        if(str.end() == pos) {
            std::cout << "Could not find " << std::quoted(search_this) << '\n';
        } else {
            std::cout << "Found " << std::quoted(search_this) << " at index " << (pos - str.begin()) << '\n';
        }             
        }    

        auto pos = std::search(std::execution::par,
                                str.begin(), str.end(), 
                                search_this.begin(), search_this.end(),
                                [](const char c1, const char c2){
                                    return std::toupper(c1) == std::toupper(c2);
                                });
        //static_assert(207 == (pos - str.begin()));
        if(str.end() == pos) {
            std::cout << "Could not find " << std::quoted(search_this) << '\n';
        } else {
            std::cout << "Found " << std::quoted(search_this) << " at index " << (pos - str.begin()) << '\n';
        }
    }
    {
        std::cout << "=== using default_searcher() algorithm ===\n";
        constexpr auto pos = std::search(str.begin(), str.end(), 
                                std::default_searcher{search_this.begin(), search_this.end()});
        static_assert(207 == (pos - str.begin()));
        if(str.end() == pos) {
            std::cout << "Could not find " << std::quoted(search_this) << '\n';
        } else {
            std::cout << "Found " << std::quoted(search_this) << " at index " << (pos - str.begin()) << '\n';
        }
    } 
    {
        std::cout << "=== using boyer_moore_searcher() algorithm ===\n";
        auto pos = std::search(str.begin(), str.end(), 
                                std::boyer_moore_searcher{search_this.begin(), search_this.end()});
        //static_assert(207 == (pos - str.begin()));
        if(str.end() == pos) {
            std::cout << "Could not find " << std::quoted(search_this) << '\n';
        } else {
            std::cout << "Found " << std::quoted(search_this) << " at index " << (pos - str.begin()) << '\n';
        }
    }
    {
        std::cout << "=== using boyer_moore_horspool_searcher() algorithm ===\n";
        auto pos = std::search(str.begin(), str.end(), 
                                std::boyer_moore_horspool_searcher{search_this.begin(), search_this.end()});
        //static_assert(207 == (pos - str.begin()));
        if(str.end() == pos) {
            std::cout << "Could not find " << std::quoted(search_this) << '\n';
        } else {
            std::cout << "Found " << std::quoted(search_this) << " at index " << (pos - str.begin()) << '\n';
        }
    }                 
    }
    std::cout << "=== using boyer_moore_horspool_searcher() algorithm in for loop to find all instances ===\n";
    std::boyer_moore_searcher bms{search_this.begin(), search_this.end()};
    for(auto pos = std::search(str.begin(), str.end(), bms);
        pos != str.end();
        pos = std::search(pos+search_this.size(), str.end(), bms)) {

        //static_assert(207 == (pos - str.begin()));
        std::cout << "Found " << std::quoted(search_this) << " at index " << (pos - str.begin()) << '\n';
    }

    {
        std::cout << "\n\n=== Using Searchers Directly ===\n\n";

        std::boyer_moore_searcher bms{search_this.begin(), search_this.end()};
        for(auto [pos_b, pos_e] = bms(str.begin(), str.end());
            pos_b != str.end();
            std::tie(pos_b, pos_e) = bms(pos_e, str.end())) {

            //static_assert(207 == (pos - str.begin()));
            std::cout << "Found " << std::quoted(search_this) << " at index " << (pos_b - str.begin()) << '-' << (pos_e-str.begin()) << '\n';
        }

    }
    
    return 0;
}

/**********
    END OF FILE
*************/


