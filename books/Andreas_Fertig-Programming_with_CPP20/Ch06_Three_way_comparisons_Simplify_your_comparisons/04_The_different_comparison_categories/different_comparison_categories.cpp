/*****

References
    Programming with C++20 | Andreas Fertig
    https://en.cppreference.com/w/cpp/language/operator_comparison#Three-way_comparison
    https://en.cppreference.com/w/cpp/language/default_comparisons

    https://en.cppreference.com/w/cpp/utility/compare/strong_ordering
    https://en.cppreference.com/w/cpp/utility/compare/weak_ordering
    https://en.cppreference.com/w/cpp/utility/compare/partial_ordering

6.4 The different comparison categories

	The types provided by the standard consist of a strength and a category.
	The naming convention of the types follows the scheme strength_category.

6.4.1 The comparison categories

	In general, every type should either overload
	
	equality	only operator== and operator!=;
	ordering	all comparison operators;
	neither		none of the comparison operators.
	
	With that, we have the comparison category and the required operators, 
	whether they can be defaulted is a separate question.

6.4.2 The comparison strength: strong or weak

	This is only relevant if before we decided that the class provides ordering.

	If we compare two objects, are they equal or equivalent? 
	For example, String earlier is equal and so, the strength is strong. 
	Should String compare the stored name only in a case-insensitive manner, 
	the strength would be weak and the result of two strings being the same would not be equal but equivalent.

	Rule of thumb:
	Use strong if everything that is copied, in the copy constructor, is also part of the comparison.
	If only a subset of what is copied is compared, use weak.
	Subset also means that, if the comparison is done in a special way, as in case-insensitive comparison of a string.
	The strength then is also weak. 
	The type strong_ordering corresponds to the term total ordering in mathematics.

	The types strong_ordering and weak_ordering have three different possible values, greater, equivalent, and less.

6.4.3 Another comparison strength: partial ordering

	partial_ordering has the same three values as weak_ordering: greater, equivalent and less.
	But it has an additional value, unordered.
	We should use this whenever we have a type that is not fully orderable.

	Choose partial_ordering when all six comparison operators are needed, 
	but from some values none of a < b, a == b, and a > b needs to be true.
	
	no STL algorithms will work with a type with a spaceship operator which returns std::partial_ordering.
	The same is true for std::set or std::map.

	We talk about equal, if we use equality comparison. When we use ordering comparison, this is equivalence.


6.4.4 Named comparison functions

	Comparison types and their values
		===========================================================================
		Category			−1		0			+1			Non-numeric values
		===========================================================================
		strong_ordering		less	equal		greater
		weak_ordering		less	equivalent	greater
		partial_ordering	less	equivalent	greater		unordered
		===========================================================================

	Named comparison functions
		==============================================
		Function 							Operation
		==============================================
		is_eq	(partial_ordering cmp)		cmp == 0
		is_neq	(partial_ordering cmp)		cmp != 0
		is_lt	(partial_ordering cmp)		cmp < 0
		is_lteq	(partial_ordering cmp)		cmp <= 0
		is_gt	(partial_ordering cmp)		cmp > 0
		is_gteq	(partial_ordering cmp)		cmp >= 0
		==============================================

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

class MyString {

    const char *    m_data;
    const size_t    m_len;

    char operator[](const size_t pos) const {
        return m_data[pos];
    }

    std::weak_ordering compare(const MyString & other) const {
        
        std::weak_ordering ret_val = std::weak_ordering::equivalent;

        for(size_t i = 0; i < m_len; ++i) {
            if(m_data[i] > other[i]) {
                ret_val = std::weak_ordering::greater;
                break;
            }
            else if(m_data[i] < other[i]) {
                ret_val = std::weak_ordering::less;
                break;
            }
        }

        return ret_val;
    }

    public:
    template<std::size_t N>
    explicit MyString(const char (&src)[N]) 
    : m_data(src), m_len(N) { }

    bool operator==(const MyString & other) const {
        if(m_len != other.m_len) { return false; }  // For Performance

        return compare(other) == 0;
    }

    auto operator<=>(const MyString & other) const {
        return compare(other);
    }

    friend std::ostream & operator<<(std::ostream &os, const MyString & ms);
};

std::ostream & operator<<(std::ostream &os, const MyString & ms) {
    os << ms.m_data;
    return os;
}

void compareMyString(const MyString & ms1, const MyString & ms2) {

    if(ms1 == ms2) {
        std::cout << ms1 << " and " << ms2 << " are equal\n";
    }
    else {
        std::cout << ms1 << " and " << ms2 << " are not equal\n";
        
        if(ms1 < ms2) {
            std::cout << ms1 << " is less than " << ms2 << '\n';
        }
        
        if(ms1 > ms2) {
            std::cout << ms1 << " is greater than " << ms2 << '\n';
        }
        
    }
    std::cout << '\n';
}

int main() {
        MyString ms1{"sample string"};
        MyString ms2{"sample string"};
        MyString ms3{"Sample string"};
        
        compareMyString(ms1, ms2);
        compareMyString(ms1, ms3);
        compareMyString(ms3, ms1);

    return 0;
}

/*****
    END OF FILE
**********/


