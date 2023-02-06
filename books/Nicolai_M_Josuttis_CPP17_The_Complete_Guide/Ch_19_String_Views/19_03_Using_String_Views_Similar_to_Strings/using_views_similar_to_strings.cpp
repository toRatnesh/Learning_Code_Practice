/*******

References
    C++17 - The Complete Guide | Nicolai M. Josuttis
	https://en.cppreference.com/w/cpp/string/basic_string_view

19 String Views

std::string_view objects refer to external character sequences without owning them.
The object can be considered as a reference to a character sequence.
It is also potentially dangerous, because similar to raw pointers it is up to the programmer to ensure that the referred character sequences is still valid

19.3 Using String Views Similar to Strings

An example of a std::string_view is

template <typename T>
void printElems(const T& coll, std::string_view prefix = std::string_view{}) {
    for (const auto& elem : coll) {
        if (prefix.data()) {  // check against nullptr
            std::cout << prefix << ' ';
        }
        std::cout << elem << '\n';
    }
}

if we declare the function as follows:

template<typename T>
void printElems(const T& coll, const std::string& prefix = std::string{});

If we pass a string literal, the call creates a temporary string which will allocate memory unless the string is short and the short string optimization is used. 
By using a string view instead, no allocation is needed, because the string view only refers to the string literal.

Using string views can also provide significant performance boosts when sorting substrings.

NOTE: creating a string from a string view is a relative expensive operation

19.3.1 String View Considered Harmful

	String views are in fact more dangerous than string references or smart pointers.
	They behave more like raw character pointers.

Don’t Assign Strings to String Views

	a function returning a new string:
	std::string retString();

	Assigning it to a string or an object declared with auto is safe
	auto std::string s1 = retString();	// safe

	Assigning the return value to a string reference is, if possible, pretty safe as long we use the object locally because references extend the lifetime of return values to the end of their lifetime
		  std::string& s2	= retString();	// Compile-Time ERROR (const missing)
	const std::string& s3	= retString();	// s3 extends lifetime of returned string
				auto&& s4	= retString();	// s4 extends lifetime of returned string

	For a string view this safety is not given. It does neither copy nor extend the lifetime of a return value
	std::string_view sv = retString();	// sv does NOT extend lifetime of returned string
	std::cout << sv << '\n';			// RUN-TIME ERROR: returned string destructed

	std::string_view substring(const std::string&, std::size_t idx = 0);	// returning string_view is also very dangerous 


Don’t Return String Views to Strings

	it is a very dangerous design to let getters of string members return a string view
	
	class Person {
		std::string name;
	public:
		Person (std::string n) : name{std::move(n)} { }
		std::string_view getName() const {	// don’t do this
			return name;
		}
	};
	
	auto n = createPerson().getName(); // OOPS: deletes temporary string
	std::cout << "name: " << n << '\n'; // FATAL RUN-TIME ERROR
	
Function Templates should use Return Type auto
	
	it is easy to accidentally assign returned strings to string views
	// define + for string views returning string:
	std::string operator+ (std::string_view sv1, std::string_view sv2) {
		return std::string(sv1) + std::string(sv2);
	}
	// generic concatenation:
	template<typename T>
	T concat (const T& x, const T& y) {
		return x + y;
	}
	
	However, using them together again might easily result in fatal run-time error:
	std::string_view hi = "hi";
	auto xy = concat(hi, hi);	// xy is std::string_view
	std::cout << xy << '\n';	// FATAL RUN-TIME ERROR: referred string destructed

	// improved generic concatenation:
	template<typename T>
	auto concat (const T& x, const T& y) {
		return x + y;
	}
	
	
	It is counter-productive to use string views in a chain of calls, where in the chain or at then end of it string are needed
	
	Passing a string literals or string you still need is fine:
	Person p1{"Jim"}; // no performance overhead
	std::string s = "Joe";
	Person p2{s}; // no performance overhead
	
	Person p3{std::move(s)}; // performance overhead: move broken
	
	Taking the parameter by value and moving it to the member is still the best solution.
	Person (std::string n) : name{std::move(n)} { }
	
Summary of Safe Usage of String Views

	Don’t use string views in API’s that pass the argument to a string
	Don’t return a string view
	Function templates should never return the type T of a passed generic argument. Return auto instead
	Never use a returned value to initialize a string view
	Don’t assign the return value of a function template returning a generic type to auto
	
NOTE: If these rules are too complicated or hard to follow, don’t use std::string_view at all

******************/

#include <iostream>
#include <string>
#include <string_view>

std::string get_string() {
    std::string astr{"sample string"};
    return astr;
}

std::string_view get_string_view() {
    std::string astr{"sample string"};
    return astr;
}

class RetSview {
    std::string m_str;
    public:
    RetSview(std::string str) : m_str{std::move(str)} {}
    std::string_view get_str() const {
        return m_str;
    }
};

class SviewAsParam{
    std::string m_str;
    public:
    SviewAsParam(std::string_view msg)      : m_str{msg} {}             // issue: move is broken
    //SviewAsParam(const std::string & msg) : m_str{msg}  {}            // issue: an initialization with a string literal creates one unnecessary copy
    //SviewAsParam(std::string msg)         : m_str{std::move(msg)} {}  // best solution
    void display() const {
        std::clog << m_str << '\n';
    }
};

std::string operator+ (std::string_view sv1, std::string_view sv2) {
    return std::string(sv1) + std::string(sv2);
}

template<typename T>
T retT_concat (const T& x, const T& y) {
    return x + y;
}

template<typename T>
auto retAuto_concat (const T& x, const T& y) {
    return x + y;
}


int main() {

    // 19.3.1 String View Considered Harmful
    {
        // Don’t Assign Strings to String Views
        //std::string & rstr = get_string();  // CE error: cannot bind non-const lvalue reference of type 'std::string&' to an rvalue of type 'std::string'
        const std::string & rstr = get_string();    // reference extends lifetime of returned string
        std::clog << "rstr: " << rstr << '\n';

        auto && rvalrstr = get_string();    // reference extends lifetime of returned string
        std::clog << "rvalrstr: " << rvalrstr << '\n';

        std::string_view    asview{get_string()}; // string_view does NOT extend lifetime of returned string
        //std::clog << "asview: " << asview << '\n';    // RUNTIME ERROR
    }

    {
        // Don’t Return String Views to Strings
        std::string_view    asview{get_string_view()};
        //std::clog << "asview: " << asview << '\n'; // RUNTIME ERROR
        //std::string         astr{get_string_view()};  // RUNTIME ERROR

        RetSview rsview{"return string view value"};
        auto str1 = rsview.get_str();
        std::clog << str1 << '\n';

        auto str2 = RetSview("temp return string view").get_str(); // temporary string is deleted
        //std::clog << str2 << '\n';  // RUNTIME ERROR
    }

    {
        // Function Templates should use Return Type auto
        std::string_view hi = "hi";
        auto res1 = retT_concat(hi, hi);    // deduced type is std::string_view
        //std::clog << res1 << '\n';        // RUNTIME ERROR, referred string destructed

        auto res2 = retAuto_concat(hi, hi); // deduced type is std::string
        std::clog << res2 << '\n';

        SviewAsParam svparam_1{"string view as parameter"}; svparam_1.display();
        std::string str{"string view as parameter"};
        SviewAsParam svparam_2{str};                        svparam_2.display();
        SviewAsParam svparam_3{std::move(str)};             svparam_3.display();
    }

    return 0;
}

/*****
    END OF FILE
********/


