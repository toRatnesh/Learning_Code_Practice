/*****

References
    Asynchronous Programming with C++ | Juan Antonio Rufes
    https://en.cppreference.com/cpp/coroutine
	https://en.cppreference.com/cpp/language/coroutines
	https://en.cppreference.com/cpp/coroutine/generator
	
	https://github.com/toRatnesh/Learning_Code_Practice/tree/main/books/Andreas_Fertig-Programming_with_CPP20/ch02_Coroutines_Suspending_functions
	

Chapter 8 | Asynchronous Programming Using Coroutines

Coroutine generators
    A generator is a coroutine that generates a sequence of elements by repeatedly resuming itself from the point that it was suspended.

Fibonacci sequence generator
    Write a generator and use to implement a coroutine function which returns numbers in fibonacci sequence

C++23 std::generator
    C++23 introduced the std::generator template class.
    By using it, we can write coroutine-based generators without writing any of the required code, such as the promise type, the return type, and all their functions.

**********/

#include <print>
#include <generator>

std::generator<int> fibonacci_generator() {
    
    int a{0};
    int b{1};

    while(true) {
        co_yield a;
        int c = a + b;
        a = b;
        b = c;
    }
}

int main() {

    auto fib_gen = fibonacci_generator();

    for(auto it = fib_gen.begin(); it != fib_gen.end(); ++it) {
        
        if((*it) > 100) {
            std::println();
            break;
        }

        std::print("{}, ", *it);
    }

    return 0;
}

/*****
    END OF FILE
**********/



