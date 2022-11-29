/***********

References
	C++17 - The Complete Guide | Nicolai M. Josuttis

5. Mandatory Copy Elision or Passing Unmaterialized Objects
    In C++17, former option to eliminate copying temporary objects, when passing or returning them by value, now becomes mandatory.

5.3 Clarified Value Categories
	5.3.1 Value Categories
		To require copy elision for temporaries when initializing new objects, some adjustments to value categories were made
		
		Value Categories Since C++11
		
					expression
					/	  \
			 glvalue	  rvalue
			/		\	/		\
		lvalue		xvalue		prvalue

		core categories lvalue, prvalue (.pure rvalue.), and xvalue (.eXpiring value.)
		
		strictly speaking glvalues, prvalues, and xvalues are terms for expressions and not for values (which means that these terms are misnomers)
		For example, a variable itself is not an lvalue; only an expression denoting the variable is an lvalue:
			int x = 3; // x here is a variable, not an lvalue
			int y = x; // x here is an lvalue
		In the first statement 3 is a prvalue initializing the variable (not the lvalue) x
		In the second statement x is an lvalue (its evaluation designates an object containing the value 3)
		The lvalue x is converted to a prvalue, which is what initializes the variable y

	5.3.2 Value Categories Since C++17

					expression
					/	  \
			 glvalue	  rvalue ---------------
			/		\	/						\
		lvalue		xvalue <- materialization - prvalue
		
		C++17 then introduces a new term, called materialization (of a temporary) for the moment a prvalue becomes a temporary object. 
		Thus, a temporary materialization conversion is a prvalue to xvalue conversion.
		Any time a prvalue validly appears where a glvalue (lvalue or xvalue) is expected, a temporary object is created and initialized with the prvalue (recall that prvalues are primarily .initializing values.), and the prvalue is replaced by an xvalue designating the temporary.
		So in the example above, we strictly speaking have:
			void f(const X& p); // accepts an expression of any value category, but expects a glvalue
			f(X()); // passes a prvalue materialized as xvalue
		
		Note that materialization does not mean that we create a new/different object. 
		The lvalue reference p still binds to both an xvalue and a prvalue, although the latter now always involves a conversion to an xvalue.
		With this modification (that prvalues are no longer objects but are instead expressions that can be used to initialize objects)
				
5.4 Unmaterialized Return Value Passing
	Unmaterialized return value passing applies to all forms of returning a temporary object (prvalue) by value

*************/

#include <iostream>

class Test {
    public:
        Test(int) { std::puts("T(int)"); }
        Test(const Test & ) = delete;
        Test(Test && ) = delete;
};
// return prvalue 
int get_val() { return 42; }
Test get_Test() { return Test(5); }
auto get_Test_using_auto() { return Test(5); }
decltype(auto) get_Test_using_decltype_auto() { return Test(5); }

void take_lvalue_xvalue(const Test &) { std::puts("take_lvalue_xvalue()"); }

void take(const Test &) { std::puts("take(const Test &)"); } // // accepts an expression of any value category
void take(Test &&) { std::puts("take(Test &&)"); }   // accepts prvalues and xvalues only, but is a better match

int main() {

    // 5.3 Clarified Value Categories
    std::puts("=== Clarified Value Categories ===");
    Test t(3);
    const Test ct(3);

    take(t);            // passes a modifiable lvalue to the first take()
    take(ct);           // passes a non-modifiable lvalue to the first take()
    take(std::move(ct));// passes a non-modifiable lvalue to the first take()
    take(std::move(t)); // passes an xvalue to the second take()
    take(Test(2));      // passes a prvalue to the second take()
    


    // 5.4 Unmaterialized Return Value Passing
    std::puts("=== Unmaterialized Return Value Passing ===");
    [[maybe_unused]] int val = get_val();
    [[maybe_unused]] Test t1 = 5;
    [[maybe_unused]] Test t2 = get_Test();
    [[maybe_unused]] Test t3 = get_Test_using_auto();
    [[maybe_unused]] Test t4 = get_Test_using_decltype_auto();

    take_lvalue_xvalue(Test(5));

    return 0;
}

/*******
    END OF FILE
******/


