/********

    This example demonstrates about examples for
    Back to Basics: Declarations in C++ - Ben Saks - CppCon 2022

    For mroe info visit
    https://www.youtube.com/watch?v=IK4GhjmSC6w

************/

#include "declaration.hpp"
#include <iostream>
#include <array>

// use of typename for nested dependent types
//template<class C>     // this will also work
template<typename C>
void display(const C & container) {
    // Item42: this name is assumed to not be a type
    //C::const_iterator iter(container.begin()); // CE error: need 'typename' before 'C::const_iterator' because 'C' is a dependent scope

    //class C::const_iterator iter(container.begin());    // CE error: 'class C::const_iterator' resolves to 'std::array<int, 5>::const_iterator' {aka 'const int*'}, which is not a class type
    typename C::const_iterator iter(container.begin());

    while(iter != container.end()) {
        std::cout << *iter << ' ';
        ++iter;
    }
    std::cout << '\n';

    return ;
}

// use of forwarding reference and rvalue reference

template<typename T>
void display_02_(T && val) {
    std::cout << "value is " << val << '\n';
}

template<typename T>
void display_02(T && fref) {
    display_02_(std::forward<T>(fref));
    
    //T && val = fref;    // CE error: cannot bind rvalue reference of type 'int&&' to lvalue of type 'int'
    
    //T && val = std::move(fref);         // this fails when instantiate with lvalue
    //display_02_(std::forward<T>(val));

    auto && val2 = fref;
    display_02_(std::forward<T>(val2));
}


int main() {

    {
        std::cout << "=== extern with initialization ===\n";
        fun();
    }

    {
        std::cout << "\n=== const vs constexpr ===\n";

        {
        char constexpr *ptr = "Sample String";
        std::cout << "char constexpr *ptr: " << ptr << '\n';
        //ptr[0]= 's'; // RUNTIME ERROR
        }
        char *const ptr = "Sample String";
        std::cout << "char *const ptr: " << ptr << '\n';
        //ptr[0]= 's';  // RUNTIME ERROR
        }
        {
        char const *ptr = "Sample String";
        std::cout << "char const *ptr: " << ptr << '\n';
        //ptr[0]= 's';    // CE error: assignment of read-only location '* ptr'
        }
        {
      
    }


    {
        std::cout << "\n=== typename for dependent type names ===\n";
        std::array<int, 5> larr{1,2,3,4,5};
        display(larr);
    }

    {
        std::cout << "\n=== Rvalue References vs. Forwarding References ===\n";
        display_02(5);

        int val = 9;
        display_02(val);

	std::cout << "\nUsing int && to defining variable\n";
        { 
		int && aval = 13; 
		std::cout << "value is " << aval << '\n';

		aval = val;
		std::cout << "value is " << aval << '\n';
		
		aval = 5;
		std::cout << "value is " << aval << '\n';
	}

        //{ int && rval = val; }  // CE

	std::cout << "\nUsing auto && to defining variable\n";
        { 
		auto && aval = 23; 		// deduced type is rvalue
		std::cout << "auto && aval = 23 " << aval << '\n';

		aval = val;
		std::cout << " aval = val " << aval << '\n';
		
		aval = 5;
		std::cout << " aval = 5" << aval << '\n';
	}
        { 
		auto && aval = val; 
		std::cout << "auto && aval = val" << aval << '\n';
		
		aval = val;
		std::cout << " aval = val" << aval << '\n';
		
		aval = 5;
		std::cout << " aval = 5" << aval << '\n';
	}

    }

    return 0;
}


/********
    END OF FILE
************/

