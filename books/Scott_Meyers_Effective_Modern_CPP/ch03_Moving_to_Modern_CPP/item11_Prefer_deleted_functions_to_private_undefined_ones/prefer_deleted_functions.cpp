/*****

References

    Effective Modern C++ | Scott Meyers
    https://en.cppreference.com/w/cpp/language/function#Deleted_functions

Item 11: Prefer deleted functions to private undefined ones

sometimes C++ declares functions for you,

C++98 way to prevent use of function
	The C++98 approach to preventing use of these functions is to declare them private and not define them.
	Declaring these functions private prevents clients from calling them. 
	Deliberately failing to define them means that if code that still has access to them 
	(i.e., member functions or friends of the class) uses them, linking will fail due to missing function definitions.

C++11 "= delete"
	In C++11, there’s a better way to achieve essentially the same end: use “= delete” to mark the function deleted functions.
	Deleted functions may not be used in any way, so even code that’s in member and friend functions will fail to compile


	By convention, deleted functions are declared public, not private.
	When client code tries to use a deleted private function, some compilers complain only about the function being private, 
	even though the function’s accessibility doesn’t really affect whether it can be used.
	when revising legacy code to replace private-and-not-defined member functions with deleted ones, 
	making the new functions public will generally result in better error messages

Advantage of "= delete"
	any function may be deleted, while only member functions may be private
		
	Although deleted functions can’t be used, they are part of your program.
	As such, they are taken into account during overload resolution.

	
	deleted functions can (and that private member functions can’t) prevent use of template instantiations that should be disabled
	
	template<typename T>
	void processPointer(T* ptr);

	template<>
	void processPointer<void>(void*) = delete;

	template<>
	void processPointer<char>(char*) = delete;


	you can’t disable instantiations of a function template inside class by declaring them private
	because it’s not possible to give a member function template specialization a different access level from that of the main template
	
	This issue doesn’t arise for deleted functions, because they don’t need a different access level.
	
	class Widget {
		public:
		template<typename T>
		void processPointer(T* ptr)	{ … }
		
		private:
		template<>								
		void processPointer<void>(void*);	// error
	};
	
	template<>
	void Widget::processPointer<void>(void*) = delete; // still public, but deleted
	

Drawback of C++98 approach:
	C++98 approach doesn’t work outside classes, 
	it doesn’t always work inside classes, 
	and when it does work, it may not work until link-time. 

Summary:

	• Prefer deleted functions to private undefined ones.
	• Any function may be deleted, including non-member functions and template instantiations.

**********/

#include <iostream>

// C++98 private declared function
class C98 {
    // making private will reuslt in CE, making public will result in linking error
    C98(const C98 &);
    C98& operator=(const C98 &);
    public:
    C98() { }    
};

// C++11 =delete
class C11 {
    public:
    C11() { }    
    C11(const C11 &)                = delete;
    C11& operator=(const C11 &)     = delete;
};

// Deleting non-member function
void display(int val);

void printIt(int val)   = delete;


// Deleting template instantiations
template<typename T>
void processPointer(T* ptr) {
    std::cout << *ptr << '\n';
}

template<>
void processPointer<void>(void* ptr)    = delete;

template<>
void processPointer<char>(char* ptr);

class SampleClass {
    // error: explicit specialization in non-namespace scope 'class SampleClass'
    // template<>
    // void processPointer<char>(char* ptr);

    public:
    template<typename T>
    void processPointer(T* ptr) {
        std::cout << *ptr << '\n';
    }

    // error: explicit specialization in non-namespace scope 'class SampleClass'
    // template<>
    // void processPointer<void>(void* ptr)    = delete;
};

template<>
void SampleClass::processPointer<char>(char* ptr);

template<>
void SampleClass::processPointer<void>(void* ptr)    = delete;

int main() {
    {   std::puts("C++98 private declared function");
        C98     c1;
        //C98     c2(c1);       //error: 'C98::C98(const C98&)' is private within this context
    }

    {   std::puts("C++11 =delete");
        C11     c1;
        //C11     c2(c1);       //error: call to deleted constructor of 'C11'
    }

    {   std::puts("Deleting non-member function");
        //display(2);       // Link error: undefined reference to `display(int)'
        //printIt(2);       // error: use of deleted function 'void printIt(int)'
    }

    {   std::puts("Deleting template instantiations");

        int     ival = 5;
        char cptr[] = "A char pointer";
        //processPointer((void*)&ival);     // error: call to deleted function 'processPointer'
        //processPointer(cptr);             // Link error: undefined reference to `void processPointer<char>(char*)'
        processPointer(&ival);

        SampleClass sc;
        //sc.processPointer((void*)&ival);  // error: use of deleted function 'void SampleClass::processPointer(T*) [with T = void]'
        //sc.processPointer(cptr);          // Link error: undefined reference to `void SampleClass::processPointer<char>(char*)'
        sc.processPointer(&ival);
    }

    return 0; 
}

/*****
    END OF FILE
**********/


