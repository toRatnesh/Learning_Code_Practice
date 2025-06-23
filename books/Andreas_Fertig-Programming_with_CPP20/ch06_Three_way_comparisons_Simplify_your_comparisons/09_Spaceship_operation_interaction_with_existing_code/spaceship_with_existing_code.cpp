/*****

References
    Programming with C++20 | Andreas Fertig
    https://en.cppreference.com/w/cpp/language/operator_comparison#Three-way_comparison
    https://en.cppreference.com/w/cpp/language/default_comparisons

6.9 Spaceship-operation interaction with existing code

	Suppose you have a legacy struct from pre-C++20 times.
	It consists of some members and the equality and less-than operators.

	Now, if we have to write a new class ShinyCpp20Class which has a field of type Legacy.
	It should be ordering comparable, preferably by using the spaceship operator.

	The question is, how do we do that?
	we can just default the spaceship operator.
	The only special thing is that we have to be specific about the return-type of operator<=>.
	We cannot just say auto.



A word about upgrading to C++20

	Consistent comparisons makes the language stronger and reduces the places where we can make mistakes.
	C++20 does clean up some bad code we could have written before C++20, sadly leading to some interesting situations.

	struct A {
		bool operator==(B&) const { return true; }			// A
	};

	struct B {
		bool operator==(const A&) const { return false; }	// B
	};

	Assume that it compiled in C++17, it implies that it worked correctly in C++17, missing const or not.
	Remember that in C++20 we have consistent comparisons? 

	They are consistent even without the spaceship operator. Why? 
	Because for the equality operator, it allows the compiler to reverse the arguments.
	When it does this with the code, A becomes the better match in the overload set, because it does not have the const. 
	Using B requires an internal const-cast of the compiler for object A.
	These additional actions make A the better match, as there is none required.	


NOTES:

	-> Consistent comparisons are a valuable feature that can take a lot of boiler-plate code from our plate.
		At the same time it ensures that our comparisons are heterogeneous and with that consistent.
	-> The compiler may reverse every comparison of the form a.operator@(b): the compiler may change it to b.operator@(a), if this is the best match.
	-> For that reason you no longer need the friend-trick, just declare your comparison operators as member functions.
	-> The compiler also performs rewrites where a.operator!=(b) can be rewritten to !a.operator==(b).
	-> We can =default all comparison operators who take the class itself as an argument.
	-> constexpr can be added or removed when using =default.
	-> Remember that =default performs a member-wise comparison.
		This is the same meaning for the comparison operators as for the special member functions like the copy constructor.
	-> Member-wise comparison goes through all members in declaration order from top to bottom.
	-> When defaulting comparison operators, prefer the primary operators.
		Since they provide the full complement of all comparisons and the compiler can rewrite them, this is all you need.
	-> When you default operator<=>, you automatically also get the equality comparison operators.
		However, if you provide your own operator<=> implementation, also provide your own operator== version. Refrain from defaulting operator== in this case, as it still defaults to member-wise comparison.
	-> You need to include the <compare> header to get the new std-types.
	-> Invoke <=> when you ask for comparison, use == when you ask for equality.

**********/

#include <iostream>
#include <compare>

struct LegacyPreCpp20 {
    int m_val;

    bool operator==(const LegacyPreCpp20 & other) const {
        return m_val == other.m_val;
    }

    bool operator<(const LegacyPreCpp20 & other) const {
        return m_val < other.m_val;
    }

};

class NewClassCpp20 {
    LegacyPreCpp20 m_a;
    LegacyPreCpp20 m_b;

    public:
    NewClassCpp20(const int a, const int b) 
    : m_a{a}, m_b{b} {}

    // auto     DO NOT USE AUTO RETURN VALUE USE ONLY std::weak_ordering
    std::weak_ordering 
    operator<=>(const NewClassCpp20 & other) const = default;
};

template<typename T>
void compareIt(const T & t1, const T & t2) {
    const auto res = t1 <=> t2;
    if(res == 0) {
        std::puts("same");
    }
    else if(res < 0){
        std::puts("different - less");
    }
    else {
        std::puts("different - greater");
    }
}

// A word about upgrading to C++20
struct B;
struct A {
    bool operator==(B&) const {
        std::cout << "operator==(B&)\n";
        return true; 
    }			// A
};

struct B {
    bool operator==(const A&) const { 
        std::cout << "operator==(const A&)\n";
        return false; 
    }	// B
};

int main() {
    {
        std::cout << "=== default spaceship operator for legacy ===\n";
        NewClassCpp20 na{13, 11};
        NewClassCpp20 nb{13, 11};
        NewClassCpp20 nc{10, 12};

        compareIt(na, nb);
        compareIt(na, nc);
        compareIt(nc, na);
    }

    {
        std::cout << "\n=== A word about upgrading to C++20 ===\n";

        {
            A a;
            B b;

            if(a == b) { std::cout << "same - 1\n"; }
            if(b == a) { std::cout << "same - 2\n"; }            
        }

        {
            const A a;
            const B b;

            if(a == b) { std::cout << "same - 1\n"; }
            if(b == a) { std::cout << "same - 2\n"; }            
        }

        {
            A a;
            const B b;

            if(a == b) { std::cout << "same - 1\n"; }
            if(b == a) { std::cout << "same - 2\n"; }            
        }
    }

    return 0;
}

/*****
    END OF FILE
**********/


