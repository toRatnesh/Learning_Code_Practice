/*****

Chapter 7: Templates and Generic Programming

	Generic programming — the ability to write code that is independent of the types of objects being manipulated

	It can be used to compute any computable value. That led to template metaprogramming: the creation of programs 
	that execute inside C++ compilers and that stop running when compilation is complete.

Item 41: Understand implicit interfaces and compiletime polymorphism
	
	The world of object-oriented programming revolves around explicit interfaces and runtime polymorphism.
	
	In that world of templates and generic programming, explicit interfaces and 
	runtime polymorphism continue to exist, but they’re less important. 
	Instead, implicit interfaces and compile-time polymorphism move to the fore.
	
	template<typename T>
	void doProcessing(T& w)
	{
		if (w.size() > 10 && w != someNastyWidget) {
			T temp(w);
			temp.normalize();
			temp.swap(w);
		}
	}	

	Because instantiating function templates with different template parameters leads 
	to different functions being called, this is known as compile-time polymorphism

	
	An explicit interface typically consists of function signatures
	An implicit interface is not based on function signatures. Rather, it consists of valid expressions.
	
	The implicit interface for T (w’s type) appears to have these constraints:
		.	It must offer a member function named size that returns an integral value.
		.	It must support an operator!= function that compares two objects of type T.	

	There is no requirement that T support operator!=, because 
	it would be just as acceptable for operator!= to take one object of type X and one object of type Y. 
	As long as T can be converted to X and someNastyWidget’s type can be converted to Y, the call to operator!= would be valid.
	Similarly for >.
	
	Implicit interfaces are simply made up of a set of valid expressions.
	
	
	The implicit interfaces imposed on a template’s parameters are just as real as 
	the explicit interfaces imposed on a class’s objects, and both are checked during compilation.
	
Summary
	.	Both classes and templates support interfaces and polymorphism.
	.	For classes, interfaces are explicit and centered on function signatures. 
		Polymorphism occurs at runtime through virtual functions.
	.	For template parameters, interfaces are implicit and based on valid expressions.
		Polymorphism occurs during compilation through template instantiation and function overloading resolution.

**********/

#include <iostream>
#include <string>

#define LOGEXP(x) std::cout << #x << ": " << x << '\n';

void display(std::string val) {
	std::cout << "\nNon template function: " << __PRETTY_FUNCTION__ << '\n';
	std::cout << "value " << val << '\n';
}

template<typename T>
void display(T val) {
	std::cout << '\n';
	std::cout << __PRETTY_FUNCTION__ << '\n';
	std::cout << "value " << val << '\n';
}

int main() {
	display(7);
	display(10.23);
	display("sample char array");

	display(std::string("sample string"));

    return 0;
}

/*****
    END OF FILE
**********/
