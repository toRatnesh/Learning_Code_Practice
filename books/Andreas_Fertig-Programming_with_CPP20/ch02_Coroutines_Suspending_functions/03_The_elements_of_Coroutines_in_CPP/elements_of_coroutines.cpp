/*******

Chapter 2 | Coroutines: Suspending functions

A coroutine is a function that can suspend itself.

2.3 The elements of Coroutines in C++

2.3.1 Stackless Coroutines in C++
2.3.2 The new kids on the block: co_await, co_return and co_yield
2.3.3 The generator
2.3.4 The promise_type
2.3.5 An iterator for generator
2.3.6 Coroutine customization points
2.3.7 Coroutines restrictions


2.3.1 Stackless Coroutines in C++

	Coroutines come in two flavors, 
		1.	stackful coroutines
		2.	stackless coroutines
		
	C++20 brings us stackless coroutines

		A coroutine can be seen as a transformation of a coroutine-function into an finite state machine (FSM).
		The FSM maintains the internal state, where the coroutine was left when it returned earlier, 
		the values that were passed to the coroutine upon creation.

	coroutine-frame
		This internal state of the FSM, as well as the values, passed to the coroutine, need to be stored somewhere.
		This storage section is called a coroutine-frame.

		In C++20 the frame is allocated on the heap.
		The heap allocation is done by the compiler automatically every time a coroutine is created.

	
2.3.2 The new kids on the block: co_await, co_return and co_yield
	Whenever we use one of these keywords in a function, this function automatically becomes a coroutine.
	====================================================
	Keyword        Action        Type        State
	====================================================
	co_yield       Output       promise      Suspended
	co_return      Output       promise      Ended
	co_await       Input        awaitable    Suspended
	====================================================


2.3.3 The generator

	In C++, we cannot have a plain return type like int or std::string.
	We need to wrap the type into a so-called generator.
	The reason is that coroutines in C++ are a very small abstraction for an FSM.
	The generator gives us implementation freedom and the choice of how we like to model our coroutine.
	
	For a class or struct to be a generator type, this class needs to fulfill an 
	Application Programming Interface (API) required to make the FSM work.
	
	During the suspension, the state of the coroutine needs to be stored somewhere, 
	plus we need a mechanism to obtain the yielded value from outside the coroutine. 
	A generator manages this job.

	template <typename T>
	class generator {

		using promise_type = promise_type_base<T, generator>;  // A - The PromiseType
		using PromiseTypeHandle = std::coroutine_handle<promise_type>;

		// D - As the default ctor is private promise_type needs to be a friend
		friend promise_type;

		explicit generator(promise_type* p)
			: m_coro_hdl{PromiseTypeHandle::from_promise(*p)} {}

		PromiseTypeHandle m_coro_hdl;     // E - The coroutine handle

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


	A -	promise_type, is a name the compiler looks for
		see the promise_type as a state controller of a coroutine.
		Hence its promise_type, does not necessarily give us only one value.

	B -	iterator. This is due to our range-based for-loop needing a begin and end.

	E - The coroutine handle, is our access key to the coroutine state machine.
		This type, std::coroutine_handle<T>, can be seen as a wrapper around a pointer, pointing to the coroutine frame.
		
		A special thing about the coroutine frame is that the compiler calls new for us whenever a coroutine, 
		and with that, a generator and promise_type, is created. This memory is the coroutine frame.

	C - 
		The compiler knows when a coroutine is started. However, the compiler does not, at least easily, 
		know when a coroutine is finished or no longer needed.
		The easiest way is to let generator free the coroutine-frame in its destructor.

		The memory resource is also the reason why generator is move-only.

	D - constructor of generator is private.
		That is because generator is part of promise_type, or better promise_type_base.
		During the allocation of the coroutine-frame, the promise_type is created.


2.3.4 The promise_type

	template <typename T, typename G>
	struct promise_type_base {
		T m_value;                           // A - The value yielded or returned from a coroutine

		auto yield_value(T value)           // B - Invoked by co_yield or co_return 
		{
			m_value = std::move(value);      // C - Store the yielded value for access outside the coroutine
			return std::suspend_always{};   // D - Suspend the coroutine here
		}

		G get_return_object() { return G{this}; };  // E - Return generator
		static auto get_return_object_on_allocation_failure() { return G{nullptr}; }

		std::suspend_always initial_suspend() { return {}; }
		std::suspend_always final_suspend() noexcept { return {}; }

		void return_void() {}
		void unhandled_exception() { std::terminate(); }
	};
	
	A - promise_type_base stores a value.
		This is the value we can yield with co_yield or co_return from the body of a coroutine to the caller.
		
	B -	promise-type API the function yield_value. With each call to co_yield or co_return, 
		this function yield_value is called with the value that was used with co_yield or co_return.
		
	D -	ensures that the coroutine gets suspended after we return from yield_value.

		
	Function get_return_object is called when the coroutine is created.
	This is what we store as IntGenerator.

	The way the channel is created here is that promise_type_base passes its this-pointer to the constructor of generator.


2.3.5 An iterator for generator

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
	
	One thing to point out here is that iterator does not call destroy on the coroutine handle. 
	The reason is that generator controls the life-time of the coroutine-handle. 
	iterator is only allowed to have a temporary view of the data.


2.3.6 Coroutine customization points
	Check Diagram
	
	get_return_object_on_allocation_failure, this static method controls which operator new is called.
	For a PromiseType with that function, the operator new(size_t, nothrow_t) overload gets called.
	Should operator new return a nullptr, then get_return_object_on_allocation_failure is invoked 
	to obtain some kind of backup object.
	This prevents the program from crashing due to a nullptr access.
	However, the coroutine will, of course, not run.
	Instead, such a coroutine looks like it has already finished.
	
	unhandled_exception is described in section "2.9 Exceptions in coroutines"

2.3.7 Coroutines restrictions

	.	constexpr and consteval functions cannot be coroutines
	.	Neither a constructor nor a destructor can be a coroutine
	
	.	A function using varargs. A variadic function template works
	.	Lambdas can be coroutines.
	.	A function with plain auto as return-type, or with a concept type, 
		cannot be a coroutine. auto with trailing return-type works.
	.	main cannot be a coroutine.
	
	.	Further, a coroutine cannot use plain return, it must be either co_return or co_yield.

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
        m_value = std::move(value);     // C - Store the yielded value for access
                                       // outside the coroutine
        return std::suspend_always{};  // D - Suspend the coroutine here
    }

    G get_return_object() { return G{this}; };  // E - Return generator
    static auto get_return_object_on_allocation_failure() { return G{nullptr}; }

    std::suspend_always initial_suspend() { return {}; }
    std::suspend_always final_suspend() noexcept { return {}; }

    void return_void() {}
    void unhandled_exception() { std::terminate(); }
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
        : m_coro_hdl{PromiseTypeHandle::from_promise(*p)} {}

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

    auto cg = counter(0, 10);

    for(auto c : cg) {
        std::cout << std::format("counter value: {}\n", c);
    }


    return 0;

}

/*****
    END OF FILE
**********/

