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

6.2.3 A thread-safe queue using fine-grained locks and condition variables

    The lock on m_mutex_tail in get_tail() solves data race. 
    Because the call to get_tail() locks the same mutex as the call to push(), there’s a defined order between the two calls. 
    Either the call to get_tail() occurs before the call to push(), in which case it sees the old value of tail, or 
    it occurs after the call to push(), in which case it sees the new value of tail and the new data attached to the previous value of tail.

    This data structure has considerably more scope for concurrency than that from listing 6.2, 
    because the locks are more fine-grained and more is done outside the locks.

    For example, in
    push(), the new node and new data item are allocated with no locks held. 
    This means that multiple threads can be allocating new nodes and data items concurrently without a problem.
    Only one thread can add its new node to the list at a time, but the code to do so is only 
    a few simple pointer assignments, so the lock isn’t held for much time.

    Also, try_pop()holds the tail_mutex for only a short time, to protect a read from tail. 
    Consequently, almost the entirety of a call to try_pop() can occur concurrently with a call to push().

    Also, the operations performed while holding the head_mutex are quite minimal; 
    the expensive delete (in the destructor of the node pointer) is outside the lock. 
    This will increase the number of calls to try_pop() that can happen concurrently; 
    only one thread can call pop_head() at a time, but multiple threads can then delete their old nodes and return the data safely.

    wait_and_pop() is more complicated, because you have to decide where to wait,
    If you make the predicate head!=get_tail(), you only need to hold head_mutex, 
    so you can use your lock on that for the call to data_cond.wait(). 
    Once you’ve added the wait logic, the implementation is the same as try_pop().

**********/

#include <iostream>
#include <mutex>
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
    struct  Node
    {
        std::unique_ptr<T>      m_data;
        std::unique_ptr<Node>   m_next;
    };

    std::unique_ptr<Node>       m_head;
    Node *                      m_tail;

    std::mutex                  m_head_mutex;
    std::mutex                  m_tail_mutex;
    std::condition_variable     m_data_cond;
    
    Node * getTail() {
        const std::lock_guard l_tail_lock{m_tail_mutex};
        return m_tail;
    }

    std::unique_ptr<Node> popHead() {
        std::unique_ptr<Node> l_old_head = std::move(m_head);
        m_head = std::move(l_old_head->m_next);
        
        return l_old_head;
    }

    std::unique_ptr<Node> tryPopHead() {
        const std::lock_guard l_head_lock{m_head_mutex};
        if(m_head.get() == getTail()) {
            return std::unique_ptr<Node>();
        }

        return popHead();
    }

    std::unique_ptr<Node> tryPopHead(T & value) {
        const std::lock_guard l_head_lock{m_head_mutex};
        if(m_head.get() == getTail()) {
            return std::unique_ptr<Node>();
        }
        
        value = std::move(*(m_head->m_data));

        return popHead();
    }    

    std::unique_lock<std::mutex> wait_for_data() {
        std::unique_lock l_head_lock{m_head_mutex};
        m_data_cond.wait(l_head_lock, [&](){ m_head.get() != getTail(); });

        return std::move(l_head_lock);
    }

    std::unique_ptr<Node> wait_and_pop_head() {
        std::unique_lock l_head_lock{wait_for_data()};
        return popHead();
    }

    std::unique_ptr<Node> wait_and_pop_head(T & value) {
        std::unique_lock l_head_lock{wait_for_data()};
        value = std::move(*(m_head->m_data));
        return popHead();
    }    


    public:

    ThreadSafeQueue() : m_head{std::make_unique<Node>()}, m_tail{m_head.get()} {

    }

    ThreadSafeQueue(const ThreadSafeQueue &)    = delete;
    ThreadSafeQueue & operator=(const ThreadSafeQueue &)    = delete;

    void push(T val) {
        std::unique_ptr<T>      l_data          = std::make_unique<T>(std::move(val));
        std::unique_ptr<Node>   l_dummy_node    = std::make_unique<Node>();
                        Node *  l_new_tail      = l_dummy_node.get();

        {
            const std::lock_guard l_tail_lock{m_tail_mutex};
            m_tail->m_data = std::move(l_data);
            m_tail->m_next = std::move(l_dummy_node);
            m_tail = l_new_tail;
        }
        m_data_cond.notify_one();

        return ;
    }

    std::unique_ptr<T> try_pop() {
        std::unique_ptr<Node> l_old_head{tryPopHead()};
        return l_old_head ? std::move(l_old_head->m_data) : std::unique_ptr<T>();
    }

    bool try_pop(T & value) {

        /* FOLLWING IS WRONG CODE BECAUSE IN CASE OF EXCEPTION THROWN IN COPY ASSIGNEMENT QUEUE HAS BEEN MODIFIED
        std::unique_ptr<Node> l_old_head{popHead()};
        value = std::move(*(l_old_head->m_data));
        return l_old_head;
        */

        std::unique_ptr<Node> l_old_head{tryPopHead(value)};
        return l_old_head;
    }

    bool empty() {
        const std::lock_guard l_head_lock{m_head_mutex};
        return (m_head.get() == getTail());
    }


    std::unique_ptr<T> wait_and_pop() {
        /*
        {
            std::unique_lock l_head_lock{wait_for_data()};
            std::unique_ptr<Node> l_old_head = popHead();
        }
        */

        const std::unique_ptr<Node> l_old_head = wait_and_pop_head();
        return l_old_head->m_data;
    }

    void wait_and_pop(T & value) {
        /*
        {
            std::unique_lock l_head_lock{wait_for_data};
            value = std::move(*(m_head->m_data));
            popHead();
        }
        */
        const std::unique_ptr<Node> l_old_head = wait_and_pop_head(value);
        return ;
    }    

    /*  WITHOUT REFACTORING

    std::unique_ptr<T> pop() {
        std::unique_ptr<Node> l_old_head{nullptr};
        {
            const std::lock_guard l_head_lock{m_head_mutex};
            {
                const std::lock_guard l_tail_lock{m_tail_mutex};
                if(m_head.get() == m_tail) {
                    return std::unique_ptr<T>();
                }
            }
            
            l_old_head = std::move(m_head);
            m_head = std::move(l_old_head->m_next);
        }
        return std::move(l_old_head->m_data);
    }
    

    bool empty() {
        const std::lock_guard l_head_lock{m_head_mutex};
        const std::lock_guard l_tail_lock{m_tail_mutex};
        return (m_head.get() == m_tail);
    }    
    */

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
            /*
            else
            {
                int val = 0;
                gqueue.pop(val);
                //std::cout << "Popped value " << val << '\n';
                result += val;
            }
            */
        
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

