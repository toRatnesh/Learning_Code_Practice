/*****

References
    Anthony Williams - C++ Concurrency in Action

3.2 Protecting shared data with mutexes
    mutex (mutual exclusion)
        You could mark all the pieces of code that access the data structure as mutually exclusive, so that if any thread was running one of them, any other thread that tried to access that data structure had to wait until the first thread was finished
        Mutexes also has issue of deadlock and protecting either too much or too little data

3.2.5 Further guidelines for avoiding deadlock
	Deadlock doesn’t only occur with locks
	you can create deadlock with two (or more) threads and no locks by having each thread call join() on the std::thread object for the other
	In this case, neither thread can make progress because it’s waiting for the other to finish
	
	avoiding deadlock: don’t wait for another thread if there’s a chance it’s waiting for you
	
	Guidelines to avoid deadlock
	
	AVOID NESTED LOCKS
	Its simple don’t acquire a lock if you already hold one. 
	You could still get deadlock from other things (like the threads waiting for each other)
	If you need to acquire multiple locks, do it as a single action with std::lock (or since C++17 std::scoped_lock ) in order to acquire them without deadlock.
	
	AVOID CALLING USER-SUPPLIED CODE WHILE HOLDING A LOCK
	Because we don’t know what the user supplied code does.
	If you call user-supplied code while holding a lock, and that code acquires a lock, you’ve violated the guideline on avoiding nested locks and could get deadlock.
	
	ACQUIRE LOCKS IN A FIXED ORDER
	If you absolutely must acquire two or more locks, and you can’t acquire them as a single operation with std::lock, the next best thing is to acquire them in the same order in every thread.
	
	USE A LOCK HIERARCHY
	Although this is a particular case of defining lock ordering, a lock hierarchy can provide a means of checking that the convention is adhered to at runtime.
	The idea is that you divide your application into layers and identify all the mutexes that may be locked in any given layer. 
	When code tries to lock a mutex, it isn’t permitted to lock that mutex if it already holds a lock from a lower layer.
	
	C++ Standard Library does not provide direct support for it, so if you need write a custom hierarchical_mutex mutex type.
	
	Deadlocks between hierarchical mutexes are impossible, because the mutexes themselves enforce the lock ordering. 
	This does mean that you can’t hold two locks at the same time if they’re the same level in the hierarchy, so hand-over-hand locking schemes require that each mutex in the chain has a lower hierarchy value than the prior one, which may be impractical in some cases.
	
	User defined hierarchical_mutex can be used with std::lock_guard<> because it implements the three member functions required to satisfy the mutex concept: lock(), unlock(), and try_lock().
	
	EXTENDING THESE GUIDELINES BEYOND LOCKS
	Deadlock doesn’t only occur with locks; it can occur with any synchronization construct that can lead to a wait cycle
	ensure that your threads are joined in the same function that started them
	
**********/

#include <iostream>
#include <mutex>
#include <thread>
#include <exception>
#include <climits>

class HierarchicalMutex {

    std::mutex      m_mutex;
    static thread_local unsigned long this_thread_hier_value;

    const unsigned long hier_value;
          unsigned long prev_hier_value;

    void check_for_hier_voilation() {
        if(this_thread_hier_value <= hier_value) {
            throw std::logic_error("Mutex hierarchy voilated");
        }
    }

    void update_hier_value() {
        prev_hier_value = this_thread_hier_value;
        this_thread_hier_value = hier_value;
    }

    public:
    explicit HierarchicalMutex(unsigned long value) : 
        hier_value(value), prev_hier_value(0) { }

    void lock() {
        check_for_hier_voilation();
        m_mutex.lock();
        update_hier_value();
    }
    bool try_lock() {
        check_for_hier_voilation();
        if(! m_mutex.try_lock()) {
            return false;
        }
        update_hier_value();
        return true;
    }
    void unlock() {
        if(this_thread_hier_value != hier_value) {
            throw std::logic_error("Mutex hierarchy voilated during unlock");
        }
        this_thread_hier_value = prev_hier_value;
        m_mutex.unlock();
    }
};
thread_local unsigned long HierarchicalMutex::this_thread_hier_value = ULONG_MAX;


HierarchicalMutex high_level_mutex(100);
HierarchicalMutex low_level_mutex(10);
HierarchicalMutex display_level_mutex(1);

std::string shared_str;

void display() {
    std::lock_guard guard(display_level_mutex);
    std::cout << shared_str << '\n';
}

void high_level_fun();

void low_level_fun() {
    std::lock_guard guard(low_level_mutex);
    shared_str = "Inside low level";
    
    // high_level_fun holds a mutex with hihg hierarchy than low_level_mutex, so calling it from high_level_fun has no issue
    //high_level_fun();

    // display holds a mutex with low hierarchy than low_level_mutex, so calling it from high_level_fun has no issue
    display();
}

void high_level_fun() {
    std::lock_guard guard(high_level_mutex);
    shared_str = "Inside high level";

    // display holds a mutex with low hierarchy than high_level_mutex, so calling it from high_level_fun has no issue
    display();

    // low_level_fun holds a mutex with low hierarchy than high_level_mutex, so calling it from high_level_fun has no issue
    low_level_fun();

    // display holds a mutex with low hierarchy than high_level_mutex, so calling it from high_level_fun has no issue
    display();
}

int main() {

    std::thread low_th(low_level_fun);
    std::thread high_th(high_level_fun);

    if(low_th.joinable())   low_th.join();
    if(high_th.joinable())  high_th.join();

    return 0;
}

/*****
    END OF FILE
**********/


