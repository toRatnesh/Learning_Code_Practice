/*******

References

    Programming with C++20 | Andreas Fertig
	https://en.cppreference.com/w/cpp/language/coroutines


Chapter 2 | Coroutines: Suspending functions

A coroutine is a function that can suspend itself.

2.9 Exceptions in coroutines

    A customization point for exceptions in the form of the PromiseType’s function 
        void unhandled_exception();

    There are two different stages where an exception can occur:

        1. During the setup of the coroutine, i.e., when the PromiseType and Generator are created.
        2. After the coroutine is set up and about to or already runs.

    In the first stage, our PromiseType and Generator are not completely set up.
    An exception that occurs during that stage is directly passed to our calling code.

    We are at this stage roughly as long as the evaluation of initial_suspend is not finished. 
    After that, we are in stage 2.

    Option 1: Let it crash
        Each exception that occurs in our coroutine’s body or in the other
        customization points of the PromiseType will cause a call to unhandled_exception

        The codeless approach is to leave unhandled_exception empty.
        If unhandled_exception returns to our coroutine FSM, 
        the compiler shuts down the coroutine by calling final_suspend

        To recap, leaving unhandled_exception masks the exception, 
        and your program will likely crash shortly after

    Option 2: Controlled termination
        implementation of unhandled_exception, call either std::terminate or abort
        gives you a chance to set a break-point with a debugger to see the call stack

    Option 3: Rethrow the exception
        re-throw the exception in the body of unhandled_exception
        That way, the exception reaches the outer try-catch block
        This allows us to deal with the exception outside of the coroutine

        As before, the coroutine is still unusable, and all objects get destroyed, 
        but we have a chance for a re-run with different input values or so.

*******/

#include <iostream>
#include <format>

#include <coroutine>
#include <exception>
#include <utility>

namespace coro_iterator {

    template <typename PT>
    struct iterator {
        std::coroutine_handle<PT> m_coro_hdl{nullptr};

        void resume() {
            if (not m_coro_hdl.done()) {
                m_coro_hdl.resume();
            }
        }

        iterator() = default;
        iterator(std::coroutine_handle<PT> hco) : m_coro_hdl{hco} { resume(); }

        void operator++() { resume(); }
        bool operator==(const iterator&) const { return m_coro_hdl.done(); }

        const auto& operator*() const { return m_coro_hdl.promise().m_value; }
    };

}  // namespace coro_iterator

template <typename T, typename G>
struct promise_type_base {
    T m_value;  // A - The value yielded or returned from a coroutine

    auto yield_value(T value)  // B - Invoked by co_yield or co_return
    {
        if(5 == value) {
            throw std::runtime_error("5 is not allowed");
        }

        m_value = std::move(value);     // C - Store the yielded value for access
                                       // outside the coroutine
        return std::suspend_always{};  // D - Suspend the coroutine here
    }

    G get_return_object() { return G{this}; };  // E - Return generator
    static auto get_return_object_on_allocation_failure() { return G{nullptr}; }

    std::suspend_always initial_suspend() { return {}; }
    std::suspend_always final_suspend() noexcept { return {}; }

    void return_void() {}
    void unhandled_exception() { 
        std::cout << "Inside " << __func__ << " rethrowing exception\n";
        //std::terminate();
        throw;
    }
};

template <typename T>
class generator {

    public:
    using promise_type = promise_type_base<T, generator>;  // A - The PromiseType
    using PromiseTypeHandle = std::coroutine_handle<promise_type>;

    // D - As the default ctor is private promise_type needs to be a friend
    friend promise_type;

    private:
    explicit generator(promise_type* p)
        : m_coro_hdl{PromiseTypeHandle::from_promise(*p)} {
            //throw std::runtime_error("Error in creating generator");
        }

    PromiseTypeHandle m_coro_hdl;  // E - The coroutine handle

   public:
    // B- Make the generator iterable
    using iterator = coro_iterator::iterator<promise_type>;
    iterator begin() { return {m_coro_hdl}; }
    iterator end() { return {}; }

    generator(generator const&) = delete;
    generator(generator&& rhs)
        : m_coro_hdl(std::exchange(rhs.m_coro_hdl, nullptr)) {}

    ~generator() {
        // C - We have to maintain the life - time of the coroutine
        if (m_coro_hdl) {
            m_coro_hdl.destroy();
        }
    }
};

using int_generator = generator<int>;

int_generator counter(const int start, const int end) {
    
    int val{start};

    while(val < end) {
        co_yield val;
        ++val;
    }

}

int main() {

    try {

        auto cg = counter(0, 10);

        for(auto c : cg) {
            std::cout << std::format("counter value: {}\n", c);
        }

    }
    catch(const std::exception & exp) {
        std::cout << "Exception: " << exp.what() << '\n';
    }

    return 0;

}

/*****
    END OF FILE
**********/

