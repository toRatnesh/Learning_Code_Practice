/*****

References

    Programming with C++20 | Andreas Fertig
	https://en.cppreference.com/w/cpp/ranges
    https://en.cppreference.com/w/cpp/ranges#Range_adaptors

Chapter 3 | Ranges: The next generation STL

	Ranges are a new element of the STL that make using algorithms more concise and add the ability to write code in a functional style.

3.6 A range adaptor

	Their purpose is to transform ranges into views, and by that allow us to create the nice function programming style pipelines

	Although the pipe syntax is the most frequently used, there is another way.
	We can create range adaptors like objects and pass them to each other.
	
	We can have three different syntaxes for creating a range adaptor.
		range | adaptor(args...)
		adaptor(range, args...)
		adaptor(args...)(range)
		
3.6.1 A custom range adaptor
	We can create such a custom adaptor with the help of a lambda
	Add a function and inside this function use actual range adaptor 
	Be sure to capture by-copy here because this lambda is returned by the function.

**********/

#include <iostream>
#include <ranges>
#include <vector>
#include <algorithm>

auto addCurrencySymbol(const std::string symbol) {
    return std::views::transform([symbol](const int val) { return (std::to_string(val) + symbol); });
}

int main() {
    const std::vector<int>  nums_vec{1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::cout << "=== range adaptor ===\n";
    {
        auto res = nums_vec | 
            std::views::filter([](const int val) { return not (val & 1);}) |
            std::views::transform([](const int val) { return (val * 2); });

        for(const auto & elem: res) {
            std::cout << elem << ',';
        }
        std::cout << '\n';
    }

    {
        auto filt = std::views::filter(nums_vec, [](const int val) { return not (val & 1);});
        auto res = std::views::transform(filt, [](const int val) { return (val * 2); });

        for(const auto & elem: res) {
            std::cout << elem << ',';
        }
        std::cout << '\n';
    }

    {
        auto filt = std::views::filter([](const int val) { return not (val & 1);})(nums_vec);
        auto res = std::views::transform([](const int val) { return (val * 2); })(filt);
        
        for(const auto & elem: res) {
            std::cout << elem << ',';
        }
        std::cout << '\n';
    }
    std::puts("");

    std::cout << "=== custom range adaptor ===\n";
    {
        const std::string symbol{"₹"};

        auto res = nums_vec | 
            std::views::filter([](const int val) { return not (val > 4);}) |
            std::views::transform([symbol](const int val) { return (std::to_string(val) + symbol); });

        for(const auto & elem: res) {
            std::cout << elem << ',';
        }
        std::cout << '\n';        
    }

    {
        const std::string symbol{"₹"};

        auto res = nums_vec | 
            std::views::filter([](const int val) { return not (val > 4);}) |
            addCurrencySymbol(symbol);

        for(const auto & elem: res) {
            std::cout << elem << ',';
        }
        std::cout << '\n';        
    }

	return 0;
}

/*****
    END OF FILE
**********/

