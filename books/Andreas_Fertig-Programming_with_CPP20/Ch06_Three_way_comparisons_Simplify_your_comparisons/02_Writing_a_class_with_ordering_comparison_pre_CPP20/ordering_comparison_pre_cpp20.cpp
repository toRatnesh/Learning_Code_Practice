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

6.2 Writing a class with ordering comparison, pre C++20

    Every time we need to sort unique objects of a class, it involves the operators
    <, >, <=, >=, == and !=  to establish an order between the objects which are sorted.

    We need to implement all six comparison functions in order to achieve this

    A common approach here is to have one function which does the actual comparison, let’s name it Compare.
    It returns Ordering, a type with three different values, less (−1), equal (0), or greater (1).

    If We have implemented these six operators for a class and we also want 
    to support the comparison of this class with a different type than number of operations increases 

**********/

#include <iostream>

class MyString {

    using ordering_t = enum class Ordering {
        LessThan    = -1,
        Equal       = 0,
        GreaterThan = 1
    };

    const char *    m_data;
    const size_t    m_len;

    char operator[](const size_t pos) const {
        return m_data[pos];
    }

    ordering_t compare(const MyString & other) const {
        
        ordering_t ret_val = Ordering::Equal;

        for(size_t i = 0; i < m_len; ++i) {
            if(m_data[i] > other[i]) {
                ret_val = Ordering::GreaterThan;
                break;
            }
            else if(m_data[i] < other[i]) {
                ret_val = Ordering::LessThan;
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

        return compare(other) == Ordering::Equal;
    }

    bool operator!=(const MyString & other) const {
        return !(*this == other);
    }

    bool operator<(const MyString & other) const {
        return compare(other) == Ordering::LessThan;
    }

    bool operator<=(const MyString & other) const {
        return compare(other) != Ordering::GreaterThan;
    }

    bool operator>(const MyString & other) const {
        return compare(other) == Ordering::GreaterThan;
    }

    bool operator>=(const MyString & other) const {
        return compare(other) != Ordering::LessThan;
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

    {
        MyString ms1{"sample string"};
        MyString ms2{"sample string"};
        
        compareMyString(ms1, ms2);
    }

    {
        MyString ms1{"Sample string"};
        MyString ms2{"sample string"};
        
        compareMyString(ms1, ms2);
    }

    {
        MyString ms1{"sample string"};
        MyString ms2{"Sample string"};
        
        compareMyString(ms1, ms2);
    }    
    
    return 0;
}

/*****
    END OF FILE
**********/

