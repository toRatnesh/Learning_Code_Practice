/*****

References

    Effective Modern C++ | Scott Meyers
    https://en.cppreference.com/w/cpp/thread/thread
    https://en.cppreference.com/w/cpp/thread/async
	https://en.cppreference.com/w/cpp/thread/condition_variable
	https://en.cppreference.com/w/cpp/thread/future
	https://en.cppreference.com/w/cpp/thread/promise

Item 39: Consider void futures for one-shot event communication

if a task wants to tell a second, asynchronously running task that a particular event has occurred
what’s the best way for this kind of inter-thread communication to take place?

1.	condition variable
2.	atomic flag
3.	condition variable with flag
4.	future

the condvar- and flag-based designs, both can be used to communicate multiple times

1.	condition variable

	detecting task:		the task that detects the condition
	reacting task:		the task reacting to the condition

	std::condition_variable cv;		// condvar for event
	std::mutex m;					// mutex for use with cv

	detecting task
	{
		...					// detect event
		cv.notify_one();	// tell reacting task
		...
	}

	reacting task
	{
		...
		std::unique_lock<std::mutex> lk(m);		// lock mutex
		cv.wait(lk);							// wait for notify (incorrect)
		...					// react event
	}
	
	a task in a wait call is truly blocked
	
	Problem in this code
	•	If the detecting task notifies the condvar before the reacting task waits, the reacting task will hang
	•	The wait statement fails to account for spurious wakeups

2.	atomic flag
	
	std::atomic<bool> flag(false);
	
	detecting task
	{
		...					// detect event
		flag = true;		// set flag, tell reacting task
		...
	}

	reacting task
	{
		...
		while (!flag);		// check flag, wait for event
		...					// react event
	}	

	Drawback: cost of polling
	

3.	condition variable with flag

	std::condition_variable cv;		// condvar for event
	std::mutex m;					// mutex for use with cv
	bool flag(false);				// not std::atomic
	
	detecting task
	{
		...										// detect event
		{
			std::lock_guard<std::mutex> g(m);	// lock mutex
			flag = true;						// set flag
		}
		cv.notify_one();						// tell reacting task
		...
	}

	reacting task
	{
		...
		std::unique_lock<std::mutex> lk(m);		// lock mutex
		cv.wait(lk, [] { return flag; });		// use lambda to avoid spurious wakeups
		...										// react event
	}
	
	This approach works, but it doesn’t seem terribly clean.
	
	
4.	future

	the reacting task wait on a future that’s set by the detecting task
	detecting task has a std::promise object (i.e., the writing end of the communications channel)
	reacting task has a corresponding future
	
	std::promise<void> p;
	
	detecting task
	{
		...					// detect event
		p.set_value();		// tell reacting task
		...
	}

	reacting task
	{
		...
		p.get_future().wait();	// wait on future corresponding to p
		...						// react event
	}
	
	Advantage:
	. requires no mutex
	. immune to spurious wakeups
	. reacting task is truly blocked after making the wait call
	. works regardless of whether the detecting task sets its std::promise before the reacting task waits
		
	Drawback:
	. between a std::promise and a future is a typically dynamically allocated shared state,
	  so this design incurs the cost of heap-based allocation and deallocation
	. a std::promise may be set only once, it can’t be used repeatedly

thread in a suspended state
	C++ concurrency API offers no way to do those things
	lower-level API often makes it possible to configure thread characteristics such as priority and affinity
	
	Assuming you want to suspend a thread only once
	a design using a void future is a reasonable choice
	
	see example code below
	
	Issue:
	If an exception is emitted, before calling set_value() on p
	the call to wait will never return
	
	There are ways to address this problem, which is not explained here
	
multiple thread in a suspended state
	we can use shared_futures instead of a future in the react code
	each reacting thread needs its own copy of the shared_future that refers to the shared state
	
Summary
	•	For simple event communication, condvar-based designs require a superfluous mutex, 
		impose constraints on the relative progress of detecting and reacting tasks, 
		and require reacting tasks to verify that the event has taken place.
	•	Designs employing a flag avoid those problems, but are based on polling, not blocking.
	•	A condvar and flag can be used together, but the resulting communications mechanism is somewhat stilted.
	•	Using std::promises and futures dodges these issues, but the approach uses heap memory for shared states, 
		and it’s limited to one-shot communication.

**********/

#include <iostream>
#include <thread>
#include <string>
#include <future>
#include <condition_variable>
#include <mutex>
#include <vector>
#include <exception>

namespace nonstd {
    class jthread {
        bool            m_join_flag;
        std::thread     m_thrd;

        public:
        ~jthread() {
            if(m_thrd.joinable()) {
                if(m_join_flag) {
                    m_thrd.join();
                } else {
                    m_thrd.detach();
                }
            }
        }

        jthread(std::thread && thr, const bool join_flag = true) 
        : m_join_flag{join_flag}, m_thrd{std::move(thr)} {  }

        jthread(jthread&&   )               = default;
        jthread& operator=(jthread&&   )    = default;

        std::thread & get() { return m_thrd; }
    };
}

std::condition_variable     cond_var;
std::mutex                  cond_var_mutex;

std::atomic_bool            atomic_flag;

std::condition_variable     cond_var_flag;
std::mutex                  cond_var_flag_mutex;
bool                        ready_flag{false};

std::promise<void>          prom_val;     

void consumer_using_cond_var() {
    std::unique_lock<std::mutex>    l_lock(cond_var_mutex);
    cond_var.wait(l_lock);
    std::cout << "Inside " << __func__ << ", thread id: " << std::this_thread::get_id() << '\n';
}

void producer_using_cond_var() {
    {
        std::lock_guard<std::mutex>    l_lock(cond_var_mutex);
        std::cout << "Inside " << __func__ << ", thread id: " << std::this_thread::get_id() << '\n';
    }
    cond_var.notify_one();
}


void consumer_using_atomic_flag() {
    while(not atomic_flag) { };
    std::cout << "Inside " << __func__ << ", thread id: " << std::this_thread::get_id() << '\n';
}

void producer_using_atomic_flag() {
    std::cout << "Inside " << __func__ << ", thread id: " << std::this_thread::get_id() << '\n';
    atomic_flag = true;
}


void consumer_using_cond_var_flag() {
    std::unique_lock<std::mutex>    l_lock(cond_var_flag_mutex);
    cond_var_flag.wait(l_lock, []{ return ready_flag; });
    std::cout << "Inside " << __func__ << ", thread id: " << std::this_thread::get_id() << '\n';
}

void consumer_using_future() {
    prom_val.get_future().wait();
    std::cout << "Inside " << __func__ << ", thread id: " << std::this_thread::get_id() << '\n';
}

void producer_using_promise() {
    std::cout << "Inside " << __func__ << ", thread id: " << std::this_thread::get_id() << '\n';
    prom_val.set_value();
}


void producer_using_cond_var_flag() {
    {
        std::lock_guard<std::mutex>    l_lock(cond_var_flag_mutex);
        std::cout << "Inside " << __func__ << ", thread id: " << std::this_thread::get_id() << '\n';
        ready_flag = true;
    }
    cond_var_flag.notify_one();
}

int main() {
    
    {   std::cout << "=== producer consumer using condition variable ===\n";
        nonstd::jthread thr1(std::thread{consumer_using_cond_var});
        nonstd::jthread thr2(std::thread{producer_using_cond_var});
        
        // producer task notifies the condvar before the consumer task waits, the consumer task will hang
        //nonstd::jthread thr1(std::thread{consumer_using_cond_var});
    }
    
    {   std::cout << "\n=== producer consumer using atomic flag ===\n";
        nonstd::jthread thr1(std::thread{producer_using_atomic_flag});
        nonstd::jthread thr2(std::thread{consumer_using_atomic_flag});
    }

    {   std::cout << "\n=== producer consumer using condition variable with flag ===\n";
        nonstd::jthread thr1(std::thread{producer_using_cond_var_flag});
        nonstd::jthread thr2(std::thread{consumer_using_cond_var_flag});
    }
    
    {   std::cout << "\n=== producer using promise and consumer using future related to promise ===\n";
        nonstd::jthread thr1(std::thread{producer_using_promise});
        nonstd::jthread thr2(std::thread{consumer_using_future});
    }    

    {   std::cout << "\n=== thread in suspended state ===\n";
        std::promise<std::string>   prom_v;

        std::thread     cons_thr(
            [fut = prom_v.get_future()](){
                fut.wait();     // suspended until future is set
                std::cout << "Inside " << __func__ << ", thread id: " << std::this_thread::get_id() << '\n';
            }
        );

        std::cout << "Inside " << __func__ << ", thread id: " << std::this_thread::get_id() << '\n';
        prom_v.set_value("set promise value to execute suspended thread");

        cons_thr.join();
    }

    {   std::cout << "\n=== multiple thread in suspended state ===\n";
        std::promise<std::string>   prom_v;
        auto shared_fut             = prom_v.get_future().share();

        std::vector<nonstd::jthread>    vec_thr;

        for(std::size_t i = 0; i< 5; ++i) {
            vec_thr.emplace_back( std::thread(
                [shared_fut](){
                    shared_fut.wait();     // suspended until future is set
                    std::cout << "Inside " << __func__ << ", thread id: " << std::this_thread::get_id() << '\n';
                }
            ));
        }

        std::cout << "Inside " << __func__ << ", thread id: " << std::this_thread::get_id() << '\n';
        prom_v.set_value("set promise value to execute suspended thread");
    }


    {   std::cout << "\n=== thread in suspended state with promise not set ===\n";
        std::promise<std::string>   prom_v;
        
        std::thread     cons_thr(
            [fut = prom_v.get_future()](){
                fut.wait();     // suspended until future is set
                std::cout << "Inside " << __func__ << ", thread id: " << std::this_thread::get_id() << '\n';
            }
        );

        nonstd::jthread     jthr(std::move(cons_thr));

        try {
            //throw std::runtime_error("Throwing exception before setting promise will lead to suspended thread waiting forever");
            std::cout << "Inside " << __func__ << ", thread id: " << std::this_thread::get_id() << '\n';
            prom_v.set_value("set promise value to execute suspended thread");
        } catch( const std::exception & exp) {
            std::cout << "Exception: " << exp.what() << '\n';
        } catch(...) {
            std::cout << "Unknown Exception\n";
        }

        //cons_thr.join();
    }

    return 0;
}

/*****
    END OF FILE
**********/

