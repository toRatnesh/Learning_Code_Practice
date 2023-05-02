/************

References
    C++17 - The Complete Guide | Nicolai M. Josuttis

9. Class Template Argument Deduction (CTAD)

    Since C++17, you do not need to specify the template arguments explicitly, if the constructor is able to deduce all template parameters using CTAD.
    std::complex c{5.1,3.3};			// OK: std::complex<double> deduced
    std::vector v2 {"hello", "world"};	// OK: std::vector<const char*> deduced

9.2 Deduction Guides
	We use deduction guides to provide additional CTAD or fix existing deductions defined by constructors
	The deduction guide only matters for the deduction of the template types. It is irrelevant for the actual constructor call after the types are deduced

	NOTE: Decay means that raw arrays convert to pointers and top-level qualifiers, such as const and references, are ignored

9.2.6 Standard Deduction Guides

Deduction Guides for Pairs and Tuples
	std::pair and std::tuple constructors take argument by reference 
	so deduction guide is used to ensure that CTAD uses the decayed type of the passed argument

Deduction from Iterators
	to deduce the type of the elements from iterators that define a range for initialization, containers have a deduction guide such as
	template<typename Iterator>
	std::vector(Iterator, Iterator) -> std::vector<typename iterator_traits<Iterator>::value_type>;

std::array<> Deduction
	deduce both the element type and the number of elements
	template<typename T, typename... U>
	array(T, U...) -> array<enable_if_t<(is_same_v<T,U> && ...), T>, (1 + sizeof...(U))>;
	
(Unordered) Map Deduction
	for containers that have key/value pairs like std::map deduction guide is complex
	
	for example, for the following constructor:
	map(initializer_list<pair<const Key, T>>, 
		const Compare& = Compare(), 
		const Allocator& = Allocator());
		
	the following deduction guide:
	template<typename Key, typename T,
		typename Compare = less<Key>,
		typename Allocator = allocator<pair<const Key, T>>>
	map(initializer_list<pair<const Key, T>>, 
		Compare = Compare(), 
		Allocator = Allocator())
	-> map<Key, T, Compare, Allocator>;
	
	As all arguments are passed by value, this deduction guide enables that the type of a passed comparator or allocator decays as discussed.

No Deductions Guides for Smart Pointers
	smart pointers do not have deduction guide 
	the corresponding constructor is a template, so that no implicit deduction guide applies

	namespace std {
		template<typename T> 
		class shared_ptr {
			public:
			...
			template<typename Y> explicit shared_ptr(Y* p);
			...
		};
	}
	
	if we provide deduction guide like this
	namespace std {
		template<typename Y> shared_ptr(Y*) -> shared_ptr<Y>;
	}
	
	type deduction for array will fail
	std::shared_ptr sp{new int[10]}; // OOPS: would deduces shared_ptr<int>

*************/

#include <iostream>
#include <utility>
#include <string>
#include <vector>
#include <set>
#include <array>
#include <map>
#include <memory>

int main() {
    
    {
        std::clog << "=== Deduction Guides for Pairs and Tuples\n";

        std::pair str_pair{"string", "pair"};
        static_assert(std::is_same_v<decltype(str_pair), std::pair<char const *, char const *>>); // decay to char cost * from char array
        std::pair int_pair{4, 5};
        static_assert(std::is_same_v<decltype(int_pair), std::pair<int, int>>);
        std::pair str_int_pair{"CTAD", 5};
        static_assert(std::is_same_v<decltype(str_int_pair), std::pair<char const *, int>>);

        std::tuple atuple{4, true, "CTAD", nullptr};
        static_assert(std::is_same_v<decltype(atuple), std::tuple<int, bool, char const *, nullptr_t>>);
    }

    {
        std::clog << "=== Deduction from Iterators\n";
        std::set int_set{1,2,3,4,5,6,7,8,9};

        /* type deduced using
        vector(Iterator, Iterator) -> vector<typename iterator_traits<Iterator>::value_type>; */
        std::vector l_vec(int_set.begin(), int_set.end());
        static_assert(std::is_same_v<decltype(l_vec), std::vector<int>>);

        /* when using curly brackets, the two iterator arguments are taken as elements of an initializer list 
        (which has higher priority according to the overload resolution rules) */
        std::vector l_vec_2{int_set.begin(), int_set.end()};
        static_assert(std::is_same_v<decltype(l_vec_2), std::vector<std::set<int>::iterator>>);
        static_assert( ! std::is_same_v<decltype(l_vec_2), std::vector<int>>);

        std::vector str_vec{"Deducing from", " iterators"};
        static_assert(std::is_same_v<decltype(str_vec), std::vector<char const *>>);

        /* following code is runtime error

        The problem is that string literals convert to character pointers, which are valid iterators. 
        Thus, we pass two iterators that do not point to the same object. In other words: We pass an invalid range. 
        Depending on where the two literals are stored, 
        you get a std::vector<const char> with an arbitrary number of elements. 
        If it is too big you get a bad_alloc exception, or 
        you get a core dump because there is no distance at all, or 
        you get a range of some undefined characters stored in between.

	for vector prefer list initialization 

        */
        std::vector str_vec_2("Deducing from", " iterators"); // runtime error
        static_assert( ! std::is_same_v<decltype(str_vec_2), std::vector<char const *>>);

    }

    {
        std::clog << "=== std::array<> Deduction\n";

        std::array int_arr{1,2,3,4,5};
        static_assert(std::is_same_v<decltype(int_arr), std::array<int, 5>>);

        /* no implicit conversion allowed for array */
        //std::array invalid_arr{1,2,3,4.5,5}; // error: class template argument deduction failed:
    }

    {
        std::clog << "=== (Unordered) Map Deduction\n";
        {
            const int key1 = 1;
            const int val1 = 2;
            const int key2 = 3;
            const int val2 = 4;
            std::pair p1 = {key1, val1};
            std::pair p2 = {key2, val2};
            std::map map_1{p1, p2};
            static_assert(std::is_same_v<decltype(map_1), std::map<int, int>>);
        }

        {
            int key1 = 1, val1 = 2, key2= 3, val2 = 4;
            std::pair p1 = {key1, val1};
            std::pair p2 = {key2, val2};
            std::map map_2{p1, p2};
            static_assert(std::is_same_v<decltype(map_2), std::map<int, int>>);    
        }
    }

    {
        std::clog << "=== No Deductions Guides for Smart Pointers\n";

        //std::shared_ptr sp1{new int(7)}; // error: class template argument deduction failed
        std::shared_ptr<int> sp2{new int(7)};

        std::shared_ptr<std::string> sp3{new std::string[10], [](std::string * p){ delete [] p; }};
        std::shared_ptr<std::string> sp4{new std::string[10], std::default_delete<std::string []>()};
    }

	return 0;
}

/*******
    END OF FILE
*********/


