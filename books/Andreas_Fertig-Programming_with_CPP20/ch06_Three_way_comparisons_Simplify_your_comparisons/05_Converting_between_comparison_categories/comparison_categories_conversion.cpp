/*****

References
    Programming with C++20 | Andreas Fertig
    https://en.cppreference.com/w/cpp/language/operator_comparison#Three-way_comparison
    https://en.cppreference.com/w/cpp/language/default_comparisons

    https://en.cppreference.com/w/cpp/utility/compare/strong_ordering
    https://en.cppreference.com/w/cpp/utility/compare/weak_ordering
    https://en.cppreference.com/w/cpp/utility/compare/partial_ordering

6.5 Converting between comparison categories

	This is due to the ability of the different categories to be convertible into a less strict category.
	For example, strong_ordering can be converted into a weak_ordering. By that, we loosen some requirements. 
	The other way around isn’t possible, of course, as there is no way to add requirements to a type.

	Something that has an order has an equivalence check as well. 
	Two objects which are equivalent can be translated to an equality comparison.

	From a strong_ordering, we can derive a weak_ordering, or even a partial_ordering.
	That’s why these types are implicitly convertible to each other in this direction.
	The other way around does not work.

	These implicit conversions happen automatically.


	The compiler automatically determines the common comparison categories among all types.
	This type is then used as the deduced return-type. 
	There is also a type-trait that can identify the common comparison category for you: std::common_comparison_category.


	The different comparison categories and how they relate to each other. Arrows show an is-a implicit conversion ability.

		partial_ordering
			^
			|
		weak_ordering
			^
			|
		strong_ordering

**********/

#include <iostream>
#include <compare>

struct Weak {
    std::weak_ordering operator<=>(const Weak&) const = default;
};

struct Strong {
    std::strong_ordering operator<=>(const Strong&) const = default;
};

struct Combined {
    Weak   w;
    Strong s;
    auto operator<=>(const Combined&) const = default;
};

int main() {
    Combined c;
    static_assert(std::is_same_v<std::weak_ordering, decltype(c <=> c)>);
    return 0;
}

/*****
    END OF FILE
**********/


