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


6.2.2 A thread-safe queue using locks and condition variables

-> Two overloads of try_pop() are almost identical to the pop() functions
except that they don’t throw anmexception if the queue is empty
Instead, they return either a bool value indicating whether a value was retrieved or 
a NULL pointer if no value could be retrieved by the pointer-returning overload

-> call to m_condv.notify_one() in push()

-> new wait_and_pop() functions are a solution to the problem of waiting for a queue entry that you saw with the stack
rather than continuously calling empty(), the waiting thread can call wait_and_pop() and 
the data structure will handle the waiting with a condition variable

Regard to exception safety

only one thread will be woken by the call to data_cond.notify_one()
But if that thread then throws an exception in wait_and_pop(),  
such as when the new std::shared_ptr<> is constructed, 
none of the other threads will be woken

Solutions
1. Use data_cond.notify_all(), which will wake all the threads but at the cost of most of them 
then going back to sleep when they find that the queue is empty after all

2. wait_and_pop() call notify_one() if an exception is thrown, 
so that another thread can attempt to retrieve the stored value

3. move the std::shared_ptr<> initialization to the push() call and store 
std::shared_ptr<> instances rather than direct data values

class thsafe_queue {
	...
	std::queue<std::shared_ptr<T> > data_queue;
	...
}

**********/

#include <iostream>
#include <queue>
#include <mutex>
#include <exception>
#include <memory>
#include <vector>
#include <string>
#include <thread>
#include <condition_variable>
#include <syncstream>

template<typename T>
class thsafe_queue {
    std::queue<T>               m_container;
    mutable std::mutex          m_mutex;
    std::condition_variable     m_condv;

    public:
    thsafe_queue()  {}

    thsafe_queue& operator=(const thsafe_queue &)   = delete;
    thsafe_queue(const thsafe_queue & other) {
        std::lock_guard     l_lock(m_mutex);
        m_container = other.m_container;
    }

    void push(T val) {
        std::lock_guard     l_lock(m_mutex);
        m_container.push(std::move(val));
        m_condv.notify_one();
    }

    std::shared_ptr<T>  wait_and_pop() {
        std::unique_lock    lu_lock(m_mutex);
        m_condv.wait( lu_lock, [this](){return not m_container.empty(); });
        auto ret = std::make_shared<T>(std::move(m_container.front()));
        m_container.pop();
        return ret;
    }

    void wait_and_pop(T & res) {
        std::unique_lock    lu_lock(m_mutex);
        m_condv.wait(lu_lock, [this](){return not m_container.empty(); });
        res = std::move(m_container.front());
        m_container.pop();
    }

    std::shared_ptr<T> try_pop() {
        std::lock_guard     l_lock(m_mutex);
        if(m_container.empty()) {
            return std::shared_ptr<T>();
        }
        auto ret = std::make_shared<T>(std::move(m_container.front()));
        m_container.pop();
        return ret;
    }

    bool try_pop(T & res) {
        std::lock_guard     l_lock(m_mutex);
        if(m_container.empty()) {
            return false;
        } 
        res = std::move(m_container.front());
        m_container.pop();
        return true;
    }

    bool empty() const {
        std::lock_guard     l_lock(m_mutex);
        return m_container.empty();
    }
};

thsafe_queue<std::string> gqueue;

std::osyncstream syn_cout(std::cout);

void read_try_pop_using_ref(std::size_t count) {
    std::string res;
    for(std::size_t i = 0; i < count; ++i) {
        bool ret = gqueue.try_pop(res);
        if(ret) {
            syn_cout << "try_pop(&), Popped value is " << res << '\n';
        } else {
            syn_cout << "Queue is empty\n";
        }
    }
}

void read_try_pop(std::size_t count) {
    for(std::size_t i = 0; i < count; ++i) {
        const auto res = gqueue.try_pop();
        if(res) {
            syn_cout << "try_pop(), Popped value is " << *res << '\n';
        } else {
            syn_cout << "Queue is empty\n";
        }
    }
}

void read_wait_pop_using_ref(std::size_t count) {
    std::string res;
    for(std::size_t i = 0; i < count; ++i) {
        if(not gqueue.empty()) {
            gqueue.wait_and_pop(res);
            syn_cout << "wait_and_pop(&), Popped value is " << res << '\n';
        } else {
            syn_cout << "Queue is empty\n";
        }
    }
}

void read_wait_pop(std::size_t count) {
    for(std::size_t i = 0; i < count; ++i) {
        const auto res = gqueue.wait_and_pop();
        if(res) {
            syn_cout << "wait_and_pop(), Popped value is " << *res << '\n';
        } else {
            syn_cout << "Queue is empty\n";
        }
    }
}

void writer(std::size_t count) {
    for(std::size_t i = 0; i < count; ++i) {
        gqueue.push(std::string("string-") + std::to_string(i));
    }
}

int main() {

    std::size_t     count = 20;

    std::thread     l_th_writer(writer, count);

    std::thread     l_th_wait_pop_ref(read_wait_pop_using_ref, count/4);
    std::thread     l_th_wait_pop(read_wait_pop, count/4);

    std::thread     l_th_try_pop_ref(read_try_pop_using_ref, count/4);
    std::thread     l_th_try_pop(read_try_pop, count/4);

    l_th_wait_pop_ref.join();
    l_th_wait_pop.join();

    l_th_writer.join();

    l_th_try_pop_ref.join();
    l_th_try_pop.join();

    return 0;
}

/*****
    END OF FILE
**********/


