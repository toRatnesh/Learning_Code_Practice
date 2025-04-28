/*****

References

    Effective Modern C++ | Scott Meyers
	https://en.cppreference.com/w/cpp/language/reference
	https://en.cppreference.com/w/cpp/language/reference#Rvalue_references

	https://en.cppreference.com/w/cpp/utility/move
	https://en.cppreference.com/w/cpp/utility/forward

Item 24: Distinguish universal references from rvalue references

	T&& declare an rvalue reference to some type T
	But if you see T&& in source code its not always rvalue reference

	void f(Widget&& param);				// rvalue reference
	Widget&& var1 = Widget();			// rvalue reference

	template<typename T>
	void f(std::vector<T>&& param);		// rvalue reference


	auto&& var2 = var1;					// not rvalue reference

	template<typename T>
	void f(T&& param);					// not rvalue reference


“T&&” has two different meanings
	1.	rvalue reference, they bind only to rvalues, and 
		their primary raison d’être is to identify objects that may be moved from.
		
	2.	universal references (or forwarding references)
		Such references look like rvalue references in the source code (i.e., “T&&”), 
		but they can behave as if they were lvalue references (i.e., “T&”). 
		
		Their dual nature permits them to bind to rvalues (like rvalue references) as well as lvalues (like lvalue references).
		
		Furthermore, they can bind to const or non-const objects, to volatile or non-volatile objects, 
		even to objects that are both const and volatile.
		They can bind to virtually anything.
		
Universal references (or forwarding references)
	Universal references arise in two contexts
	
	1.	function template parameters
	
		template<typename T>
		void f(T&& param);					// not rvalue reference
		
	2.	auto declarations
	
		auto&& var2 = var1;					// not rvalue reference

	What these contexts have in common is the presence of type deduction.
	
	“T&&” without type deduction, represents rvalue reference:
	void f(Widget&& param);		// no type deduction; param is an rvalue reference
	Widget&& var1 = Widget();	// no type deduction; var1 is an rvalue reference
	
	Because universal references are references, they must be initialized.
	If the initializer is an rvalue, the universal reference corresponds to an rvalue reference. 
	If the initializer is an lvalue, the universal reference corresponds to an lvalue reference. 
	For universal references that are function parameters, the initializer is provided at the call site.
	
	template<typename T>
	void f(T&& param);	// param is a universal reference
	
	Widget w;
	f(w);				// lvalue passed to f; param's type is Widget& (i.e., an lvalue reference)
	f(std::move(w));	// rvalue passed to f; param's type is Widget&& (i.e., an rvalue reference)
	
	
	For a reference to be universal, type deduction is necessary, and its form must be precisely “T&&”.
	
	template<typename T>
	void f(std::vector<T>&& param); // param is an rvalue reference, bcoz it's std::vector<T>&& not T&&
	
	template<typename T>
	void f(const T&& param);		// param is an rvalue reference, bcoz of presence of const
	
	template<class T, class Allocator = allocator<T>>		// from C++ Standards
	class vector {
		public:
		void push_back(T&& x);			// can not exist until vector instantiation
		…
	};
	
	push_back’s parameter certainly has the right form for a universal reference, but there’s no type deduction in this case.
	That’s because push_back can’t exist without a particular vector instantiation for it to be part of, 
	and the type of that instantiation fully determines the declaration for push_back.
	
	That is, saying
	std::vector<Widget> v;
	
	causes the std::vector template to be instantiated as follows:
	class vector<Widget, allocator<Widget>> {
		public:
		void push_back(Widget&& x);			// rvalue reference
		…
	};
	
	
	template<class T, class Allocator = allocator<T>>		// from C++ Standards
	class vector {
		public:
		template <class... Args>
		void emplace_back(Args&&... args);
		…
	};
	Here, the type parameter Args is independent of vector’s type parameter T, 
	so Args must be deduced each time emplace_back is called.
	
	
	auto variables can also be universal references.
	To be more precise, variables declared with the type auto&& are universal references, 
	because type deduction takes place and they have the correct form (“T&&”).
	
Universal references—is a lie
    the foundation of universal references—is a lie…er, an “abstraction.” 
    The underlying truth is known as reference collapsing, a topic to which Item 28 is dedicated.

    Distinguishing between rvalue references and universal references will 
    help you read source code more accurately, and it will avoid ambiguities.

Summary
	•	If a function template parameter has type T&& for a deduced type T, 
		or if an object is declared using auto&&, the parameter or object is a universal reference.
	•	If the form of the type declaration isn’t precisely type&&, 
		or if type deduction does not occur, type&& denotes an rvalue reference.
	•	Universal references correspond to rvalue references if they’re initialized with rvalues.
		They correspond to lvalue references if they’re initialized with lvalues.

**********/

#include <iostream>
#include <type_traits>
#include <vector>

#define LOGEXP(...) std::cout << std::boolalpha << #__VA_ARGS__ << " = " << __VA_ARGS__ << '\n'

class St {
    int     val;
    public:
    
    ~St()   { std::cout << "~St()\n"; }
    St()   { std::cout << "St()\n"; }
    explicit St(const int ival) : val(ival) { std::cout << "St(const int ival)\n"; }
    
    St(const St & other) : val(other.val) { 
        std::cout << "St(const St & other)\n"; 
    }
    St & operator=(const St & other) { 
        std::cout << "operator=(const St & other)\n"; 

        if(this != &other) {
            val = other.val;
        }
        return *this;
    }

    St(St && other) : val(std::move(other.val)) { 
        std::cout << "St(St && other)\n"; 
    }
    St & operator=(St && other) { 
        std::cout << "operator=(St && other)\n"; 

        if(this != &other) {
            val = std::move(other.val);
        }
        return *this;
    }    

};


void processSt(St && ) {
    std::cout << "processSt(St && tval)\n";
}

void processSt(const St && ) {
    std::cout << "processSt(St && tval)\n";
}

void processSt(const St & ) {
    std::cout << "processSt(const St & )\n";
}

decltype(auto) getSt() {
    return St{};
}

template<typename T>
void use_vector(std::vector<T> && ) {
    std::puts("use_vector(std::vector<T> && )");
}

template<typename T>
void processIt(T && tval) {
    std::cout << __PRETTY_FUNCTION__ << '\n';
    LOGEXP(std::is_rvalue_reference<decltype(tval)>::value);
    LOGEXP(std::is_lvalue_reference<decltype(tval)>::value);
}

template<typename T>
class LearnRvalue {

    public:
    void itTakesRvalue(T && ) {
        std::cout << "It looks like T&& but its rvalue\n";
    }

    template<typename Arg>
    void itTakesUniversalRef(Arg && arg) {
        std::cout << __PRETTY_FUNCTION__ << '\n';
        LOGEXP(std::is_rvalue_reference<decltype(arg)>::value);
        LOGEXP(std::is_lvalue_reference<decltype(arg)>::value);
        std::cout << "Its universal reference\n";
    }    
};

int main() {
    
    {   std::cout << "=== rvalue references ===\n";

        {   std::cout << "--- using object constructor ---\n";

            St s;
            // error: cannot bind rvalue reference of type 'St&&' to lvalue of type 'St'
            //St && st = s;

            St && st = St{};
            LOGEXP(std::is_rvalue_reference<decltype(st)>::value);

            processSt(st);
            processSt(std::move(st));
        }
        
        {   std::cout << "--- setting object from a function return value ---\n";
            St && st = getSt();
            LOGEXP(std::is_rvalue_reference<decltype(st)>::value);

            processSt(st);
            processSt(std::move(st));
        }

        {   std::cout << "--- using return value from a function ---\n";
            LOGEXP(std::is_rvalue_reference<decltype(getSt())>::value);

            processSt(getSt());
            processSt(std::move(getSt()));
        }

        {   std::cout << "--- using vector to rvalue reference ---\n";
            std::vector<int> lvec{1, 2, 3, 4, 5, 6, 7, 8, 9};
            // error: cannot bind rvalue reference of type 'std::vector<int>&&' to lvalue of type 'std::vector<int>'
            //use_vector(lvec);
            use_vector(std::move(lvec));
        }

        {   std::cout << "--- using member function template which looke like T&& but is rvalue reference ---\n";
            St  st;
            LearnRvalue<St>     lrv;
            // error: cannot bind rvalue reference of type 'St&&' to lvalue of type 'St'
            //lrv.itTakesRvalue(st);
            lrv.itTakesRvalue(std::move(st));
        }
    }

    {   std::cout << "=== universal references ===\n";

        {   std::cout << "--- using an already created object ---\n";
            St st;
            auto && val = st;
            LOGEXP(std::is_rvalue_reference<decltype(val)>::value);
            LOGEXP(std::is_lvalue_reference<decltype(val)>::value);            
        } 
        {   std::cout << "--- using an object ---\n";
            auto && val = St{};
            LOGEXP(std::is_rvalue_reference<decltype(val)>::value);
            LOGEXP(std::is_lvalue_reference<decltype(val)>::value);            
        }                 
        {   std::cout << "--- using return value of function ---\n";
            auto && val = getSt();
            LOGEXP(std::is_rvalue_reference<decltype(val)>::value);
            LOGEXP(std::is_lvalue_reference<decltype(val)>::value);            
        } 

        {   std::cout << "--- calling a template function with arg as an object ---\n";
            St st;
            processIt(st);
        } 
        {   std::cout << "--- calling a template function with arg as an object created in place ---\n";
            processIt(St{});
        } 
        {   std::cout << "--- calling a template function with arg as an function return value ---\n";
            processIt(getSt());
        }
        {   std::cout << "--- using member function template taking universal reference ---\n";
            const std::string str{"using universal reference"};

            LearnRvalue<St>     lrv;
            lrv.itTakesUniversalRef(str);
            lrv.itTakesUniversalRef(std::move(str));
        }                              
    }

    return 0;
}

/*****
    END OF FILE
**********/


