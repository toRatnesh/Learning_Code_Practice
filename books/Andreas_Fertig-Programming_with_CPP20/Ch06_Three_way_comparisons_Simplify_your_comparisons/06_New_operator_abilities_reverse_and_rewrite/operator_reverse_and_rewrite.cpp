/*****

References
    Programming with C++20 | Andreas Fertig
    https://en.cppreference.com/w/cpp/language/operator_comparison#Three-way_comparison
    https://en.cppreference.com/w/cpp/language/default_comparisons

6.6 New operator abilities: reverse and rewrite

	In C++20 the compiler can reverse or rewrite comparisons

	It can also reverse operands, if there is a match in the overload set.
	The benefit is that we no longer need the friend-function trick.

	Operator categories
					Equality	Ordering
	Primary			==			<=>
	Secondary		!=			<, >, <=, >=

	For every primary comparison in form a.operator@(b) the compiler may reverse it to b.operator@(a), if this is the best match.
	For every secondary comparison, it allows the compiler to rewrite an expression, a.operator!=(b) then becomes ! a.operator ==(b).

	This feature is also called consistent comparisons.


	How does spaceship work
	We basically need two comparison operations:
		->	Equal (==);
		->	Greater than (>), alternatively less than (<),
	With these two operations we can build the others:
		->	Not equal (!=), is the opposite of equal;
		->	Less than (<), is not equal and not greater than;
		->	Greater than or equal (>=), is the opposite of less than;
		->	Less than or equal (<=), is the opposite of greater.

	This is knowledge that the compiler can also have, 
	and it has it in C++20 where it may reverse operands and rewrite comparison expressions.

**********/

#include <iostream>
#include <cstdint>
#include <compare>

struct CustId {
    uint32_t    m_id;

    bool operator==(const CustId & other) const {
        std::cout << "operator==\n";
        return m_id == other.m_id;
    }
    bool operator<(const CustId & other) const {
        std::cout << "operator<\n";
        return m_id < other.m_id;
    }
    bool operator>(const CustId & other) const {
        std::cout << "operator>\n";
        return m_id > other.m_id;
    } 

    auto operator<=>(const CustId & other) const = default;       
};

auto compareId(const CustId & id1, const CustId & id2) {
    if(id1 == id2) { std::cout << "Ids are same\n"; }
    if(id1 != id2) { std::cout << "Ids are different\n"; } 
    
    if(id1 < id2) { std::cout << "First id is less than second id\n"; }
    if(id1 > id2) { std::cout << "First id is greater than second id\n"; }

    if(id1 <= id2) { std::cout << "First id is less than or equal to second id\n"; }
    if(id1 >= id2) { std::cout << "First id is greater than or equal to second id\n"; }

}

int main() {
    CustId id1{123};
    CustId id2{123};
    CustId id3{345};

    std::cout << "=== comparing " << id1.m_id << " and " << id2.m_id << " ===\n";
    compareId(id1, id2);
    std::cout << "=== comparing " << id1.m_id << " and " << id3.m_id << " ===\n";
    compareId(id1, id3);
    std::cout << "=== comparing " << id3.m_id << " and " << id1.m_id << " ===\n";
    compareId(id3, id1);

    return 0;
}

/*****
    END OF FILE
**********/


