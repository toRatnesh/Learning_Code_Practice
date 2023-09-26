/*****

References
    Anthony Williams - C++ Concurrency in Action

4. Synchronizing concurrent operations

	Sometimes we need to synchronize actions on separate threads. 
	One thread might need to wait for another thread to complete a task before the first thread can complete its own.

	C++ Standard Library techniques to handle synchronization

		Condition variables
		Futures
		Latches				(since C++20)
		Barriers			(since C++20)

4.1 Waiting for an event or other condition

	If one thread is waiting for a second thread to complete a task, it has several options
	
	1. keep checking a flag in shared data (protected by a mutex)
	2. the waiting thread sleep for short periods between the checks using the std::this_thread::sleep_for()
	3. condition variable (preferred)

4.1.2 Building a thread-safe queue with condition variables
    Check example
        One version of deque wait for data to be available

**********/

#include <iostream>
#include <thread>
#include <condition_variable>
#include <mutex>
#include <queue>
#include <chrono>

template<typename T>
class threadsafe_queue {

    std::queue<T>           m_queue;
    mutable std::mutex      m_queue_mutex;  // mutable to use inside const function
    std::condition_variable m_queue_conv;

    public:
    threadsafe_queue() {}
    threadsafe_queue(const threadsafe_queue & other) {
        const std::lock_guard     lock_g(m_queue_mutex);
        m_queue = other.m_queue;
    }

    bool is_empty( ) const {
        const std::lock_guard     lock_g(m_queue_mutex);
        return m_queue.empty();
    }

    void enque(T val) {
        const std::lock_guard     lock_g(m_queue_mutex);
        m_queue.push(val);
        m_queue_conv.notify_one();
    }

    bool try_deque(T & val) {
        bool ret = false;
        const std::lock_guard     lock_g(m_queue_mutex);
        if(m_queue.empty()) {
            ret = false;
        } else {
            val = m_queue.front();
            m_queue.pop();
            ret = true;
        }
        return ret;
    }

    std::shared_ptr<T> try_deque() {
        std::shared_ptr<T> ret{nullptr};
        const std::lock_guard     lock_g(m_queue_mutex);
        if(m_queue.empty()) {
            ret = std::make_shared<T>();
        } else {
            ret = std::make_shared<T>(m_queue.front());
            m_queue.pop();
        }
        return ret;
    }

    bool wait_and_deque(T & val) {
        std::unique_lock        ulock(m_queue_mutex);
        m_queue_conv.wait(ulock, [this]{return not m_queue.empty();});
        val = m_queue.front();
        m_queue.pop();
        return true;
    }

    std::shared_ptr<T> wait_and_deque() {
        std::unique_lock        ulock(m_queue_mutex);
        m_queue_conv.wait(ulock, [this]{return not m_queue.empty();});
        std::shared_ptr<T>  ret = std::make_shared<T>(m_queue.front());
        m_queue.pop();
        return ret;
    }

};

threadsafe_queue<int>    g_ts_queue;

void writer(int no_elems) {
    int i = 0;
    while(i++ < no_elems) {
        std::cout << "Inside writer " << i << '\n';
        g_ts_queue.enque(i);
        std::this_thread::sleep_for(std::chrono::nanoseconds(100));
    }
}

void reader(int no_elems, bool wait) {
    int i = 0;
    while(i++ < no_elems) {
        std::shared_ptr<int>    val{nullptr};
        if(wait) {
            val = g_ts_queue.wait_and_deque();
            std::cout << "After wait inside reader, value is " << *val << '\n';
        } else {
            if(g_ts_queue.is_empty()) {
                // do nothing
            } else {
                val = g_ts_queue.try_deque();
                std::cout << "Inside reader, value is " << *val << '\n';
            }
            
        }
        
    }
}

int main() {
    int no_elems = 10;

    std::thread wrt(writer, no_elems);
    wrt.detach();

    std::thread rdt(reader, no_elems/2, false);
    rdt.detach();

    std::thread rdt_wait(reader, no_elems/2, true);
    rdt_wait.detach();

    std::this_thread::sleep_for(std::chrono::seconds(5));

    return 0;
}

/*****
    END OF FILE
**********/


