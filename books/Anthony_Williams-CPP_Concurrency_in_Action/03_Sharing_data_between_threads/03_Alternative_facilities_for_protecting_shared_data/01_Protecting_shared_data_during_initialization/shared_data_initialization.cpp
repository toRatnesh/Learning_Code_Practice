/*****

References
    Anthony Williams - C++ Concurrency in Action

3.3 Alternative facilities for protecting shared data
	Apart from std::mutex there are other mechanism to protect shared data in special scenario. Like
	std::call_once
	std::shared_mutex
	std::recursive_mutex
	
3.3.1 Protecting shared data during initialization
	Suppose you are lazy initializing a shaerd data for example a Singleton instance
	and you are using mutithreded code, then you will need to protect the only during initialization to avoid race condition
	
	A protection like following listing can cause unnecessary serialization of threads
	
	class Singleton {
		static Singleton * instance = nullptr;
		
		...

		static Singleton * get_instance() {
			std::unique_lock<std::mutex> unq_lock(resource_mutex);	// All threads are serialized here
			if(!instance) {
				instance = new Singleton();	// Only the initialization needs protection
			}
			unq_lock.unlock();
			return instance;
		}
		
		...
	
	};



	Double-checked locking pattern also fails to provide a solution
	it has the potential for nasty race conditions, because the read outside the lock, isn’t synchronized with the write done by another thread inside the lock

	
	class Singleton {
		static Singleton * instance = nullptr;
		
		...

		static Singleton * get_instance() {
			if(!instance) {
				std::unique_lock<std::mutex> unq_lock(resource_mutex);	// All threads are serialized here
				if(!instance) {
					instance = new Singleton();	// Only the initialization needs protection
				}
				unq_lock.unlock();	
			}
			return instance;
		}
		
		...
	
	};	
	
	std::once_flag and std::call_once
	C++ Standard Library provides std::once_flag and std::call_once to handle this situation.
	every thread can use std::call_once, safe in the knowledge that the pointer will have been initialized by some thread
	
	The necessary synchronization data is stored in the std::once_flag instance; each instance of std::once_flag corresponds to a different initialization.
	
	Use of std::call_once will typically have a lower overhead than using a mutex explicitly, especially when the initialization has already been done
	
	std::once_flag instances can’t be copied or moved
	
	class Singleton {
		static Singleton * instance = nullptr;
		static std::once_flag resource_flag;
		
		static void init_instance() {
			if(!instance) {
				instance = new Singleton();
			}	
		}

		...
		
		Singleton * get_instance() {
			std::call_once(resource_flag, init_instance); // Initialization is called exactly once.
			return instance;
		}
		...
		
	};	

	C++11 Local static are thread safe
	One scenario where there’s a potential race condition over initialization is that of a local variable declared with static.
	In C++11 this problem is solved: the initialization is defined to happen on exactly one thread, and no other threads will proceed until that initialization is complete, so the race condition is over.
	This can be used as an alternative to std::call_once for those cases where a single global instance is required.
	
	class Singleton {
		...
		static Singleton & get_instance() {
			static Singleton instance;	// Initialization guaranteed to be thread-safe
			return instance;
		}
		...
	};
	

**********/

#include <iostream>
#include <mutex>
#include <thread>
#include <string>

class SingletonUsingCallOnce {
    static SingletonUsingCallOnce * instance;
    static std::once_flag resource_flag;

    std::string     m_data;
    
    static void init_instance() {
        if(!instance) {
            instance = new SingletonUsingCallOnce();
        }	
    }
    
    public:
    static SingletonUsingCallOnce * get_instance() {
        std::call_once(resource_flag, init_instance); // Initialization is called exactly once.
        return instance;
    }

    void display_instance(std::string thread_id) {
        std::cout << "Thread " << thread_id << ", instance " << instance << '\n';
    }

};
SingletonUsingCallOnce * SingletonUsingCallOnce::instance = nullptr;
std::once_flag SingletonUsingCallOnce::resource_flag;

class SingletonCpp11 {
    std::string     m_data;
    
    public:
    static SingletonCpp11 & get_instance() {
        static SingletonCpp11 instance;
        return instance;
    }

    void display_instance(std::string thread_id) {
        std::cout << "Thread " << thread_id << ", instance " << &(get_instance()) << '\n';
    }

};

int main() {
    
    {
        std::cout << "=== initialization using std::call_once ===\n";

        std::thread th1(&SingletonUsingCallOnce::display_instance, SingletonUsingCallOnce::get_instance(), "thread-01");
        std::thread th2(&SingletonUsingCallOnce::display_instance, SingletonUsingCallOnce::get_instance(), "thread-02");

        if(th1.joinable())  th1.join();
        if(th2.joinable())  th2.join();
    }
    std::cout << '\n';

    {
        std::cout << "=== initialization using C++11 local static varible ===\n";

        std::thread th1(&SingletonCpp11::display_instance, SingletonCpp11::get_instance(), "thread-01");
        std::thread th2(&SingletonCpp11::display_instance, SingletonCpp11::get_instance(), "thread-02");

        if(th1.joinable())  th1.join();
        if(th2.joinable())  th2.join();
    }

    return 0;
}

/*****
    END OF FILE
**********/


