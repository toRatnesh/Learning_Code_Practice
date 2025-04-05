/*****

References

    Effective Modern C++ | Scott Meyers
    https://en.cppreference.com/w/cpp/language/override

Item 12: Declare overriding functions override

overriding
	For overriding to occur, several requirements must be met:

	• The base class function must be virtual.
	• The base and derived function names must be identical (except in the case of destructors).
	• The parameter types of the base and derived functions must be identical.
	• The constness of the base and derived functions must be identical.
	• The return types and exception specifications of the base and derived functions must be compatible.
	• The functions’ reference qualifiers must be identical.

	Code containing overriding errors is typically valid, but its meaning isn’t what you intended.
	You therefore can’t rely on compilers notifying you if you do something wrong.

C++11 override:
	C++11 gives you a way to make explicit that 
	a derived class function is supposed to override a base class version: declare it override.

	when written this way, compilers will kvetch about all the overriding-related problems

override and final:
	C++11 introduces two contextual keywords, over ride and final.
	These keywords have the characteristic that they are reserved, but only in certain contexts. 
	In the case of override, it has a reserved meaning only when it occurs at the end of a member function declaration.
	That means that if you have legacy code that already uses the name override, you don’t need to change it for C++11

& and && in member function
	If we want to write a function that accepts only lvalue arguments, we declare a nonconst lvalue reference parameter:
		void doSomething(Widget& w); // accepts only lvalue Widgets
	If we want to write a function that accepts only rvalue arguments, we declare an rvalue reference parameter:
		void doSomething(Widget&& w); // accepts only rvalue Widgets

Summary:

	• Declare overriding functions override.
	• Member function reference qualifiers make it possible to treat lvalue and rvalue objects (*this) differently.

**********/

#include <iostream>
#include <string>
#include <memory>


class Base {
    public:
    virtual void fun(double val) {
        std::cout << "Base::fun(double) " << val << '\n';
    }
    virtual void fun2(int val) {
        std::cout << "Base::fun2(int) " << val << '\n';
    }    
    virtual void display(std::string val) {
        std::cout << "Base::display(std::string ) " << val << '\n';
    }    
};

class Derived : public Base {
    public:
    virtual void fun(int val)  {
        std::cout << "Derived::fun(int) " << val << '\n';
    }

    /*  error: 'virtual void Derived::fun2(double)' marked 'override', but does not override
    virtual void fun2(double val) override {
        std::cout << '[' << __func__ << ',' << __LINE__ << "] " << val << '\n';
    }
    */     

    virtual void fun2(int val) override {
        std::cout << "Derived::fun2(int) " << val << '\n';
    } 

    virtual void display(std::string val) {
        std::cout << "Derived::display(std::string) " << val << '\n';
    }  
};

class Base2 {
	public:
	virtual void mf1() const;
	virtual void mf2(int x);
	virtual void mf3() &;
	//void mf4() const;
    virtual void mf4() const;   // add virtual to override
};

class DerivedWrong: public Base2 {
	public:
	virtual void mf1();                 // const missing
	virtual void mf2(unsigned int x);   // data type of x is diff
	virtual void mf3() &&;              // ref is &&
	void mf4() const;                   // virtual is not present in base class
};

class DerivedCorrect: public Base2 {
	public:
	virtual void mf1() const override;
	virtual void mf2(int x) override;
	virtual void mf3() & override;
	void mf4() const override;  // virtual is not necessary in derived class
};

int main() {
    
    {
        std::unique_ptr<Base> lp = std::make_unique<Derived>();

        lp->fun(23);
        lp->fun(23.45);

        lp->fun2(23);
        
        lp->display("sample string");
    }

    return 0; 
}

/*****
    END OF FILE
**********/


