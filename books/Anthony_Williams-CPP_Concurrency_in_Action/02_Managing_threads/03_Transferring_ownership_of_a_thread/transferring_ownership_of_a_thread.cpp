/*******

References
    Anthony Williams - C++ Concurrency in Action

2 Managing threads

    The C++ Standard Library makes most thread-management tasks relatively easy, 
    with almost everything managed through the std::thread object associated with a given thread.

2.3 Transferring ownership of a thread

    std::thread own a resource: each instance is responsible for managing a thread of execution
    Instances of std::thread are movable, even though they aren’t copyable
    This ensures that only one object is associated with a particular thread of execution at any one time while allowing programmers the option of transferring that ownership between objects.

    The move support in std::thread means that ownership can readily be transferred out of a function
    Likewise, if ownership should be transferred into a function, it can accept an instance of std::thread by value as one of the parameters

    The move support in std::thread also allows for containers of std::thread objects, if those containers are move-aware

    One benefit of the move support of std::thread is that you can build on the thread_guard class from listing 2.1.3 (Waiting in exceptional circumstances) and have it take ownership of the thread
    it also means that no one else can join or detach the thread once ownership has been transferred into the object

***********/

#include <iostream>
#include <thread>
#include <string>
#include <stdexcept>
#include <memory>
#include <vector>

void thread_routine_01() {
    for(size_t i = 0; i < 3; ++i) {
        std::cout << "Inside " << __func__ << '\n';
    }
    return;
}

void thread_routine_02() {
    for(size_t i = 0; i < 3; ++i) {
        std::cout << "Inside " << __func__ << '\n';
    }
    return;
}

std::thread getThread_01() {
    std::thread thr(thread_routine_01);
    return thr;
}

std::thread getThread_02() {
    return std::thread(thread_routine_02);
}

void useThread(std::thread thr) {
    if(thr.joinable()) { thr.join(); }
    return ;
}

// using move to implement improved version of thread guard from example 2.1.3 Waiting in exceptional circumstances
// this is a poor version of C++20 std::jthread
class thread_guard {
	std::thread m_thr;
	
	public:
	explicit thread_guard(std::thread thr)
		: m_thr(std::move(thr)) {
            if(not m_thr.joinable()) {
                throw std::logic_error("Non joinable thread");
            }
        }

	~thread_guard() {
		if(m_thr.joinable()) {
			m_thr.join();
		}
	}
	
	thread_guard(thread_guard const&)	= delete;
	thread_guard& operator=(thread_guard const&)	= delete;
};

int main() {
    std::cout << "=== Transfering ownership of thread ===\n";
    {
        std::thread thr1(thread_routine_01);
        std::thread thr2(thread_routine_02);
        
        
        std::thread thr3 = std::move(thr1);
        thr1 = std::move(thr2);

        // thr1 already had an associated thread (which was running thread_routine_02), 
        // so std::terminate() is called to terminate the program
        //thr1 = std::move(thr3);
        
        if(thr1.joinable()) thr1.join();
        if(thr2.joinable()) thr2.join();
        if(thr3.joinable()) thr3.join();
    }

    std::cout << "\n=== Getting/Passing thread from/to funciton ===\n";   
    {
        useThread(getThread_01());
        useThread(getThread_02());
        std::cout << '\n';
        {
            std::thread thr(getThread_01());
            if(thr.joinable()) thr.join();
        }
        {
            std::thread thr(getThread_02());
            if(thr.joinable()) thr.join();
        } 
        std::cout << '\n';       
        {
            std::thread thr(thread_routine_01);
            useThread(std::move(thr));
        }
        {
            useThread(std::thread(thread_routine_02));
        }        
        std::cout << '\n';

    }

    {
        // Using a thread gauard
        std::thread thr(thread_routine_01); 
        try {
            throw std::runtime_error("Causing an exception");
        } catch (...) {

        }
        
        thread_guard thg(std::move(thr));
    } 

    std::cout << "\n=== containers of std::thread ===\n";
    {
        std::vector<std::thread> vec_thread;
        std::thread thr(thread_routine_01);
        vec_thread.push_back(std::move(thr));
        vec_thread.emplace_back(thread_routine_02);
        vec_thread.emplace_back(getThread_01());
        vec_thread.emplace_back([](std::string msg){std::cout << "Inside Lambda: " << msg << '\n'; }, "emplace_back lambda as thread routine");

        for(auto & thr_elem : vec_thread) {
            thr_elem.join();
        }
    }

    return 0;
}

/*******
	END OF FILE
***********/


