/*****

References
    Anthony Williams - C++ Concurrency in Action

3.2 Protecting shared data with mutexes
    mutex (mutual exclusion)
        You could mark all the pieces of code that access the data structure as mutually exclusive, so that if any thread was running one of them, any other thread that tried to access that data structure had to wait until the first thread was finished
        Mutexes also has issue of deadlock and protecting either too much or too little data

3.2.3 Spotting race conditions inherent in interfaces
	Consider using shared std::stack in mutithreaded program, the results of empty() and size() can’t be relied on. Although they might be correct at the time of the call, once they’ve returned, other threads are free to access the stack and might push() new elements onto or pop() the existing ones off of the stack before the thread that called empty() or size() could use that information.
	
	In this case even if we protect the internal data with a mutex, this interface is still inherently subject to race conditions. This problem is not unique to a mutex-based implementation; it’s an interface problem, so the race conditions would still occur with a lock-free implementation.

	Alternatives for interface problem:
	
	1: PASS IN A REFERENCE
		pass a reference to a variable in which you want to receive the popped value as an argument
		
		Drawback:
		it requires the calling code to construct an instance of the stack’s value type prior to the call
		Its impractical, because constructing an instance is expensive in terms of time or resources
		the constructors require parameters that aren’t necessarily available at this point in the code
		many user-defined types do not support assignment, though they may support move construction or even copy construction (and allow return by value)
			
	2: REQUIRE A NO-THROW COPY CONSTRUCTOR OR MOVE CONSTRUCTOR
		restrict the use of your thread-safe stack to those types that can safely be returned by value without throwing an exception
		Although this is safe, it’s not ideal. 
		There are many more user-defined types with copy constructors that can throw and don’t have move constructors
		would be unfortunate if such types couldn’t be stored in your thread-safe stack.
		
	3: RETURN A POINTER TO THE POPPED ITEM
		return a pointer to the popped item rather than return the item by value
		advantage: pointers can be freely copied without throwing an exception
		disadvantage: for simple types such as integers, the overhead of such memory management can exceed the cost of returning the type by value
		
		Performance impact: requiring that each object in the stack be allocated separately with new would impose quite an overhead compared to the original non-thread-safe version.
		
	4: PROVIDE BOTH OPTION 1 AND EITHER OPTION 2 OR 3
		If you’ve chosen option 2 or 3, it’s relatively easy to provide option 1 as well, and 
		this provides users of your code the ability to choose whichever option is most appropriate for them at little additional cost.
		
	EXAMPLE DEFINITION OF A THREAD-SAFE STACK
		Following code
		only two interface: push() and pop()
		implements options 1 and 3: there are two overloads of pop(),
		First, takes a reference to a location in which to store the value and 
		Second, returns std::shared_ptr<>

**********/

#include <iostream>
#include <mutex>
#include <thread>
#include <exception>
#include <stack>
#include <memory>
#include <chrono>

class EmptyStackException : std::exception {
    public:
    const char * what() const noexcept {
        return "Stack is empty";
    }
};

template<typename T>
class ThreadSafeStack {
    std::stack<T> m_stack_data;
    std::mutex m_stack_mutex;

    public:
    ThreadSafeStack() { }
    ThreadSafeStack(const ThreadSafeStack & other) {
        // copy in the constructor body rather than the member initializer list 
        // in order to ensure that the mutex is held across the copy
        
        // copy constructor locks the mutex in the source object
        std::lock_guard guard(other.m_stack_mutex); // ATTENTION: other.m_stack_mutex is used
        m_stack_data = other.m_stack_data;
    }

    ThreadSafeStack& operator=(const ThreadSafeStack & other) = delete;

    void push(T value) {
        std::lock_guard guard(m_stack_mutex);
        m_stack_data.push(value);
    }

    std::shared_ptr<T> pop() {
        std::lock_guard guard(m_stack_mutex);
        if(m_stack_data.empty())  {
            throw EmptyStackException{};
        }

        std::shared_ptr<T> res_val = std::make_shared<T>(m_stack_data.top()); 
        m_stack_data.pop();
        return res_val;
    }

    void pop(T & value) {
        std::lock_guard guard(m_stack_mutex);
        if(m_stack_data.empty())  {
            throw EmptyStackException{};
        }

        value =  m_stack_data.top();
        m_stack_data.pop();        
    }

    bool empty() const {
        std::lock_guard guard(m_stack_mutex);
        return m_stack_data.empty();
    }

};

ThreadSafeStack<size_t> thr_safe_stack;

void reader(size_t elems) {
    size_t  ret_val = 0;

    for(size_t i = 0; i < elems; ++i) {
        
        try {
            ret_val = *(thr_safe_stack.pop());
        } catch (const EmptyStackException & ex) {
            std::cout << ex.what() << '\n';
            continue;
        }

        std::cout << "popped value is " << ret_val << '\n';
        std::this_thread::sleep_for(std::chrono::nanoseconds(1));
    }
}

void reader_02(size_t elems) {
    size_t  ret_val = 0;

    for(size_t i = 0; i < elems; ++i) {
        
        try {
            thr_safe_stack.pop(ret_val);
        } catch (const EmptyStackException & ex) {
            std::cout << ex.what() << '\n';
            continue;
        }
        
        std::cout << "popped value is " << ret_val << '\n';

        std::this_thread::sleep_for(std::chrono::nanoseconds(1));
    }
}


void writer(size_t elems) {
    for(size_t i = 0; i < elems; ++i) {
        thr_safe_stack.push(i+1);
    }
}

int main() {

    std::thread thr_write(writer, 10);
    std::thread thr_read(reader, 10);
    std::thread thr_read_02(reader_02, 10);
    
    if(thr_write.joinable())        thr_write.join();
    if(thr_read.joinable())         thr_read.join();
    if(thr_read_02.joinable())      thr_read_02.join();
    
    return 0;
}

/*****
    END OF FILE
**********/


