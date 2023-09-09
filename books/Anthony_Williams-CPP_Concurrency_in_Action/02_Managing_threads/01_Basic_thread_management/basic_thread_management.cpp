/*******

References
    Anthony Williams - C++ Concurrency in Action

2 Managing threads

    The C++ Standard Library makes most thread-management tasks relatively easy, 
    with almost everything managed through the std::thread object associated with a given thread.

2.1 Basic thread management

2.1.1 Launching a thread

    Threads are started by constructing a std::thread object that specifies the task to run on that thread

    C++ Standard Library, std::thread works with any callable type, so you can pass 
    an instance of a class with a function call operator to the std::thread constructor

    Avoid "C++’s most vexing parse"
    When constructing a std::thread object If you pass a temporary rather than a named variable, 
    the syntax can be the same as that of a function declaration, in which case the compiler interprets it as such, rather than an object definition.
    
    To avoid this, use an extra set of parentheses with name of function object, or use uniform initialization syntax

    After starting a thread, you need to explicitly decide whether to wait for it to finish (by joining it) or leave it to run on its own (by detaching it)
    If you don’t decide before the std::thread object is destroyed, then your program is terminated (the std::thread destructor calls std::terminate()).
	
    Ensure that the thread is correctly joined or detached, even in the presence of exceptions
    
	If you don’t wait for your thread to finish, you need to ensure that the data accessed by the thread is valid until the thread has finished with it.

    Caution
    Do not create a thread within a function that has access to the local variables in that function, unless the thread is guaranteed to finish before the function exits.
    Alternatively, you can ensure that the thread has completed execution before the function exits by joining with the thread.

2.1.2 Waiting for a thread to complete

	to wait for a thread to complete, call join() on the associated std::thread instance
	join() is a simple and brute-force technique—either you wait for a thread to finish or you don’t
	
	calling join() also cleans up any storage associated with the thread, so the std::thread object is no longer associated with the now finished thread; it isn’t associated with any thread
	
	you can call join() only once for a given thread
	after a call to join(), the std::thread object is no longer joinable, and joinable() will return false

2.1.3 Waiting in exceptional circumstances

	You need to call either join() or detach() before a std::thread object is destroyed
	
	When caling join(), 
		carefully pick the place in the code where you call join()
		make sure that its called also in presence of an exception to avoid accidental lifetime problems
		One way of doing this is to use the standard Resource Acquisition Is Initialization (RAII) idiom and provide a class that does the join() in its destructor, as in the following listing.
		
	If you don’t need to wait for a thread to finish, you can avoid this exception-safety issue by detaching it.
	This breaks the association of the thread with the std::thread object and ensures that std::terminate() won’t be called when the std::thread object is destroyed, even though the thread is still running in the background.
	
	To detach a thread, you can usually call detach() immediately after the thread has been started

2.1.4 Running threads in the background

	Calling detach() on a std::thread object leaves the thread to run in the background, with no direct means of communicating with it.
	
	Detached threads truly run in the background; ownership and control are passed over to the C++ Runtime Library, which ensures that the resources associated with the thread are correctly reclaimed when the thread exits.
	
	Daemon Threads
	Detached threads are often called daemon threads after the UNIX concept of a daemon process.
	Such threads are typically long-running; they run for almost the entire lifetime of the application
	
***********/

#include <iostream>
#include <thread>
#include <string>
#include <stdexcept>

size_t thread_routine(std::string msg) {
    std::cout << "Inside thread routine, message: " << msg << '\n';
    return msg.size();
}

class ClWithCallOperator {
    public:
    void operator()() {
        std::cout << "Overloaded operator() inside class \n";
    }
};

void thread_routine_02(std::string & msg) {
    std::cout << "Message is " << msg << '\n';
    return ;
}

void using_thread(bool join_flag) {
    std::string msg = "sample string";
    std::thread thr(thread_routine_02, std::ref(msg));
    if(thr.joinable() && join_flag) {
        thr.join();
    } else if(thr.joinable()) {
        // passing reference to local variable has UB in this case
        // because reference to local varible is passed and varible may be destroyed before execution of thread
        thr.detach();   
    }
    return ;
}

void print_in_loop(std::string msg)  {
    for(size_t i = 0; i < 3; ++i) {
        std::cout << msg << '\n';
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
}

class thread_guard {
	std::thread& m_thr;
	
	public:
	explicit thread_guard(std::thread& thr)
		: m_thr(thr) {}

	~thread_guard() {
		if(m_thr.joinable()) {
			m_thr.join();
		}
	}
	
	thread_guard(thread_guard const&)	= delete;
	thread_guard& operator=(thread_guard const&)	= delete;
};

int main() {

    std::cout << "=== Launching a thread ===\n";
    { 
        std::thread thr(thread_routine, "Launching a thread function"); 
        thr.join(); 
    }
    {
        ClWithCallOperator clobj;
        std::thread thr(clobj); 
        thr.join(); 
    }    
    {
        // C++’s most vexing parse
        //std::thread thr(ClWithCallOperator()); // warning: parentheses were disambiguated as a function declaration
        //thr.join(); 
    } 
    {
        // C++’s most vexing parse - SOLUTION-1
        std::thread thr((ClWithCallOperator())); 
        thr.join(); 
    } 
    {
        // C++’s most vexing parse - SOLUTION-2
        std::thread thr(ClWithCallOperator{}); 
        thr.join(); 
    } 
    {
        std::thread thr([](std::string msg){ 
            std::cout << "Inside lambda: " << msg << '\n'; }, 
            "Launching a thread using lambda"); 
        thr.join(); 
    }

    std::cout << "\n=== Waiting for a thread to complete ===\n";
    using_thread(true);
    using_thread(false);
   

    std::cout << "\n=== Waiting in exceptional circumstances ===\n";
    { 
        std::thread thr(thread_routine, "Joining thread in case of exception"); 
        try {
            throw std::runtime_error("Causing an exception");
        } catch (...) {
            // not calling join or detach here will terminate the program      
            if(thr.joinable()) thr.join();
        }
        if(thr.joinable()) thr.join();
    } 

    {
        // Using a thread gauard(RAII) solves issue in above case of exception 
        std::thread thr(thread_routine, "Using thread guard"); 
        try {
            throw std::runtime_error("Causing an exception");
        } catch (...) {

        }
        
        thread_guard thg(thr);
    } 
    
    std::cout << "\n=== Running threads in the background ===\n";
    {
        std::thread thr(print_in_loop, "this thread will run in parallel to main thread");
        thr.detach();
    }
    
    std::cout << "inside main\n";

    // if you want to see execution of detach thread wait for completion of its execution
    //std::this_thread::sleep_for(std::chrono::seconds(8));

    return 0;
}

/*******
	END OF FILE
***********/


