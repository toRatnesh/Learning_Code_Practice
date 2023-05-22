/*********

References
    C++17 - The Complete Guide | Nicolai M. Josuttis
    https://en.cppreference.com/w/cpp/utility/variant

Chapter 16 std::variant<>
    std::variant<>
        a new union class
        supports a new way of polymorphism and dealing with inhomogeneous collections
        allows us to deal with elements of different data types  without the need for a common base class and pointers (raw or smart).

16.4 Polymorphism and Inhomogeneous Collections with std::variant
	std::variant enables a new form of polymorphism and dealing with inhomogeneous collections
	compile-time polymorphism with a close set of data types
	we can program that at runtime for different types different functions/methods are called (without any need for virtual functions, references, and pointers)

16.4.3 Comparing variant Polymorphism
	pros and cons of using std::variant<> for polymorphism and inhomogeneous collections
	Pros:
		don’t need common base types (non-intrusive)
		don’t have to use pointers for inhomogeneous collections
		no need for virtual member functions
		value semantics (no access of freed memory or memory leaks).
		Elements in a vector are located together
	Cons:
		close set of types (you have to know all alternatives at compile time)
		elements all have the size of the biggest element type
		copying elements might be more expensive

************/

#include <iostream>
#include <string>
#include <variant>
#include <vector>
#include <iomanip>


template<typename ...Ts>
struct Overload : public Ts... {
    using Ts::operator()...;
};

template<typename ...Ts>
Overload(Ts...) -> Overload<Ts...>;


class S {
    int     m_ival;
    double  m_dval;
    public:
    S(int ival, double dval) : m_ival{ival}, m_dval{dval} { }
    void display() const { 
        std::cout << '{' << m_ival << ',' << m_dval << '}';
    }
    friend std::ostream & operator<<(std::ostream & os, const S & sobj);
};

std::ostream & operator<<(std::ostream & os, const S & sobj) {
    os << '{' << sobj.m_ival << ',' << sobj.m_dval << '}';
    return os;
} 

int main() {
    using var_elem_t = std::variant<int, double, std::string, S>;
    std::vector<var_elem_t> coll{23, 34.56, "sample string", S{7, 8.19}};

    // using if constexpr to handle diff types differently
    std::cout << "=== using if constexpr to handle diff types differently ===\n";
    for(const auto & elem : coll) {
        std::visit([](const auto & val){
                if constexpr(std::is_convertible_v<decltype(val), std::string>) {
                    std::cout << std::quoted(val) << ' ';
                } else if constexpr(std::is_same_v<decltype(val), const S &>) {
                    val.display();
                }else {
                    std::cout << val << ' ';
                }
            }, elem);
    }
    std::cout << '\n';

    std::cout << "\n=== using overload to handle diff types differently ===\n";
    // using overload to handle diff types differently
    for(const auto & elem : coll) {
        std::visit(Overload{
            [](const std::string & val){ std::cout << std::quoted(val) << ' '; },
            [](const S & val) { std::cout << val << ' '; },
            [](const auto & val) { std::cout << val << ' '; }
            },  elem);

    }
    std::cout << '\n';

    return 0;
}

/*********
    END OF FILE
************/


