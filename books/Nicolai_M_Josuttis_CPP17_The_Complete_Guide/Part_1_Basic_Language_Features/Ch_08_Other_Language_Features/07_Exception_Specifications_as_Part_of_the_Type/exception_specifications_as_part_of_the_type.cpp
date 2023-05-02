/********************

References:
	C++17 - The Complete Guide | Nicolai M. Josuttis

7. Exception Specifications as Part of the Type
    Since C++17 exception handling specifications became part of the type of a function    
    Using function that doesn’t throw where functions are allowed to throw is still valid
    overloading a function name for the same signature with a different exception specification is not allowed
    it is still the case that you are not allowed to ignore a noexcept specification of a base class

    Using Conditional Exception Specifications
        When using conditional noexcept specifications, 
        the type of the functions depends on whether the condition is true or false

    Consequences for Generic Libraries
        for example for std::is_function<>
        Now, with C++17, the number of partial specialization is doubled by adding a noexcept qualifier to all these partial specializations so that we get 48 partial specializations now
        Libraries not implementing the noexcept overloads might no longer compile code that uses them to pass functions or function pointers to places where noexcept is required.

*********************/

#include <iostream>
#include <cassert>
#include <type_traits>

int fun_noexcept() noexcept {   return 5;   }
int fun_except() {  return 4;   }

// overloading a function name for the same signature with a different exception specification is not allowed
int fun() noexcept { return 11; }
//int fun() { return 21; }    // CE: error: redefinition of 'int fun()'

struct Base {
    virtual int foo() noexcept { return 1; }
};

// it is still the case that you are not allowed to ignore a noexcept specification of a base class:
struct Derived : public Base {
    //int foo()  { return 11; }           // CE: looser exception specification on overriding virtual function 'virtual int Derived::foo()'
    //int foo() override { return 11; }   // CE: looser exception specification on overriding virtual function 'virtual int Derived::foo()'
    int foo() noexcept override { return 11; } 
};

// Using Conditional Exception Specifications
void f1() { }
void f2() noexcept { }
void f3() noexcept(sizeof(int) == 4) { }    // this function has same type as f1 and f2 if sizeof(int) == 4
void f4() noexcept(sizeof(int) != 4) { }    // this funcion has always different typr than f3 because noexcept condition is opposite
void f5() throw() { } // throw() is same as noexcept but it's deprecated

// Consequences for Generic Libraries
template<typename Callable>
void call_1(Callable callable1, Callable callable2) { callable1(); callable2(); }

template<typename Callable, typename Callable_noexcept>
void call_2(Callable callable, Callable_noexcept callable_noexcept) { callable(); callable_noexcept(); }



int main() {
    assert(4 == sizeof(int));

    using fp_noexcept_t = int (*)() noexcept;
    using fp_except_t   = int (*)();

    fp_noexcept_t l_fp_noexcept;
    l_fp_noexcept = fun_noexcept;
    assert(5 == l_fp_noexcept());
    //l_fp_noexcept = fun_except;     // error: invalid conversion from 'int (*)()' to 'fp_noexcept_t' {aka 'int (*)() noexcept'} 
    
    fp_except_t l_fp_except;
    l_fp_except = fun_noexcept; // Using function that doesn’t throw where functions are allowed to throw is still valid
    assert(5 == l_fp_except());
    l_fp_except = fun_except;
    assert(4 == l_fp_except());

    // Consequences for Generic Libraries
    //call_1(fun_noexcept, fun_except); // error: no matching function for call to 'call_1(int (&)() noexcept, int (&)())'
    call_2(fun_noexcept, fun_except);

    static_assert(std::is_function_v<decltype(fun_noexcept)>);
    static_assert(std::is_function_v<decltype(fun_except)>);

    return 0;
}

/********
    END OF FILE
********/
