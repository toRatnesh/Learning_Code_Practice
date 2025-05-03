/*****

References

    Effective Modern C++ | Scott Meyers
    https://en.cppreference.com/w/cpp/language/value_category

Item 41: Consider pass by value for copyable parameters that are cheap to move and always copied

For example, a member function addName might copy its parameter into a private container. 
For efficiency, such a function should copy lvalue arguments, but move rvalue arguments:

See example code below

Overload
	Versin using overload for lvalue and rvalue requires writing two functions that do essentially the same thing.

Template using universal reference
	reduces the source code you have to deal with, but the use of universal references leads to other complications
	.	addName’s implementation must typically be in a header file
	.	it not only instantiates differently for lvalues and rvalues, 
		it also instantiates differently for std::string and types that are convertible to std::string
	.	there are argument types that can’t be passed by universal reference
	
Pass-by-value

	class Widget {
		public:
		void addName(std::string newName)			// take lvalue or rvalue
		{ names.push_back(std::move(newName)); }	// move it
		…
	};
	

the two calling scenarios we’ve examined:
	Widget w;
	std::string name("Bart");
	w.addName(name);			// pass lvalue
	w.addName(name + "Jenne");	// pass rvalue
	
Now consider the cost, in terms of copy and move operations

• Overloading:
	Regardless of whether an lvalue or an rvalue is passed, 
	the caller’s argument is bound to a reference called newName. That costs nothing.
	To insert in container Widget::names
	cost summary: one copy for lvalues, one move for rvalues

• Universal reference:
	As with overloading, the caller’s argument is bound to the reference newName. This is a no-cost operation.
	cost summary for std::string arguments is the same as with overloading: one copy for lvalues, one move for rvalues
	
• Passing by value: 
	Regardless of whether an lvalue or an rvalue is passed, the parameter newName must be constructed.
	If an lvalue is passed, this costs a copy construction.
	If an rvalue is passed, it costs a move construction.
	cost summary:	one copy plus one move for lvalues, and two moves for rvalues
	
	Compared to the by-reference approaches, that’s one extra move for both lvalues and rvalues.
	
"Consider pass by value for copyable parameters that are cheap to move and always copied"

1. consider using pass by value
	Advantage:
	.	it requires writing only one function
	.	it generates only one function in the object code
	.	it avoids the issues associated with universal references
	Drawback:
	.	it has a higher cost than the alternatives

2. Consider pass by value only for copyable parameters
	.	For move only type, the copy must be created via the move constructor
	.	For move only type, “overloading” solution requires only one overload: the one taking an rvalue reference
	
3. Pass by value is worth considering only for parameters that are cheap to move.

4. Consider pass by value only for parameters that are always copied
	because if some checks or performed on the parameter,
	we need to create object to performe check on it, even if the object is not inserted in the container


copied via assignment
	When parameters are copied via assignment, analyzing the cost of pass by value is complicated.
	Usually, the most practical approach is to adopt a “guilty until proven innocent” policy, 
	whereby you use overloading or universal references instead of pass by value unless 
	it’s been demonstrated that pass by value yields acceptably efficient code for the parameter type you need.

Now, for software that must be as fast as possible, pass by value may not be a viable strategy, 
because avoiding even cheap moves can be important.	Moreover, it’s not always clear how many moves will take place.

slicing problem
	An issue unrelated to performance, but still worth keeping in mind, is that pass by value, 
	unlike pass by reference, is susceptible to the slicing problem.
	
Summary
•	For copyable, cheap-to-move parameters that are always copied, pass by value may be nearly 
	as efficient as pass by reference, it’s easier to implement, and it can generate less object code.
•	Copying parameters via construction may be significantly more expensive than copying them via assignment.
•	Pass by value is subject to the slicing problem, so it’s typically inappropriate for base class parameter types.

**********/

#include <iostream>
#include <vector>

class St {

    int     val;
    public:
    
    ~St()   { std::puts("~St()"); }
    St()   { std::puts("St()"); }
    
    St(const St & other) noexcept : val(other.val) { 
        std::puts("St(const St & other)");
    }
    St & operator=(const St & other) noexcept { 
        std::puts("operator=(const St & other)");

        if(this != &other) {
            val = other.val;
        }
        return *this;
    }

    St(St && other) noexcept : val(std::move(other.val)) { 
        std::puts("St(St && other)");
    }
    St & operator=(St && other) noexcept { 
        std::puts("operator=(St && other)");

        if(this != &other) {
            val = std::move(other.val);
        }
        return *this;
    }    

};

class UsingOverload {
    std::vector<St>     mvec_st;
    public:
    void add(const St & st) {
        mvec_st.push_back(st);
    }
    void add(St && st) {
        mvec_st.push_back(std::move(st));
    }    
};

class UsingUniversalref {
    std::vector<St>     mvec_st;
    public:
    template<typename T>
    void add(T&& st) {
        mvec_st.push_back(std::forward<T>(st));
    }    
};


class UsingPassByvalue {
    std::vector<St>     mvec_st;
    public:
    void add(St st) {
        mvec_st.push_back(std::move(st));
    }    
};

class Base {
    public:
    virtual void fun() { std::puts("Inside Base::fun()"); }
};

class Derived : public Base {
    public:
    virtual void fun() override { std::puts("Inside Derived::fun()"); }
};

void process(Base base) {
    base.fun();
}

void process(Base * base) {
    base->fun();
}

int main() {
    {   std::puts("=== using overload on lvalue and rvalue ===");
        UsingOverload   uobj;
        St st;
        uobj.add(st);
        uobj.add(std::move(st));
    }

    {   std::puts("\n=== using universal reference ===");
        UsingUniversalref   uobj;
        St st;
        uobj.add(st);
        uobj.add(std::move(st));
    }

    {   std::puts("\n=== using pass by value ===");
        UsingPassByvalue   uobj;
        St st;
        uobj.add(st);
        uobj.add(std::move(st));
    }

    {   std::puts("\n=== Slicing problem ===");
        Base b;
        process(b);
        process(&b);

        Derived d;
        process(d);
        process(&d);
    }

    return 0;
}

/*****
    END OF FILE
**********/

