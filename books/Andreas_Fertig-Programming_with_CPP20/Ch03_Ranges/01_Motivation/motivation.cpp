/*****

References

    Programming with C++20 | Andreas Fertig
	https://en.cppreference.com/w/cpp/ranges


Chapter 3 | Ranges: The next generation STL

	Ranges are a new element of the STL that make using algorithms more concise and add the ability to write code in a functional style.
	
3.1 Motivation

	Ranges improve the STL in various ways, as we will see in this section.

3.1.1 Avoid code duplication

	Consider follwing example

	const std::string firstText{"Hello"};
	const std::string secondText{"Bello"};
	const bool equal = std::equal(firstText.begin(), firstText.end(), secondText.begin());

	The number of times one needed to apply an algorithm only to a portion of a container is vanishing small.
	Using the entire container is a much more common pattern.

	The code below does the same thing as before.
	The only difference is that this code uses ranges:

	const bool equal = std::ranges::equal(firstText, secondText);

	Ranges, as their name implies, work with the entire range of a container, 
	or better a collection of items, as we can apply filters and other operations on them.

3.1.2 Consistency

	struct Container {};	// A Container without begin
	int* begin(Container);	// B Free-function begin for Container

	struct OtherContainer {	// C Container with begin
		int* begin();
	};

	void Use(auto& c)
	{
		begin(c);			// D Call ::begin(Container)
		std::begin(c);		// E Call STL std::begin
	}

	The code as presented will not compile for either container type.

	void Use(auto& c)
	{
		using std::begin;	// E Bring std::begin in the namespace
		
		//F Now both functions are in scope
		begin(c);
	}

	The code now behaves correctly. In the case of a Container object, ::begin is called, 
	and for OtherContainer, std::begin calls OtherContainer::begin.

	Issue:
	1.	You have to know this. The code is not necessarily obvious.
	2.	Assume std::begin would perform some checks on the type.
		However, our hand-rolled ::begin would still not have such a check.
		
	Ranges also bring us consistency, helping in the situation just described.

	void Use(auto& c)
	{
		// G Use ranges
		std::ranges::begin(c);
	}

	By using std::ranges::begin, we get the consistent potential check the STL might perform for a begin function,
	plus this version works with the free and member function and calls the appropriate one.

3.1.3 Safety

	Consider follwing example:
	
	auto it = std::begin(std::string{"C++"});			// Undefined Behavior
	auto it = std::ranges::begin(std::string{"Urg"});	// compile-time error.
	
	Range version of begin comes with a check, ensuring that we do not accidentally pass a temporary.

	We are looking here at a so-called customization point.
	
	Thanks to ranges, we get consistent constraint checking.
	And yes, this constraint checking is often done by Concepts.

3.1.4 Composability

	While STL algorithms are a great thing, they are not composable.
	Ranges address this.
	
	std::vector<int> numbers{2, 3, 4, 5, 6};
	auto results = numbers | std::views::filter(is_odd) | std::views::transform([](int n) { return n * 2; });
	
**********/

#include <iostream>
#include <string>
#include <ranges>
#include <algorithm>
#include <vector>

struct WithBegin {
    char *  m_arr;

    auto begin() { return m_arr; }
};

struct WithoutBegin {
    char *  m_arr;
};

auto begin(WithoutBegin & wb) { return wb.m_arr; }

void use(auto & cont) {
    std::cout << "Calling begin() and std::begin()\n";
    // this code will not compile becase either one will not work
    [[maybe_unused]] auto it1 = begin(cont);
    [[maybe_unused]] auto it2 = std::begin(cont);
}

void enhancedUse(auto & cont) {
    // this code will compile, but has issues
    std::cout << "Calling begin() and using std::begin\n";
    using std::begin;
    [[maybe_unused]] auto it = begin(cont);
}

void rangeUse(auto & cont) {
    std::cout << "Calling std::ranges::begin\n";
    [[maybe_unused]] auto it = std::ranges::begin(cont);
}

int main() {

    std::cout << "=== Avoid code duplication ===\n";

    const std::string str1{"Sample string"};
    const std::string str2{"Sample string"};

    if(std::equal(str1.cbegin(), str1.cend(), str2.cbegin())) {
        std::cout << str1 << " and " << str2 << " are equal\n";
    } else {
        std::cout << str1 << " and " << str2 << " are not equal\n";
    }

    if(std::ranges::equal(str1, str2)) {
        std::cout << str1 << " and " << str2 << " are equal\n";
    } else {
        std::cout << str1 << " and " << str2 << " are not equal\n";
    }


    std::cout << "=== Consistency ===\n";
    {
        WithBegin    wb;
        //use(wb);            // CE error: invalid initialization of reference of type 'WithoutBegin&' from expression of type 'WithBegin'    
        enhancedUse(wb);
        rangeUse(wb);
    }
    {
        WithoutBegin wb;
        //use(wb);            // CE error: no matching function for call to 'begin(WithoutBegin&)'            
        enhancedUse(wb);
        rangeUse(wb);
    }


    std::cout << "=== Safety ===\n";
    
    [[maybe_unused]] auto it1 = std::begin(std::string("temporary string"));  // clang warning: object backing the pointer will be destroyed at the end of the full-expression [-Wdangling-gsl]
    
    // CE error: no match for call to '(const std::ranges::__access::_Begin) (std::string)'
    //[[maybe_unused]] auto it2 = std::ranges::begin(std::string("temporary string"));
    std::cout << "std::ranges::begin gives CE for temporary object while std::begin doesn't\n";

    
    std::cout << "=== Composability ===\n";

    std::vector<int> numbers{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    auto is_odd = [](const auto & num) { return num & 1; };

    {
        std::vector<int>    odd_numbers_vec;
        std::vector<int>    result_vec;

        std::copy_if(numbers.begin(), numbers.end(), 
                    std::back_inserter(odd_numbers_vec), 
                    is_odd);

        std::transform(odd_numbers_vec.begin(), odd_numbers_vec.end(), 
                    std::back_inserter(result_vec), 
                    [](const auto & num) { return num * 2; });
        
        for(const auto & elem : result_vec) {
            std::cout << elem << ',';
        }
        std::cout << '\n';
    }

    auto result_vec = numbers | std::views::filter(is_odd) 
                        | std::views::transform([](const auto & num) { return num * 2; });
	for(const auto & elem : result_vec) {
        std::cout << elem << ',';
    }
    std::cout << '\n';

	return 0;
}

/*****
    END OF FILE
**********/

