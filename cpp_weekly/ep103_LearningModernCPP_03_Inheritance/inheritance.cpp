/************
 *	In this tutorial Jason talks aboout inheritance one of OOP's principle.
 * *************/

#include <iostream>

struct Base {

	// used virtual function so need to define virtual destructor 
	// and since defined virtual destructor hence need to satisfy the "rule of five"
	Base() = default;
	Base(const Base &) = default;
	Base(Base &&) = default;
	Base& operator=(const Base &) = default;
	Base& operator=(Base &&) = default;
	virtual ~Base() = default;

	virtual void fun() = 0;
	virtual void fun(const int i) {
		std::cout << "Base::fun(int i)" << i << '\n';
	}
	virtual void fun(const std::string & msg) {
		std::cout << "Base::" << msg << '\n';
	}

	void fun(const int val, const std::string & msg) {
		std::cout << "Base:: " << val << ' ' << msg << '\n';
	}

	int data = 23;
};

struct Derived : Base {
	//void fun(int i ) override // error: 'void Derived::fun(int)' marked 'override', but does not override
	void fun() override
	{
		std::cout << "Derived::fun()\n";
	}
	void fun(const int i) override {
		std::cout << "Derived::fun(int i)" << i << '\n';
	}
	using Base::fun; 

	void fun(const int val, const std::string & msg) {
		std::cout << "Derived:: " << val << ' ' << msg << '\n';
	}
};

int main() {
	std::cout << "=== USING BASE CLASS POINTER TO DERIVED CLASS OBJECT ===\n";
	Base * lbp = new Derived();
	lbp->fun();
	lbp->fun(7);
	lbp->fun(std::string("This is a sample string."));

	// calls base class version becasue member fun is not virtual so early binding takes place
	lbp->fun(13, std::string("This is a sample string.")); 

	std::cout << lbp->data << '\n';
	delete lbp;
	std::cout << '\n';

	std::cout << "=== USING DERIVED CLASS OBJECT ===\n";
	Derived dobj;
	dobj.fun();
	dobj.fun(7);

	// error: no matching function for call to 'Derived::fun(std::string)'
	// call to this method fails because void fun(const std::string & msg) is hidden by other fun definitions
	// using Base::fun; in derived class will make all things named fun visible in derived class
	dobj.fun(std::string("This is a sample string."));

	// calls derived class version becasue member fun is not virtual so early binding takes place
	dobj.fun(13, R"(This is a sample string.)");
	std::cout << dobj.data << '\n';

	return 0;
}

/******
 *	END OF FILE
 * ******/
