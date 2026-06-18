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
#include <iostream>


namespace nonstd {

    struct generator {

        struct promise_type {
            int out_data{};

            generator get_return_object() noexcept {
                return generator{*this};
            }


            auto yield_value(int data) noexcept {
                out_data = data;
                return std::suspend_always{};
            }

            auto initial_suspend() noexcept {
                return std::suspend_always{};
            }

            auto final_suspend() noexcept {
                return std::suspend_always{};
            }

            auto unhandled_exception() noexcept {
                std::println("Inside {}", __func__);
            }

            auto return_void() noexcept {
                std::println("Inside {}", __func__);
            }

        };

        std::coroutine_handle<promise_type>     handle{};

        explicit generator(promise_type & prom) : 
            handle{std::coroutine_handle<promise_type>::from_promise(prom)} 
        {
            //std::println("Inside {}", __func__);
        }  

        ~generator() {
            //std::println("Inside {}", __func__);

            if(handle) {
                handle.destroy();
            }
        }    

        auto next_value() {
            if(not handle.done()) {
                handle.resume();
            }
            return handle.promise().out_data;
        }
    };


}

std::generator<int> std_fibonacci_generator()
{
    
    int a{0};
    int b{1};

    while(true) {
        co_yield a;
        int c = a + b;
        a = b;
        b = c;
    }
}

nonstd::generator fibonacci_generator()
{
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
    {
        std::println("=== using std::generator ===");
        
        auto fib_gen = std_fibonacci_generator();

        for(auto it = fib_gen.begin(); it != fib_gen.end(); ++it) {
            
            if((*it) > 100) {
                std::println();
                break;
            }

            std::print("{}, ", *it);
        }
    }

    {
        std::println("=== using custom generator ===");

        auto fib_gen = fibonacci_generator();

        while(true) {
            auto val = fib_gen.next_value();
            if(val > 100) {
                std::println();
                break;
            }

            std::print("{}, ", val);
        }
    }

    return 0;
}

/*****
    END OF FILE
**********/

