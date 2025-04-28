/*****

References

    Effective Modern C++ | Scott Meyers
	https://en.cppreference.com/w/cpp/language/reference
	https://en.cppreference.com/w/cpp/language/sfinae
	https://en.cppreference.com/w/cpp/types/enable_if


Item 28: Understand reference collapsing
	when an argument is passed to a template function, 
	the type deduced for the template parameter encodes whether the argument is an lvalue or an rvalue
	this happens only when the argument is used to initialize a parameter that’s a universal reference,
	
	Encoding mechanism
	When an lvalue is passed as an argument, T is deduced to be an lvalue reference
	When an rvalue is passed, T is deduced to be a non-reference
	(lvalues are encoded as lvalue references, but rvalues are encoded as non-references)


Reference collapsing
	Note: references to references are illegal in C++
		int x;
		auto& & rx = x;			// error! can't declare reference to reference

	consider an lvalue is passed to a function template taking a universal reference:
		template<typename T>
		void func(T&& param);	// func with universal reference

		Widget w;				// a variable (an lvalue)
		func(w);				// invoke func with lvalue; T deduced as Widget&

	If we take the type deduced for T (i.e., Widget&) and use it to instantiate the template, we get this:
		void func(Widget& && param);
		
	Reference collapsing: 
	Compilers may produce references to references, in particular contexts, template instantiation being among them.
	When compilers generate references to references, reference collapsing dictates what happens next.
	
	4 possible reference-reference combinations
		1.	lvalue to lvalue
		2.	lvalue to rvalue
		3.	rvalue to lvalue
		4.	rvalue to rvalue
		
	If a reference to a reference arises in a context where this is permitted (e.g., during template instantiation), 
	the references collapse to a single reference according to this rule:
	 =======================================================================================
	|	If either reference is an lvalue reference, the result is an lvalue reference.		|
	|	Otherwise (i.e., if both are rvalue references) the result is an rvalue reference.	|
	 =======================================================================================


Insight of std::forward
	Reference collapsing is a key part of what makes std::forward work
	
	Consider following
	
	template<typename T>
	void f(T&& fParam) {
		…
		someFunc(std::forward<T>(fParam));	// forward fParam to someFunc
	}
	
	std::forward’s job is to cast fParam (an lvalue) to an rvalue 
	if and only if T encodes that the argument passed to f was an rvalue, i.e., if T is a non-reference type.
	
	Sample implementaion of std::forward
	
	template<typename T>
	// T&& forward(typename remove_reference<T>::type& param) 	// C++11
	T&& forward(remove_reference_t<T>& param)					// C++14
	{
		return static_cast<T&&>(param);
	}
		
	if the argument passed to f is an lvalue of type Widget
	Widget& forward(Widget& param) {
		return static_cast<Widget&>(param);
	}
	
	if the argument passed to f is an rvalue of type Widget
	Widget&& forward(Widget& param) {
		return static_cast<Widget&&>(param);
	}


More about universal reference
	A universal reference isn’t a new kind of reference, 
	it’s actually an rvalue reference in a context where two conditions are satisfied:
	
	1.	Type deduction distinguishes lvalues from rvalues.
		Lvalues of type T are deduced to have type T&, while rvalues of type T yield T as their deduced type.
	2.	Reference collapsing occurs.


Reference collapsing occurs in four contexts
	1.	template instantiation
	2.	type generation for auto variables
	3.	generation and use of typedefs and alias declarations
	4.	uses of decltype


Summary
	•	Reference collapsing occurs in four contexts: 
		1. template instantiation, 
		2.	auto type generation, 
		3.	creation and use of typedefs and alias declarations, and 
		4.	decltype.
	•	When compilers generate a reference to a reference in a reference collapsing context, 
		the result becomes a single reference. 
		If either of the original references is an lvalue reference, the result is an lvalue reference. 
		Otherwise it’s an rvalue reference.
	•	Universal references are rvalue references in contexts where type deduction 
		distinguishes lvalues from rvalues and where reference collapsing occurs.

**********/

#include <iostream>
#include <type_traits>

#define LOGEXP(...) std::cout << std::boolalpha << #__VA_ARGS__ << " = " << __VA_ARGS__ << '\n'

template<typename T>
void funWithUniversalRef(T&& val) {

    std::cout << "Enter: " << __func__ << '\n';
    std::cout << "Value is: " << val << '\n';
    
    LOGEXP(std::is_rvalue_reference<decltype(val)>::value);
    LOGEXP(std::is_lvalue_reference<decltype(val)>::value);

    std::cout << "--- reference collapse in case of alaias type ---\n";
    using rvalue_t  = T&&;
    LOGEXP(std::is_rvalue_reference<rvalue_t>::value);
    LOGEXP(std::is_lvalue_reference<rvalue_t>::value);
}

int main() {
    {   std::cout << "=== Reference collapsing in template instantiation ===\n";
        {   std::string str{"string value"};    funWithUniversalRef(str);   }
        {   const std::string str{"const string value"};    funWithUniversalRef(str);   }

        {   std::string str{"string value"};    funWithUniversalRef(std::move(str));   }
        {   const std::string str{"const string value"};    funWithUniversalRef(std::move(str));   }

        {   funWithUniversalRef(std::string("in-place string as argument"));   }
    }

    {   std::cout << "\n=== Reference collapsing in auto type generation ===\n";
        {
            std::string str{"string value"};    
            auto && val = str;
            std::cout << "Value is: " << val << '\n';
            LOGEXP(std::is_rvalue_reference<decltype(val)>::value);
            LOGEXP(std::is_lvalue_reference<decltype(val)>::value);            
        }
        {
            const std::string str{"const string value"};
            auto && val = str;
            std::cout << "Value is: " << val << '\n';
            LOGEXP(std::is_rvalue_reference<decltype(val)>::value);
            LOGEXP(std::is_lvalue_reference<decltype(val)>::value);            
        }
        
        {
            std::string str{"string value"};
            auto && val = std::move(str);
            std::cout << "Value is: " << val << '\n';
            LOGEXP(std::is_rvalue_reference<decltype(val)>::value);
            LOGEXP(std::is_lvalue_reference<decltype(val)>::value);            
        }
        {
            const std::string str{"const string value"};
            auto && val = std::move(str);
            std::cout << "Value is: " << val << '\n';
            LOGEXP(std::is_rvalue_reference<decltype(val)>::value);
            LOGEXP(std::is_lvalue_reference<decltype(val)>::value);            
        }

        {
            auto && val = std::string("in-place string as argument");
            std::cout << "Value is: " << val << '\n';
            LOGEXP(std::is_rvalue_reference<decltype(val)>::value);
            LOGEXP(std::is_lvalue_reference<decltype(val)>::value);            
        }        
    }

    return 0;
}

/*****
    END OF FILE
**********/


