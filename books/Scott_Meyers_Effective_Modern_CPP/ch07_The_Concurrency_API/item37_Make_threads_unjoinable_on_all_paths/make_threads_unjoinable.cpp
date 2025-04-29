/*****

References

    Effective Modern C++ | Scott Meyers
    https://en.cppreference.com/w/cpp/thread/thread
    https://en.cppreference.com/w/cpp/thread/async

Item 37: Make std::threads unjoinable on all paths

std::thread object is in one of two states:
    1.	joinable
    2.	unjoinable

joinable std::thread
	an underlying asynchronous thread of execution that is or could be running
	an underlying thread that’s blocked or waiting to be scheduled is joinable
	std::thread objects corresponding to underlying threads that have run to completion

unjoinable std::thread
	a std::thread that’s not joinable
	• Default-constructed std::threads
	• std::thread objects that have been moved from
	• std::threads that have been joined
	• std::threads that have been detached

if the destructor for a joinable thread is invoked, execution of the program is terminated

why the std::thread destructor behaves this way?
It’s because the two other obvious options are arguably worse.
1.	An implicit join:
	In this case, a std::thread’s destructor would wait for its underlying asynchronous thread of execution to complete. 
	That sounds reasonable, but it could lead to performance anomalies that would be difficult to track down.
2.	An implicit detach:
	In this case, a std::thread’s destructor would sever the connection between 
	the std::thread object and its underlying thread of execution.
	The underlying thread would continue to run.
	This sounds no less reasonable than the join approach, but the debugging problems it can lead to are worse.

The Standardization Committee decided that the consequences of destroying a joinable thread were sufficiently dire 
that they essentially banned it (by specifying that destruction of a joinable thread causes program termination).	

Custom RAII class to make thread unjoinable
	we can wtite custom Resource Acquisition Is Initialization(RAII) class and make thread unjoinable in its destructor
	check exmaple code below

	•	The constructor accepts only std::thread rvalues (std::thread objects aren’t copyable)
	•	because std::thread objects may start running a function immediately after they are initialized, 
		it’s a good habit to declare them last in a class
		That guarantees that at the time they are constructed, 
		all the data members that precede them have already been initialized
	•	ThreadRAII offers a get function to provide access to the underlying
		Providing get avoids the need for ThreadRAII to replicate the full std::thread interfacestd::thread object
	•	Before the ThreadRAII destructor invokes a member function on the std::thread object t, 
		it checks to make sure that t is joinable.
		This is necessary, because invoking join or detach on an unjoinable thread yields undefined behavior.

Summary
	• Make std::threads unjoinable on all paths.
	• join-on-destruction can lead to difficult-to-debug performance anomalies.
	• detach-on-destruction can lead to difficult-to-debug undefined behavior.
	• Declare std::thread objects last in lists of data members.

**********/

#include <iostream>
#include <thread>
#include <string>
#include <vector>

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

        jthread(std::thread && thr, const bool join_flag) 
        : m_join_flag{join_flag}, m_thrd{std::move(thr)} {  }

        jthread(jthread&&   )               = default;
        jthread& operator=(jthread&&   )    = default;

        std::thread & get() { return m_thrd; }
    };
};


void doAsyncWork(const std::string str) {
    std::cout << "Inside " << __func__ 
    << ", thread id " << std::this_thread::get_id() 
    << ", " << str << '\n';
}

void create_safe_raii_thread(const bool to_join) {
    std::cout << "Inside " << __func__ << ", thread id " << std::this_thread::get_id() << '\n';
    nonstd::jthread  thr(std::thread(doAsyncWork, "Creating a unjoinable thread"), to_join);
}

void create_safe_thread(const bool to_join) {
    std::cout << "Inside " << __func__ << ", thread id " << std::this_thread::get_id() << '\n';
    std::thread  thr(doAsyncWork, "Creating a unjoinable thread");
    if(thr.joinable()) {
        if(to_join) {
            thr.join();
        } else {
            thr.detach();
        }
    }
}

void create_unsafe_thread() {
    std::cout << "Inside " << __func__ << ", thread id " << std::this_thread::get_id() << '\n';
    std::thread  thr(doAsyncWork, "Creating a joinable thread");
}

int main() {

    //create_unsafe_thread();

    create_safe_thread(true);
    create_safe_thread(false);

    create_safe_raii_thread(true);
    create_safe_raii_thread(false);

    return 0;
}

/*****
    END OF FILE
**********/

