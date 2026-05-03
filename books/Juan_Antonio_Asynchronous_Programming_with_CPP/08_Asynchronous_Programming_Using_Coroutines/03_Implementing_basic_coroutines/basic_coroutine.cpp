/*****

References
    Asynchronous Programming with C++ | Juan Antonio Rufes
    https://en.cppreference.com/cpp/coroutine
	https://en.cppreference.com/cpp/language/coroutines
	https://en.cppreference.com/cpp/coroutine/generator
	
	https://github.com/toRatnesh/Learning_Code_Practice/tree/main/books/Andreas_Fertig-Programming_with_CPP20/ch02_Coroutines_Suspending_functions
	

Chapter 8 | Asynchronous Programming Using Coroutines
    
Implementing basic coroutines



**********/

#include <iostream>
#include <string>
#include <coroutine>


struct coro_string {
    
    struct promise_type {

        std::string     out_data{};
        std::string     in_data{};

        coro_string get_return_object() noexcept {
            std::cout << "Inside " << __func__ << '\n';
            return coro_string{*this};
        }

        auto yield_value(std::string data) noexcept {
            std::cout << "Inside " << __func__ << '\n';
            out_data = std::move(data);

            return std::suspend_always{};
        }

        auto initial_suspend() noexcept {
            std::cout << "Inside " << __func__ << '\n';
            return std::suspend_always{};
        }

        auto final_suspend() noexcept {
            std::cout << "Inside " << __func__ << '\n';
            return std::suspend_always{};
        }

        auto unhandled_exception() noexcept {
            std::cout << "Inside " << __func__ << '\n';
        }

        auto return_void() noexcept {
            std::cout << "Inside " << __func__ << '\n';
        }

        auto await_transform(std::string) noexcept {

            struct awaiter {
                promise_type & prom;

                bool await_ready() const noexcept {
                    return true;
                }

                std::string await_resume() const noexcept {
                    return std::move(prom.in_data);
                }

                void await_suspend(std::coroutine_handle<promise_type>) const noexcept {

                }
            };

            return awaiter{*this};
        }

    };  // promise_type

    std::coroutine_handle<promise_type>     handle{};

    explicit coro_string(promise_type & prom) : handle{std::coroutine_handle<promise_type>::from_promise(prom)} {
        std::cout << "Inside " << __func__ << '\n';
    }

    ~coro_string() {
        if(handle) {
            handle.destroy();
        }
        std::cout << "Inside " << __func__ << '\n';
    }

    std::string get() {
        if(not handle.done()) {
            handle.resume();
        }
        return std::move(handle.promise().out_data);
    }

    void set(std::string data) {
        handle.promise().in_data = std::move(data);
        if(not handle.done()) {
            handle.resume();
        }
    }

};

coro_string processData() {
    //std::cout << co_await std::string{} << '\n';
    //co_yield std::string{"-- Returning a string value from coroutine function --"};

    auto data = co_await std::string{};
    co_yield data;

    co_return ;
}


int main() {

    auto data_processor = processData();
    data_processor.set("-- Setting a string value to coroutine --");
    auto data = data_processor.get();
    std::cout << "Data is: " << data << '\n'; 

    return 0;
}

/*****
    END OF FILE
**********/

