/*****

Chapter 7: Templates and Generic Programming

	Generic programming — the ability to write code that is independent of the types of objects being manipulated

	It can be used to compute any computable value. That led to template metaprogramming: the creation of programs 
	that execute inside C++ compilers and that stop running when compilation is complete.

Item 43: Know how to access names in templatized base classes

	When a class inherits from a template base class and uses a member function from base class inside the derived class

	the code will not compile unless an explicit way is used to call the base class member function

	Issue:
		The problem is that when compilers encounter the definition for 
		the derived class template, they don’t know what class it inherits from.

		Without knowing what template parameter is, there’s no way to know what the class base looks like.
		In particular, there’s no way to know if it has that particular member function.
		
		
		Base class may go under a total template specialization for a specific type and 
		does not define the same interface present in template base class
		
		
		it recognizes that base class templates may be specialized and 
		that such specializations may not offer the same interface as the general template. 
		As a result, it generally refuses to look in templatized base classes for inherited names.
		
		In some sense, when we cross from Object-Oriented C++ to Template C++, inheritance stops working.

	three ways to access the name present in template base class
		1.	use this
		2.	using declarations
		3.	specify that the function being called is in the base class	(least preferred because may not work in case of virtual function)
		
Summary:

	.	In derived class templates, refer to names in base class templates via a “this->” prefix, 
		via using declarations, or via an explicit base class qualification.

**********/

#include <iostream>
#include <string>
#include <memory>

//#define LOGINFO std::cout << "[" << __FILE__ << ' ' << __LINE__ << ' ' << __func__ << "] ";
#define LOG(msg) std::cout << msg;

class Student {
    public:
    void display() { LOG("Student::display\n"); }
    void displayMasked() { LOG("Student::displayMasked\n"); }
};

class Teacher {
    public:
    void display() { LOG("Teacher::display\n"); }
    void displayMasked() { LOG("Teacher::displayMasked\n"); }
};

template<typename T>
class Display {

    public:

    virtual ~Display()  { }

    void displayMsg() {
        LOG("Display: ");
        T t;
        t.display();
    }

    void displayMaskedMsg() {
        LOG("Masekd display: ");
        T t;
        t.displayMasked();
    } 

    virtual void show() {
        LOG("Show: ");
        T t;
        t.display();
    }   
      
};

template<typename T>
class PrettyDisplay : public Display<T> {

    public:
    using Display<T>::displayMsg;
    using Display<T>::displayMaskedMsg;

    void prettyDisplayMsg() {
        LOG("Pretty display: \n");
        // CE error: there are no arguments to 'displayMsg' that depend on a template parameter, 
        // so a declaration of 'displayMsg' must be available
        // displayMsg();

        this->displayMsg();
        Display<T>::displayMsg();
        displayMsg();
    }

    void prettyDisplayMaskedMsg() {
        LOG("Pretty masekd display: \n");
        // error: there are no arguments to 'displayMaskedMsg' that depend on a template parameter, 
        // so a declaration of 'displayMaskedMsg' must be available
        // displayMaskedMsg();

        this->displayMaskedMsg();
        Display<T>::displayMaskedMsg();
        displayMaskedMsg();
    }

    
    virtual void show() override {
        LOG("Pretty show: \n");
        // this->show();        // VIRTUAL BINDING TAKE PALCE, RECURSION WILL RESULT IN STACK OVER FLOW
        Display<T>::show();     // NO VIRTUAL BINDING
    }
    
};

int main() {

    {   PrettyDisplay<Student>  obj;
        obj.prettyDisplayMsg(); 
        std::cout << '\n';
        obj.prettyDisplayMaskedMsg();
        std::cout << '\n';
    }

    {   PrettyDisplay<Teacher>  obj;
        obj.prettyDisplayMsg(); 
        std::cout << '\n';
        obj.prettyDisplayMaskedMsg();
        std::cout << '\n';
    }

    std::cout << "\n=== Accessing virtual function using pointer to Display(base) class ===\n";

    {   std::unique_ptr<Display<Student>>  pobj{new PrettyDisplay<Student>};
        pobj->show(); 
    }


    return 0;
}

/*****
    END OF FILE
**********/
