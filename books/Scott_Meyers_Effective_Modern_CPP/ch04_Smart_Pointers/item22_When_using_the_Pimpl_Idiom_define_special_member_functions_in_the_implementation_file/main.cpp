/*****

References

    Effective Modern C++ | Scott Meyers
	https://en.cppreference.com/w/cpp/language/pimpl

Item 22: When using the Pimpl Idiom, define special member functions in the implementation file

Pimpl (“pointer to implementation”) Idiom
	The technique whereby you replace the data members of a class with a pointer to an implementation class (or struct), 
	put the data members that used to be in the primary class into the implementation class, 
	and access those data members indirectly through the pointer. For example,

	class Widget {						// in header "widget.h"
		public:
		Widget();
		…
		private:
		std::string name;
		std::vector<double> data;
		Gadget g1, g2, g3;				// Gadget is some user-defined type
	};

	Applying the Pimpl Idiom
	
	class Widget {						// still in header "widget.h"
		public:
		Widget();
		~Widget();						// dtor is needed—see below
		…
		private:
		struct Impl;					// declare implementation struct and pointer to it
		Impl *pImpl;					//  C++98
		std::unique_ptr<Impl>	pImpl;	//  C++11	
	};	

	Part 1:	the declaration of a data member that’s a pointer to an incomplete type. 
	Part 2:	dynamic allocation and deallocation of the object that holds the data members that used to be in the original class.
			The allocation and deallocation code goes in the implementation file, e.g., for Widget, in widget.cpp
			
	#include "widget.h"		// in impl. file "widget.cpp"
	#include "gadget.h"
	#include <string>
	#include <vector>

	struct Widget::Impl {			// definition of Widget::Impl
		std::string name;			// with data members formerly
		std::vector<double> data;	// in Widget
		Gadget g1, g2, g3;
	};
	Widget::Widget(): pImpl(new Impl) { }						// C++98 allocate data members for this Widget object
	Widget::Widget(): pImpl(std::make_unique<Impl>()) { }		// C++11 allocate data members for this Widget object
	
	Widget::~Widget() { delete pImpl; }			// C++98 destroy data members for this object

	the dependencies have been moved from widget.h (which is visible to and used by Widget clients) to widget.cpp
	
	
Difference in using unique_ptr and shared_ptr for pImpl 

	For std::unique_ptr, the type of the deleter is part of the type of the smart pointer, 
	and this makes it possible for compilers to generate smaller runtime data structures and faster runtime code. 
	A consequence of this greater efficiency is that pointed-to types must be complete 
	when compiler-generated special functions (e.g., destructors or move operations) are used.
	
	So if we want to use unique_ptr for pImpl we need to define our own special member functions in implementation source code file
	
	For std::shared_ptr, the type of the deleter is not part of the type of the smart pointer. 
	This necessitates larger runtime data structures and somewhat slower code, 
	but pointed-to types need not be complete when compiler-generated special functions are employed.	

Summary

	•	The Pimpl Idiom decreases build times by reducing compilation dependencies between class clients and class implementations.
	•	For std::unique_ptr pImpl pointers, declare special member functions in the class header, 
		but implement them in the implementation file. Do this even if the default function implementations are acceptable.
	•	The above advice applies to std::unique_ptr, but not to std::shared_ptr.

**********/

#include "using_pimpl.hpp"

#include <iostream>

int main() {
    {   std::cout << "=== PIMPL using shared pointer ===\n";
        PimplUsingSharedPtr lp1;
        PimplUsingSharedPtr lp2;

        PimplUsingSharedPtr lp3{lp2};   // // compiler generated compiler will do shallow copy
        lp3 = lp1;

        PimplUsingSharedPtr lp4{std::move(lp2)};
        lp4 = std::move(lp1);

        PimplUsingSharedPtr lp5(St{2});
    }

    {   std::cout << "\n=== PIMPL using unique pointer ===\n";
        PimplUsingUniquePtr lp1;
        PimplUsingUniquePtr lp2;

        PimplUsingUniquePtr lp3{lp2};
        lp3 = lp1;

        PimplUsingUniquePtr lp4{std::move(lp2)};
        lp4 = std::move(lp1);

        PimplUsingUniquePtr lp5(St{7});
    }

    return 0;
}

/*****
    END OF FILE
**********/

