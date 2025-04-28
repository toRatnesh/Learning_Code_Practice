/*****

References

    Effective Modern C++ | Scott Meyers
    https://en.cppreference.com/w/cpp/language/lambda

Item 33: Use decltype on auto&& parameters to std::forward them

C++14 generic lambdas
	lambdas that use auto in their parameter specifications
	implemented operator() in the lambda’s closure class is a template
	
	auto f = [](auto x){ return func(normalize(x)); };
	
	class SomeCompilerGeneratedClassName {
		public:
		template<typename T>		
		auto operator()(T x) const		// auto return type
		{ return func(normalize(x)); }
	};
	
	The correct way to write the lambda is to have it perfect-forward x to normalize
	
	in our lambda, we can determine whether the argument passed was an lvalue or an rvalue 
	by inspecting the type of the parameter x
	decltype gives us a way to do that	

	That means that instantiating std::forward with an rvalue reference type yields the same result 
	as instantiating it with a non-reference type
	
	auto f = [](auto&& x){ return func(normalize(std::forward<decltype(x)>(x))); };
	
	C++14 lambdas can also be variadic:
	auto f = [](auto&&... params){ return func(normalize(std::forward<decltype(params)>(params)...)); };
	
Summary
	•	Use decltype on auto&& parameters to std::forward them

**********/

#include <iostream>

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

void display(St&& ) {
    std::puts("display(S&& st)");
}

void display(const St & ) {
    std::puts("display(const St & st)");
}

int main() {

    {   std::puts("=== Lambda with auto && and without forward ===");
        auto lambda = [](auto && arg){ display(arg); };
        { St st; lambda(st); }
        { const St st; lambda(st); }

        { St st; lambda(std::move(st)); }
        { const St st; lambda(std::move(st)); }
        
        { lambda(St{}); }        
    }

    {   std::puts("\n=== Lambda with auto && and with forward ===");
        auto lambda = [](auto && arg){ display(std::forward<decltype(arg)>(arg)); };
        { St st; lambda(st); }
        { const St st; lambda(st); }

        { St st; lambda(std::move(st)); }
        { const St st; lambda(std::move(st)); }
        
        { lambda(St{}); }        
    }

    return 0;
}

/*****
    END OF FILE
**********/


