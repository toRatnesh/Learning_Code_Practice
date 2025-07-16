/*****


Chapter 7: Templates and Generic Programming

    Generic programming — the ability to write code that is independent of the types of objects being manipulated

    It can be used to compute any computable value. That led to template metaprogramming: the creation of programs 
    that execute inside C++ compilers and that stop running when compilation is complete.


Item 45: Use member function templates to accept “all compatible types.”

    member function templates (often just known as member templates) — templates that generate member functions of a class:
    

    Consider a rough implementaion of smart pointer

    template <class T>
    class shared_ptr
    {
    public:
	    // construct from any compatible built-in pointer, shared_ptr, weak_ptr, or auto_ptr
	    template <class Y>
	    explicit shared_ptr(Y *p);
	    
	    template <class Y>
	    shared_ptr(shared_ptr<Y> const &r);        // ”generalized copy constructor”
	    
	    template <class Y>
	    explicit shared_ptr(weak_ptr<Y> const &r);
	    
	    template <class Y>
	    explicit shared_ptr(auto_ptr<Y> &r);
	    
	    // assign from any compatible shared_ptr or auto_ptr
	    template <class Y>
	    shared_ptr &operator=(shared_ptr<Y> const &r);
	    
	    template <class Y>
	    shared_ptr &operator=(auto_ptr<Y> &r);
	    ...
    };
    
    generalized copy constructor:
	    Constructors like this — ones that create one object from another object whose type is a 
	    different instantiation of the same template (e.g., create a SmartPtr<T> from a SmartPtr<U>) — 
	    are sometimes known as generalized copy constructors.
	    
    All these constructors are explicit, except the generalized copy constructor. 
    That means that implicit conversion from one type of shared_ptr to another is allowed, 
    but implicit conversion from a built-in pointer or other smart pointer type is not permitted.

    Member function templates don’t alter the basic rules of the language.
    
    Declaring a generalized copy constructor (a member template) in a class doesn’t keep 
    compilers from generating their own copy constructor (a nontemplate),
    so if you want to control all aspects of copy construction, you must declare 
    both a generalized copy constructor as well as the “normal” copy constructor.


Summary:
    .	Use member function templates to generate functions that accept all compatible types.
    .	If you declare member templates for generalized copy construction or generalized assignment, 
	    you’ll still need to declare the normal copy constructor and copy assignment operator, too.

**********/

#include <iostream>
#include <string>

template<typename T>
class TemplateMemfun{

    T m_data;

    public:

    //explicit TemplateMemfun(T val) : m_data{val} {
    //	std::puts("Parameterized constructor");
    //}

    template<typename U>
    explicit TemplateMemfun(U val) : m_data{val} { 
	    std::puts("Template Parameterized constructor");
    }

    TemplateMemfun(const TemplateMemfun & other) : m_data{other.m_data} { 
	    std::puts("Copy construtor");
    }

    template<typename U>
    TemplateMemfun(const TemplateMemfun<U> & other) : m_data{other.data()} {
	    std::puts("Generalized copy construtor");
    }

    T data() const { return m_data; }
};

int main() {
    {
	std::puts("=== Using Parameterized constructor ===");
	TemplateMemfun<int>			ival{3};
	TemplateMemfun<double>		dval{5.7};
	TemplateMemfun<std::string>	sval{std::string("sample string")};

	std::cout << ival.data() << '\n';
	std::cout << dval.data() << '\n';
	std::cout << sval.data() << '\n';

	std::puts("\n=== Using Copy construtor ===");
	TemplateMemfun<int>			ival2{ival};
	TemplateMemfun<double>		dval2{dval};
	TemplateMemfun<std::string>	sval2{sval};

	std::cout << ival.data() << '\n';
	std::cout << dval.data() << '\n';
	std::cout << sval.data() << '\n';

	std::puts("\n=== Using Generalized copy construtor ===");
	TemplateMemfun<int>			ival3{dval};
	//TemplateMemfun<int>			ival4{sval};

	TemplateMemfun<double>		dval3{ival};
	//TemplateMemfun<double>		dval4{sval};

	//TemplateMemfun<std::string>	sval3{ival};
	//TemplateMemfun<std::string>	sval4{dval};

	std::cout << ival3.data() << '\n';
	//std::cout << ival4.data() << '\n';

	std::cout << dval3.data() << '\n';
	//std::cout << dval4.data() << '\n';

	//std::cout << sval3.data() << '\n';
	//std::cout << sval4.data() << '\n';
    }

    {
	std::puts("\n=== Using template Parameterized constructor ===");
	TemplateMemfun<int>			ival{7.93};
	TemplateMemfun<double>		dval{5};
	TemplateMemfun<std::string>	sval{"sample string"};

	std::cout << ival.data() << '\n';
	std::cout << dval.data() << '\n';
	std::cout << sval.data() << '\n';
    }

    return 0;
}

/*****
    END OF FILE
**********/

