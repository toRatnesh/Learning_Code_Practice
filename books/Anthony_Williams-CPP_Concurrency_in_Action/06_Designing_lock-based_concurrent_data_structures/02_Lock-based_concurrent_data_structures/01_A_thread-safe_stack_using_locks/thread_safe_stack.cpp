/*****

References
    Anthony Williams - C++ Concurrency in Action


6. Designing lock-based concurrent data structures

In this chapter we’ll start by taking the basic building blocks of locks and condition variables and revisit the design of basic data structures

6.2 Lock-based concurrent data structures

Ensure that
	right mutex is locked when accessing the data
	the lock is held for the minimum amount of time
	data can’t be accessed outside the protection of the mutex lock
	there are no race conditions inherent in the interface
	
need to consider the design of a data structure with multiple mutexes even more carefully

6.2.1 A thread-safe stack using locks
	consider example code

->  the basic thread safety is provided by protecting each member function with a lock on the mutex
->  By returning the popped data item directly as part of the call to pop(), you avoid a potential
	race condition that would be present with separate top() and pop() member functions
->  Locking a mutex may throw an exception, but because no data has been modified, this is safe
->	call to m_container.push() may throw an exception, either way, std::stack<> guarantees it will be safe
->  creation of res might throw an exception the call to std::make_shared might throw because it or 
	the copy constructor or move constructor of the data item to be returned might throw, 
	the C++ runtime and Standard Library ensure that there are no memory leaks and the new object (if any) is correctly destroyed
	Because you still haven’t modified the underlying stack, you’re OK
->  In second overload of pop() the copy assignment or move assignment operator that can throw
    Because you still haven’t modified the underlying stack, you’re OK
->  Finally, empty() doesn’t modify any data, so that’s exception-safe
->  The only member functions that aren’t safe are the constructors and destructors, but this isn’t a problem;
    the object can be constructed only once and destroyed only once.

Drawback of this implementaion
The stack doesn’t provide any means of waiting for an item to be added, so if a thread needs to wait, 
it must periodically call empty(), or call pop() and catch the empty_stack exceptions.

This makes this stack implementation a poor choice if such a scenario is required, because 
a waiting thread must either consume precious resources checking for data or the user must write external wait and notification code.

**********/

#include <iostream>
#include <stack>
#include <mutex>
#include <exception>
#include <memory>
#include <vector>
#include <string>
#include <thread>

struct empty_stack_exception : public std::exception {
    const char * what() const noexcept {
        return "Stack is empty";
    }
};

template<typename T>
class thsafe_stack {
    std::stack<T>       m_container;
    mutable std::mutex          m_cont_mutex;

    public:
    thsafe_stack()  {}

    thsafe_stack& operator=(const thsafe_stack & )     = delete;
    thsafe_stack(const thsafe_stack & other) {
        std::lock_guard     l_lock(m_cont_mutex);
        m_container         = other.m_container;
    }

    void push(T val) {
        std::lock_guard     l_lock(m_cont_mutex);
        m_container.push(val);
    }

    std::shared_ptr<T> pop() {
        std::lock_guard     l_lock(m_cont_mutex);
        if(m_container.empty()) throw   empty_stack_exception{};
        std::shared_ptr<T>  res = std::make_shared<T>(std::move(m_container.top()));
        m_container.pop();
        
        return res;
    }

    void pop(T & val) {
        std::lock_guard     l_lock(m_cont_mutex);
        if(m_container.empty()) throw   empty_stack_exception{};
        val = std::move(m_container.top());
        m_container.pop();
    }

    bool empty() const {
        std::lock_guard     l_lock(m_cont_mutex);
        return m_container.empty();
    }
};

thsafe_stack<std::string> gstack;

void reader(std::size_t count) {
    for(size_t i = 0; i < count; ++i) {
        try {
            if(not gstack.empty()) {
                const auto val = gstack.pop();
                std::cout << "Using pop(), Popped value is " << *val << '\n';
            }
        } catch(const empty_stack_exception & exp) {
            std::cout << exp.what() << '\n';
        }
    }
}

void reader_02(std::size_t count) {
    for(size_t i = 0; i < count; ++i) {
        try {
            if(not gstack.empty()) {
                std::string val;
                gstack.pop(val);
                std::cout << "Using pop(&), Popped value is " << val << '\n';
            }
        } catch(const empty_stack_exception & exp) {
            std::cout << exp.what() << '\n';
        }
    }
}

void writer(std::size_t count) {
    for(size_t i = 0; i < count; ++i) {
        gstack.push(std::string("string-")+std::to_string(i));
    }
}

int main() {

    std::size_t count = 10;

    std::thread l_writer_th(writer, count);
    std::thread l_reader01_th(reader, count/2);
    std::thread l_reader02_th(reader_02, count/2);

    l_writer_th.join();
    l_reader01_th.join();
    l_reader02_th.join();

    return 0;
}

/*****
    END OF FILE
**********/


