/*****

References

    Effective Modern C++ | Scott Meyers
    https://en.cppreference.com/w/cpp/iterator/basic_const_iterator

Item 13: Prefer const_iterators to iterators

	const_iterators are the STL equivalent of pointers-to-const.
	They point to values that may not be modified.

	In the example code
	The casts aren’t strictly necessary, because it was possible to get const_iterators in other ways 
	(e.g., you could bind values to a reference-to-const variable, then use that variable in place of values in your code), 
	but one way or another, the process of getting const_iterators to elements of a non-const container involved some amount of contorting.

	const_iterators simply don’t convert to iterators

C++11
	const_iterators are both easy to get and easy to use. 
	The container member functions cbegin() and cend() produce const_iterators, even for non-const containers, 
	and STL member functions that use iterators to identify positions (e.g., insert and erase) actually use const_iterators.

	C++11 added the non-member functions begin and end

C++14
	C++14 added the non-member functions cbegin, cend, rbegin, rend, crbegin, and crend
	
Using cbegin() in C++11
	template <class C>
	auto cbegin(const C& container)->decltype(std::begin(container))
	{
		return std::begin(container); // see explanation below
	}

	Invoking the non-member begin function (provided by C++11) on a const container yields a const_iterator, 
	and that iterator is what this template returns.

Summary
	
	• Prefer const_iterators to iterators.
	• In maximally generic code, prefer non-member versions of begin, end, rbegin, etc., over their member function counterparts.	

**********/

#include <iostream>
#include <vector>
#include <algorithm>

template<typename Cont>
void display(const Cont & cont) {
    for(const auto & elem : cont) {
        std::cout << elem << ' ';
    }
    std::cout << '\n';
}

template<typename Cont, typename Val>
void findAndInsert(Cont & cont, const Val & tval, const Val & ival) {
    auto l_it = std::find(std::cbegin(cont), std::cbegin(cont), tval);
    cont.insert(l_it, ival);
}

template<typename Cont>
auto cbegin_cpp11(const Cont & cont) -> decltype(std::begin(cont))
{
    return std::begin(cont);
}

template<typename Cont>
auto cend_cpp11(const Cont & cont) -> decltype(std::end(cont))
{
    return std::end(cont);
}

int main() {

    {   std::cout << "=== C++98 alternative for const iterator ===\n";

        typedef std::vector<int>::iterator          Iter_t;
        typedef std::vector<int>::const_iterator    ConstIter_t;

        std::vector<int> lvec{23, 45, 76, 38, 92, 37, 93, 26};
        display(lvec);

        ConstIter_t l_it = std::find(static_cast<ConstIter_t>(lvec.begin()),
                                     static_cast<ConstIter_t>(lvec.end()), 37);
        
        // error: no matching function for call to '__gnu_cxx::__normal_iterator<int*, std::vector<int> >::__normal_iterator(ConstIter_t&)'
        // lvec.insert(static_cast<Iter_t>(l_it), 84);
    }

    {   std::cout << "=== C++11 member cbegin() and cend() ===\n";
        std::vector<int> lvec{23, 45, 76, 38, 92, 37, 93, 26};
        display(lvec);

        auto l_it = std::find(lvec.cbegin(), lvec.cend(), 37);
        lvec.insert(l_it, 84);
        display(lvec);
    }

    {   std::cout << "=== C++14 non-member cbegin() and cend() ===\n";

        std::vector<int> lvec{23, 45, 76, 38, 92, 37, 93, 26};
        display(lvec);

        findAndInsert(lvec, 37, 84);
        display(lvec);
    }

    {   std::cout << "=== Alternative for cbegin() and cend() in c++11 ===\n";

        std::vector<int> lvec{23, 45, 76, 38, 92, 37, 93, 26};
        display(lvec);

        auto l_it = std::find(cbegin_cpp11(lvec), cend_cpp11(lvec), 37);
        lvec.insert(l_it, 84);
        display(lvec);
    }

    return 0;
}

/*****
    END OF FILE
**********/


