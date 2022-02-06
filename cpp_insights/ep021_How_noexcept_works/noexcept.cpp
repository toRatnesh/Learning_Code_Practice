/************
  This example demonstrates about 'noexcept'.

  noexcept operator:
  The noexcept operator performs a compile-time check that returns true if an expression is declared to not throw any exceptions.

  It can be used within a function template's noexcept specifier to declare that the function will throw exceptions for some types but not others.

  For more info visit:
https://en.cppreference.com/w/cpp/language/noexcept



noexcept specifier:
Specifies whether a function could throw exceptions.

noexcept is an improved version of throw(), which is deprecated in C++11. Unlike pre-C++17 throw(), noexcept will not call std::unexpected and may or may not unwind the stack, which potentially allows the compiler to implement noexcept without the runtime overhead of throw(). As of C++17, throw() is redefined to be an exact equivalent of noexcept(true).

For more info visit:
https://en.cppreference.com/w/cpp/language/noexcept_spec

 **************/

#include <iostream>

struct S {

    int m;

    bool set(int val) noexcept {
        try {
            if(0 > val) {
                throw std::runtime_error("-ve Value");
            }
        }
        catch(const std::runtime_error & e) {
            std::clog << e.what() << '\n';
        }
        m = val;

        return true;
    }

    int get() noexcept {
        return m;
    }

    bool fun_noexcept() noexcept {
        throw 42;   // throw will call std::terminate because function is declared noexcept
    }

    bool fun_except()  {
        throw 42;  
    }
};

int fun() noexcept {
    return 3+2;
}

int get() {
    return 2;
}

int main() {
    S s;
    s.set(5);

    try {
        std::clog << s.get() << '\n';
    }
    catch(...) {
        std::clog << "Exception in get()" << '\n';
    }

    std::clog << std::boolalpha 
        << "noexcept(s.set(2)): " << noexcept(s.set(2)) << '\n'
        << "noexcept(s.get()):  " << noexcept(s.get()) << '\n'
        << "noexcept(s.fun_noexcept()): " << noexcept(s.fun_noexcept()) << '\n'
        << "noexcept(s.fun_except()):   " << noexcept(s.fun_except()) << '\n'
        << "noexcept(fun()):   " << noexcept(fun()) << '\n'
        << "noexcept(get()):   " << noexcept(get()) << '\n'
        << '\n';

    return 0;
}

/********
  END OF FILE
 ********/
