/*****

References
    Asynchronous Programming with C++ | Javier Reguera-Salgado & Juan Antonio Rufes
    https://en.cppreference.com/cpp/coroutine
    https://en.cppreference.com/cpp/language/coroutines
    https://en.cppreference.com/cpp/coroutine/generator

    https://github.com/toRatnesh/Learning_Code_Practice/tree/main/books/Andreas_Fertig-Programming_with_CPP20/ch02_Coroutines_Suspending_functions


Chapter 8 | Asynchronous Programming Using Coroutines

The parsing coroutine
    simple string parser. The coroutine will wait for the input, a std::string object, and will yield the output, a number, after parsing the input string

**********/

#include <coroutine>
#include <iostream>
#include <optional>
#include <utility>
#include <thread>

template <typename input_t, typename output_t>
struct coro_return_t {
    struct promise_type {
        output_t out_data{};
        std::optional<input_t> in_data{};

        auto get_return_object() noexcept { return coro_return_t{*this}; };

        auto yield_value(output_t data) noexcept {
            out_data = std::move(data);

            return std::suspend_always{};
        }

        auto initial_suspend() noexcept { return std::suspend_always{}; };

        auto final_suspend() noexcept { return std::suspend_always{}; };

        auto unhandled_exception() {

        };

        auto return_void() noexcept {

        }

        auto await_transform(input_t) noexcept {
            struct awaiter {
                promise_type& prom;

                auto await_ready() const noexcept {
                    return prom.in_data.has_value();
                };

                auto await_suspend(
                    std::coroutine_handle<promise_type>) const noexcept {}

                input_t await_resume() const noexcept {
                    return *std::exchange(prom.in_data, std::nullopt);
                }
            };

            return awaiter(*this);
        };
    };

    std::coroutine_handle<promise_type> coro_handle{};

    ~coro_return_t() {
        if (coro_handle) {
            coro_handle.destroy();
        }
    }

    explicit coro_return_t(promise_type& prom)
        : coro_handle{std::coroutine_handle<promise_type>::from_promise(prom)} {

    }

    output_t get() {
        if (not coro_handle.done()) {
            coro_handle.resume();
        }

        return std::move(coro_handle.promise().out_data);
    }

    void set(input_t data) {
        coro_handle.promise().in_data = std::move(data);

        if (not coro_handle.done()) {
            coro_handle.resume();
        }
    }
};

coro_return_t<char, int> parse_string() {
    while (true) {
        char c = co_await char{};
        int number{};
        int sign{1};
        if (c != '-' && c != '+' && !std::isdigit(c)) {
            continue;
        }
        if (c == '-') {
            sign = -1;
        } else if (std::isdigit(c)) {
            number = number * 10 + c - '0';
        }
        while (true) {
            c = co_await char{};
            if (std::isdigit(c)) {
                number = number * 10 + c - '0';
            } else {
                break;
            }
        }
        co_yield number* sign;
    }
}

int main() {

    auto num_parser = parse_string();

    {
        std::string num1 = "-123454321#";

        // parse the first half of the string
        std::size_t sz = num1.size();
        for (std::size_t i = 0; i < sz / 2; ++i) {
            num_parser.set(num1[i]);
        }

        std::cout << "parsing number...\n";

        // parse the second half of the string
        for (std::size_t i = sz / 2; i < sz; ++i) {
            num_parser.set(num1[i]);
        }
        
        // print the parsed number
        std::cout << num_parser.get() << std::endl;
    }

    std::string num2 = "-123454321#98765#-20241337#+31415#";
    // now let's parse a string containing several numbers
    for (char c : num2) {
        num_parser.set(c);

        // do something...

        std::this_thread::sleep_for(std::chrono::seconds(1));

        if (c == '#') {
            std::cout << num_parser.get() << std::endl;
        }
    }

    return 0;
}

/*****
    END OF FILE
**********/
