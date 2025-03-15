/*****

References
    Programming with C++20 | Andreas Fertig
    https://en.cppreference.com/w/cpp/language/operator_comparison#Three-way_comparison
    https://en.cppreference.com/w/cpp/language/default_comparisons

Chapter 6 | Threeway comparisons: Simplify your comparisons

    spaceship operator, helps us write less code when defining comparisons

    Consider a basic case where you needed to provide an operator== which did something special.
    For consistency reasons, you usually would have provided operator != as well.
    But what was its implementation?
    Well, in all cases I can remember, the implementation was this:

    bool operator!=(const T& t) { return !(*this == t); }

    That is not special code. It is absolutely trivial, but has to be written, reviewed and maintained. 
    Let’s see how C++20 tackles this corner.


6.3 Writing a class with ordering comparison in C++20

    The spaceship operator in C++ is written as operator<=> and has a dedicated return type
    which can be expressed as less than (−1), equal to (0), or greater than (1),

    With =default, we can request a default implementation from the compiler for the spaceship operator

6.3.1 Memberwise comparison with =default

    Requesting the default spaceship or equalityoperators will lead to a member-wise comparison done by the compiler for us.

    A member-wise comparison is not deep-compared. Just the two pointer addresses are. 
    It depends on your application whether this is the right thing.

    For example, in a scenario where the data behind a pointer is not relevant, only the address of the pointer =default can be enough.
    A memory management class like shared_ptr is an example.

    Whenever the data to which the pointer refers to should be compared, =default is the wrong solution.

    Member-wise comparison goes through the member variables in declaration order from top to bottom.


    the return type of Compare now return std::weak_ordering, one of the new standard types from the <compare> header.

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


