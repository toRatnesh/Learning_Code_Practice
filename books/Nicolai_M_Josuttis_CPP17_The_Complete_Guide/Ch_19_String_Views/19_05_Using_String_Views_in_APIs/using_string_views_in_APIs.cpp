/**********

References
	C++17 - The Complete Guide | Nicolai M. Josuttis
	https://en.cppreference.com/w/cpp/string/basic_string_view
	
19.5 Using String Views in API’s

using a std::string_view only makes sense if the function using the parameter has the following constraints

	It doesn’t expect a null terminator at the end
	It respects the lifetime of the passed argument
	The calling function should not deal with the owner of the underlying characters (such as deleting it, changing its value, or freeing its memory).
	It can deal with the nullptr as value

NOTE: that ambiguity errors are possible
	void foo(const std::string&);
	void foo(std::string_view);

	foo("hello"); // ERROR: ambiguous

19.5.1 Using String Views to Initialize Strings

	// traditional way to initialize a string member
	Person (const std::string& n) : name(n) { }
	This constructor has its drawbacks. Initializing a person with a string literal creates one unnecessary copy, which might cause an unnecessary request for heap memory.

	// using a string view, the performance is better, but move is broken
	Person (std::string_view n) : name(n) { }
	A temporary string view n gets created, which does not allocate memory at all, because the string view only refers to the characters of the string literal.
	But use of string view disables move semantics unless you provide an additional overload for it.

	// recommended way
	Person (std::string n) : name(std::move(n)) { }

	String views are not a better interface for taking strings.
	In fact, string views should only be used in call chains, where they never have to be used as strings.

19.5.2 Using String Views instead of Strings

	There are other replacement of strings by string views possible. But be aware, example
	
	std::string toString (const std::string& prefix, const std::chrono::system_clock::time_point& tp) {
		// convert to calendar time:
		auto rawtime = std::chrono::system_clock::to_time_t(tp);
		std::string ts = std::ctime(&rawtime);	// NOTE: not thread safe
		ts.resize(ts.size()-1);		// skip trailing newline
		return prefix + ts;
	}	

	std::string toString (std::string_view prefix, const std::chrono::system_clock::time_point& tp) {
		auto rawtime = std::chrono::system_clock::to_time_t(tp);
		std::string_view ts = std::ctime(&rawtime);	// NOTE: not thread safe
		ts.remove_suffix(1);				// skip trailing newline
		return std::string(prefix) + ts;	// unfortunately no operator + yet
	}

******************/

#include <iostream>
#include <string>
#include <string_view>

void ambiguous_fun([[maybe_unused]] std::string_view fp_parm)    { }
void ambiguous_fun([[maybe_unused]] std::string fp_parm)         { }

// 19.5.1 Using String Views to Initialize Strings
class SviewAsParam{
    std::string m_str;
    public:
    SviewAsParam(std::string_view msg)      : m_str{msg} {}             // issue: move is broken, creating string from string_view needs to allocate memory
    //SviewAsParam(const std::string & msg) : m_str{msg}  {}            // issue: an initialization with a string literal creates one unnecessary copy
    //SviewAsParam(std::string msg)         : m_str{std::move(msg)} {}  // best solution
    void display() const {
        std::clog << m_str << '\n';
    }
};

void read_only_operation(std::string_view fp_sview) {
    std::clog << "string view parm " << fp_sview << '\n';
}

int main() {

    //ambiguous_fun("this call is ambiguous"); // error: call of overloaded 'ambiguous_fun(const char [23])' is ambiguous

    // 19.5.1 Using String Views to Initialize Strings
    {
        std::clog << "=== 19.5.1 Using String Views to Initialize Strings ===\n";
        SviewAsParam sv1{"C++ string view-1"};  sv1.display();
        std::string astr{"C++ string view-2"};  
        SviewAsParam sv2{astr};                 sv2.display();
        SviewAsParam sv3{std::move(astr)};      sv3.display();
    }


    // 19.5.2 Using String Views instead of Strings
    {
        std::clog << "\n=== 19.5.2 Using String Views instead of Strings ===\n";
        // In fact, string views should only be used in call chains, where they never have to be used as strings.
        read_only_operation("this is a char array");
        std::string astr{"this is a string"};
        read_only_operation(astr);
    }

    return 0;
}

/*****
    END OF FILE
*******/


