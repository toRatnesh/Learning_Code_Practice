
/*****

References
    Effective Modern C++ | Scott Meyers


Chapter 7: Templates and Generic Programming

    Generic programming — the ability to write code that is independent of the types of objects being manipulated

    It can be used to compute any computable value. That led to template metaprogramming: the creation of programs 
    that execute inside C++ compilers and that stop running when compilation is complete.

Item 47: Use traits classes for information about types

	Consider std::advance
	
	template< class InputIt, class Distance >
	void advance( InputIt& it, Distance n );

	Conceptually, advance just does iter += d, but advance can’t be implemented that way, 
	because only random access iterators support the += operation. 
	Less powerful iterator types have to implement advance by iteratively applying ++ or -- d times.

	There are five categories of iterators:
	1.	Input iterators
	2.	Output iterators
	3.	Forward iterators
	4.	Bidirectional iterators
	5.	Random access iterators

	struct input_iterator_tag {};
	struct output_iterator_tag {};
	struct forward_iterator_tag: public input_iterator_tag {};
	struct bidirectional_iterator_tag: public forward_iterator_tag {};
	struct random_access_iterator_tag: public bidirectional_iterator_tag {};

	we really want to do is implement advance essentially like this:
	template <typename IterT, typename DistT>
	void advance(IterT &iter, DistT d) {
		if (iter is a random access iterator) {
			// use iterator arithmetic for random access iters
			iter += d;
		} else {
			// use iterative calls to ++ or -- for other iterator categories
			if (d >= 0) {
				while (d--)
					++iter;
			} else {
				while (d++)
					--iter;
			}
		}
	}
	
	This requires being able to determine whether iter is a random access iterator, which in turn 
	requires knowing whether its type, IterT, is a random access iterator type. 
	
	In other words, we need to get some information about a type.
	That’s what traits let you do: they allow you to get information about a type during compilation.
	
	The standard technique is to put it into a template and one or more specializations of that template.
	By convention, traits are always implemented as structs, which are called as traits classes.

	The way iterator_traits works is that for each type IterT, 
	a typedef named iterator_category is declared in the struct iterator_traits<IterT>. 
	This typedef identifies the iterator category of IterT.
	
	template<typename IterT>
	struct iterator_traits {
		typedef typename IterT::iterator_category iterator_category;
		...
	};
	
	because there’s no such thing as a pointer with a nested typedef, 
	the iterator_traits implementation handles iterators that are pointers
	
	template<typename T>		// partial template specialization for built-in pointer types
	struct iterator_traits<T*> {
		typedef random_access_iterator_tag iterator_category;
		...
	};
	
	
	template <typename IterT, typename DistT>
	void advance(IterT &iter, DistT d) {
		if (typeid(typename std::iterator_traits<IterT>::iterator_category) == 
			typeid(std::random_access_iterator_tag)) {
		...
	}

	the if statement is evaluated at runtime
	Why do something at runtime that we can do during compilation?
	
	To get advance to behave the way we want, all we have to do is create multiple versions of an overloaded 
	function containing the “guts” of advance, declaring each to take a different type of iterator_category object.
	
	template <typename IterT, typename DistT>       // impl for random access iterators
	void doAdvance(IterT &iter, DistT d, std::random_access_iterator_tag) {
		iter += d;
	}
	
	template <typename IterT, typename DistT>		// impl for bidirectional iterators
	void doAdvance(IterT &iter, DistT d, std::bidirectional_iterator_tag) {
		if (d >= 0) {
			while (d--)
				++iter;
		} else {
			while (d++)
				--iter;
		}
	}
	
	template <typename IterT, typename DistT>	// impl for input iterators
	void doAdvance(IterT &iter, DistT d, std::input_iterator_tag) {
		if (d < 0) {
			throw std::out_of_range("Negative distance"); // see below
		}
		while (d--)
			++iter;
	}
	
 
	// call the version // of doAdvance // that is // appropriate for // iter’s iterator // category
	template <typename IterT, typename DistT>
	void advance(IterT &iter, DistT d)
	{
		doAdvance(                                           
			iter, d,                                         
			typename                                         
			std::iterator_traits<IterT>::iterator_category() 
		);                                                   
	} 	
	
Summary:
	.	Traits classes make information about types available during compilation.
		They’re implemented using templates and template specializations.		
	.	In conjunction with overloading, traits classes make it possible to perform compile-time if...else tests on types.

**********/

#include <iostream>
#include <string>
#include <iterator>
#include <exception>
#include <vector>
#include <list>

template<typename T, typename U>
struct x_is_same : std::false_type {};

template<typename T>
struct x_is_same<T, T> : std::true_type {};    // specialized template


template<typename T>
struct x_remove_cv { using type = T; };

template<typename T>
struct x_remove_cv<const T> { using type = T; };

template<typename T>
struct x_remove_cv<volatile T> { using type = T; };

template<typename T>
struct x_remove_cv<const volatile T> { using type = T; };



template<typename Iter>
struct x_iterator_traits {
    using iterator_category = typename Iter::iterator_category;
};

template<typename Iter, typename Distance>
void x_doAdvance(Iter & it, Distance n, std::random_access_iterator_tag) {
    it = it + n;
}

template<typename Iter, typename Distance>
void x_doAdvance(Iter & it, Distance n, std::bidirectional_iterator_tag) {
    if(n >= 0) {
        while(n--) { ++it; }
    } else {
        while(n++) { --it; }
    }    
}

template<typename Iter, typename Distance>      // it will also work for forward_iterator_tag
void x_doAdvance(Iter & it, Distance n, std::input_iterator_tag) {
    if(n >= 0) {
        while(n--) { ++it; }
    } else {
        throw std::out_of_range("negative distance value for input iterator is invalid");
    }
}

template<typename Iter, typename Distance>
void x_doAdvance(Iter & it, Distance n, std::output_iterator_tag) {
    if(n >= 0) {
        while(n--) { ++it; }
    } else {
        throw std::out_of_range("negative distance value for output iterator is invalid");
    }
}

template<typename Iter, typename Distance>
void x_advance(Iter & it, Distance n) {
    return x_doAdvance(it, n, typename x_iterator_traits<Iter>::iterator_category{});
}

int main() {

    {
        static_assert(x_is_same<int, int>::value);
        static_assert(not x_is_same<int, double>::value);
    }

    {
        static_assert(x_is_same<int, x_remove_cv<const int>::type>::value);
        static_assert(x_is_same<int, x_remove_cv<volatile int>::type>::value);
        static_assert(x_is_same<int, x_remove_cv<const volatile int>::type>::value);
    }

    {
        std::vector<int> lvec{1, 2, 3, 4, 5};
        auto it = lvec.begin();
        std::cout << *it << '\n';
        x_advance(it, 2);
        std::cout << *it << '\n';
    }

    {
        std::list<int> lvec{1, 2, 3, 4, 5};
        auto it = lvec.begin();
        std::cout << *it << '\n';
        x_advance(it, 2);
        std::cout << *it << '\n';
    }

    return 0;
}

/*****
    END OF FILE
**********/

