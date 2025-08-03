/*****

References
    Anthony Williams - C++ Concurrency in Action

6. Designing lock-based concurrent data structures

    In this chapter we’ll start by taking the basic building blocks of locks and 
    condition variables and revisit the design of basic data structures

6.2 Lock-based concurrent data structures

    Ensure that
        right mutex is locked when accessing the data
        the lock is held for the minimum amount of time
        data can’t be accessed outside the protection of the mutex lock
        there are no race conditions inherent in the interface
        
    need to consider the design of a data structure with multiple mutexes even more carefully


6.2.2 A thread-safe queue using locks and condition variables

    ->  Two overloads of try_pop() are almost identical to the pop() functions
        except that they don’t throw anmexception if the queue is empty
        Instead, they return either a bool value indicating whether a value was retrieved or 
        a NULL pointer if no value could be retrieved by the pointer-returning overload

    ->  call to m_condv.notify_one() in push()

    ->  new wait_and_pop() functions are a solution to the problem of waiting for a queue entry that you saw with the stack
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

        class ThreadSafeQueue {
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
#include <vector>
#include <future>
#include <iomanip>

#define VERIFY_PRINT(C) std::cout << "Assertion failed " << std::quoted(C) << '\n';

#define VERIFY(...) if(not(__VA_ARGS__)) { VERIFY_PRINT(#__VA_ARGS__); }

template<typename T>
class ThreadSafeQueue {
    std::queue<T>               m_container;
    mutable std::mutex          m_mutex;
    std::condition_variable     m_condv;

    public:
    ThreadSafeQueue()  {}

    ThreadSafeQueue& operator=(const ThreadSafeQueue &)   = delete;
    ThreadSafeQueue(const ThreadSafeQueue & other) {
        std::lock_guard     l_lock(m_mutex);
        m_container = other.m_container;
    }

    void push(T val) {
        std::lock_guard     l_lock(m_mutex);
        m_container.push(std::move(val));
        m_condv.notify_one();
    }

    std::unique_ptr<T>  wait_and_pop() {
        std::unique_lock    lu_lock(m_mutex);
        m_condv.wait( lu_lock, [this](){return not m_container.empty(); });
        auto ret = std::make_unique<T>(std::move(m_container.front()));
        m_container.pop();
        return ret;
    }

    void wait_and_pop(T & res) {
        std::unique_lock    lu_lock(m_mutex);
        m_condv.wait(lu_lock, [this](){return not m_container.empty(); });
        res = std::move(m_container.front());
        m_container.pop();
    }

    std::unique_ptr<T> try_pop() {
        std::lock_guard     l_lock(m_mutex);
        if(m_container.empty()) {
            return std::unique_ptr<T>();
        }
        auto ret = std::make_unique<T>(std::move(m_container.front()));
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

ThreadSafeQueue<int> gqueue;

int reader(const std::size_t count, const bool pop_using_val)
{
    int result = 0;

    for (std::size_t i = 0; i < count; ++i)
    {
            if (pop_using_val)
            {
                const auto val = gqueue.try_pop();
                //std::cout << "Popped value " << *val << '\n';
                result += (*val);
            }
            else
            {
                int val = 0;
                gqueue.try_pop(val);
                //std::cout << "Popped value " << val << '\n';
                result += val;
            }
        
    }

    return result;
}

int writer(int count)
{
    int result = 0;

    for (int i = 0; i < count; ++i)
    {
        gqueue.push(i);

        result += i;
    }

    return result;
}

int main()
{
    constexpr int count = 100;
    int expected_result = 0;

    for (int i = 0; i < count; ++i)
    {
        expected_result += i;
    }
    std::cout << "Expected result is " << expected_result << '\n';

    constexpr int thread_count = 1;


    std::vector<std::future<int>> l_writer_results;
    for (int i = 0; i < thread_count; ++i)
    {
        l_writer_results.push_back(std::async(std::launch::async, writer, count / thread_count));
    }
    l_writer_results.push_back(std::async(std::launch::async, writer, count % thread_count));


    std::vector<std::future<int>> l_reader_results;
    for (int i = 0; i < thread_count; ++i)
    {
        l_reader_results.push_back(std::async(std::launch::async, reader, count / thread_count, true));
    }
    l_reader_results.push_back(std::async(std::launch::async, reader, count % thread_count, false));


    int writer_result = 0;
    for (auto &l_temp_result : l_writer_results)
    {
        writer_result += l_temp_result.get();
    }
    std::cout << "Result from writer is " << writer_result << '\n';

    int reader_result = 0;
    for (auto &l_temp_result : l_reader_results)
    {
        reader_result += l_temp_result.get();
    }

    std::cout << "Result from reader is " << reader_result << '\n';

    VERIFY(reader_result == writer_result);

    return 0;
}

/*****
    END OF FILE
**********/
