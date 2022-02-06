/***************
  This example demonstrates about use of covariant return types and covariant smart pointers.

  Covariant return types
  If the function Derived::f overrides a function Base::f, their return types must either be the same or be covariant. Two types are covariant if they satisfy all of the following requirements:

  => both types are pointers or references (lvalue or rvalue) to classes. Multi-level pointers or references are not allowed.
  => the referenced/pointed-to class in the return type of Base::f() must be a unambiguous and accessible direct or indirect base class of the referenced/pointed-to class of the return type of Derived::f().
  => the return type of Derived::f() must be equally or less cv-qualified than the return type of Base::f().

  For more info visit:
https://en.cppreference.com/w/cpp/language/virtual
https://en.wikipedia.org/wiki/Covariant_return_type
https://www.learncpp.com/cpp-tutorial/the-override-and-final-specifiers-and-covariant-return-types/
Tutoril :   https://www.youtube.com/watch?v=tvGCQmE5-Fs&list=PLs3KjaCtOwSZ2tbuV1hx8Xz-rFZTan2J1&index=266

 ***************/

#include <iostream>
#include <memory>

struct Base {
	//virtual Base fun() = 0;                   // CASE - 1
	//virtual std::shared_ptr<Base> fun() = 0;  // CASE - 2
	virtual Base * fun() = 0;
	virtual void display() { std::puts("Base display"); }
	virtual void display2() { std::puts("Base display2"); }
};

struct Derived : Base {
	//std::shared_ptr<Derived> child;           // CASE - 2
	Derived * child;

	//virtual Derived fun()                     // CASE - 1 invalid covariant return type for 'virtual Derived Derived::fun()'
	//virtual std::shared_ptr<Derived> fun()    // CASE - 2 invalid covariant return type for 'virtual std::shared_ptr<Derived> Derived::fun()'
	virtual Derived * fun() 
	{ 
		return child; 
	}
	void display() { std::puts("Derived display"); }
};


template<typename Contained, typename Base = void>
struct Covariant_Pointer : Covariant_Pointer<Base, void> {
	//Contained * value;
	std::shared_ptr<Contained> value;
};

template<typename Contained>
struct Covariant_Pointer<Contained, void> {

};

struct Base2 {
	virtual Covariant_Pointer<Base> & get_child() = 0;
	virtual void display() { std::puts("Base display"); }
	virtual void display2() { std::puts("Base display2"); }
};

struct Derived2 : Base2 {
	Covariant_Pointer<Derived, Base> child;
	Covariant_Pointer<Derived, Base> & get_child() override {
		return child;
	}
	void display() { std::puts("Derived display"); }
};


int main() {

	Derived d;
	Base & br = d;
	Derived & dr = d;

	br.display();
	dr.display();

	br.display2();
	dr.display2();
	std::puts("-----------");

	Derived2 d2;
	Base2 & br2 = d2;
	Derived2 & dr2 = d2;

	br2.display();
	dr2.display();

	br2.display2();
	dr2.display2();

	return 0;
}

/*******
  END OF FILE
 ********/
