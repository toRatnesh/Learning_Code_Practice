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

    struct Node {
        std::shared_ptr<T>      m_data;
        std::unique_ptr<Node>   m_next;

    };

    std::unique_ptr<Node>   m_head;
    Node *                  m_tail;

    std::mutex              m_mutex_head;
    std::mutex              m_mutex_tail;
    std::condition_variable m_condv;

    Node * get_tail() {
        const std::lock_guard    l_tail_lock(m_mutex_tail);
        return m_tail;
    }

    std::unique_ptr<Node> pop_head() {
        auto l_head = std::move(m_head);
        m_head = std::move(l_head->m_next);
        return l_head;                
    }

    std::unique_ptr<Node> try_pop_head() {
        const std::lock_guard       l_head_lock(m_mutex_head);
        if(m_head.get() == get_tail()) {
            return std::unique_ptr<Node>();
        }
        return pop_head();
    }

    std::unique_ptr<Node> try_pop_head(T & val) {
        const std::lock_guard       l_head_lock(m_mutex_head);
        if(m_head.get() == get_tail()) {
            return std::unique_ptr<Node>();
        }
        val = std::move(*(m_head->m_data));
        return pop_head();
    }

    std::unique_lock<std::mutex> wait_for_data() {
        std::unique_lock        l_head_lock(m_mutex_head);
        m_condv.wait(l_head_lock, [&](){return m_head.get() != get_tail();});
        return std::move(l_head_lock);
    }

    std::unique_ptr<Node> wait_and_pop_head() {
        std::unique_lock        l_head_lock(wait_for_data());
        return pop_head();
    }

    std::unique_ptr<Node> wait_and_pop_head(T & val) {
        std::unique_lock        l_head_lock(wait_for_data());
        val = std::move(*(m_head->m_data));
        return pop_head();
    }

public:
    thsafe_queue() : m_head(std::make_unique<Node>()) , m_tail(m_head.get()) {}

    thsafe_queue(const thsafe_queue &)              = delete;
    thsafe_queue& operator=(const thsafe_queue &)   = delete;
    
    bool empty() {
        const std::lock_guard    l_head_lock(m_mutex_head);
        if (m_head.get() == get_tail()) {
            return true;
        }
        return false;
    }

    void push(T val) {
        auto l_data = std::make_shared<T>(std::move(val));
        auto l_node = std::make_unique<Node>();
        auto l_tail         = l_node.get();
        {
            const std::lock_guard      l_tail_lock(m_mutex_tail);
            m_tail -> m_data    = l_data;
            m_tail -> m_next    = std::move(l_node);
            m_tail              = l_tail;
        }
        m_condv.notify_one();
    }

    std::shared_ptr<T> try_pop() {
        /*
        const std::lock_guard       l_head_lock(m_mutex_head);
        if(m_head.get() == get_tail()) {
            std::shared_ptr<T>();
        }
        */

        /*
            auto l_head = std::move(m_head);
            m_head = std::move(l_head->next);
        */

        auto l_head = try_pop_head();
        return l_head ? (l_head->m_data) : std::shared_ptr<T>();
    }

    bool try_pop(T & val) {
        /*
        const std::lock_guard       l_head_lock(m_mutex_head);
        if(m_head.get() == get_tail()) {
            std::shared_ptr<T>();
        }
        */

        // auto l_head = std::move(m_head);
        // m_head = std::move(l_head->next);

        const auto l_head = try_pop_head(val);
        return l_head ? true : false;
    }

    std::shared_ptr<T> wait_and_pop() {
        /*
        const std::unique_lock        l_head_lock(m_mutex_head);
        m_condv.wait(l_head_lock, [&](){return m_head.get() != get_tail();});
        */

        // auto l_head = std::move(m_head);
        // m_head = std::move(l_head->next);

        auto l_head = wait_and_pop_head();
        return l_head->m_data;
    }

    void wait_and_pop(T & val) {
        /*
        const std::unique_lock        l_head_lock(m_mutex_head);
        m_condv.wait(l_head_lock, [&](){return m_head.get() != get_tail();});
        */

        // auto l_head = std::move(m_head);
        // m_head = std::move(l_head->next);

        auto l_head = wait_and_pop_head(val);
        return ;
    }

};


thsafe_queue<std::string> gqueue;
std::osyncstream syn_cout(std::cout);

void read_try_pop_using_ref(std::size_t count) {
    std::string res;
    for (std::size_t i = 0; i < count; ++i) {
        bool ret = gqueue.try_pop(res);
        if (ret) {
            syn_cout << "try_pop(&), Popped value is " << res << '\n';
        } else {
            syn_cout << "Queue is empty\n";
        }
    }
}

void read_try_pop(std::size_t count) {
    for (std::size_t i = 0; i < count; ++i) {
        const auto res = gqueue.try_pop();
        if (res) {
            syn_cout << "try_pop(), Popped value is " << *res << '\n';
        } else {
            syn_cout << "Queue is empty\n";
        }
    }
}

void read_wait_pop_using_ref(std::size_t count) {
    std::string res;
    for (std::size_t i = 0; i < count; ++i) {
        if (not gqueue.empty()) {
            gqueue.wait_and_pop(res);
            syn_cout << "wait_and_pop(&), Popped value is " << res << '\n';
        } else {
            syn_cout << "Queue is empty\n";
        }
    }
}

void read_wait_pop(std::size_t count) {
    for (std::size_t i = 0; i < count; ++i) {
        const auto res = gqueue.wait_and_pop();
        if (res) {
            syn_cout << "wait_and_pop(), Popped value is " << *res << '\n';
        } else {
            syn_cout << "Queue is empty\n";
        }
    }
}

void writer(std::size_t count) {
    for (std::size_t i = 0; i < count; ++i) {
        gqueue.push(std::string("string-") + std::to_string(i));
    }
}

int main() {

    std::size_t count = 20;

    std::vector<std::thread> vecth;

    vecth.push_back(std::thread(writer, count));
    
    vecth.push_back(std::thread(read_wait_pop_using_ref, count / 4));
    vecth.push_back(std::thread(read_wait_pop, count / 4));

    vecth.push_back(std::thread(read_try_pop_using_ref, count / 4));
    vecth.push_back(std::thread(read_try_pop, count / 4));


    for(auto & th : vecth) {
        th.join();
    }

    return 0;
}

/*****
    END OF FILE
**********/


