/*****

References
    Anthony Williams - C++ Concurrency in Action

3.3 Alternative facilities for protecting shared data
	Apart from std::mutex there are other mechanism to protect shared data in special scenario. Like
	std::call_once
	std::shared_mutex
	std::recursive_mutex

3.3.3 Recursive locking
	For std::mutex, it’s an error for a thread to try to lock a mutex it already owns, and attempting to do so will result in undefined behavior

	std::recursive_mutex
	to reacquire the same mutex several times without having first released it
	You must release all your locks before the mutex can be locked by another thread
	
	Use case 
	When a class is designed to be accessible from multiple threads concurrently, so it has a mutex protecting the member data.
	Sometimes it’s desirable for one public member function to call another as part of its operation. In this case, the second member function will also try to lock the mutex.
	But such usage is not recommended because it can lead to sloppy thinking and bad design. In particular, the class invariants are typically broken while the lock is held, which means that the second member function needs to work even when called with the invariants broken.	
	It’s usually better to extract a new private member function that’s called from both member functions, which does not lock the mutex (it expects it to already be locked).	
	
	Most of the time, if you think you want a recursive mutex, you probably need to change your design instead.

**********/

#include <iostream>
#include <mutex>
#include <thread>
#include <string>

class Data {
    std::string             m_data;
    std::recursive_mutex    m_data_mutex;

    public:
    
    void display() {
        std::lock_guard guard(m_data_mutex);
        std::cout << "data is " << m_data << '\n';
    }

    void update_and_display(std::string data) {
        std::lock_guard guard(m_data_mutex);
        m_data = data;
        display();
    }
};

int main() {
    Data data;

    std::thread th1(&Data::update_and_display, std::ref(data), "Thread-01");
    std::thread th2(&Data::update_and_display, std::ref(data), "Thread-02");
    
    if(th1.joinable()) th1.join();
    if(th2.joinable()) th2.join();

    return 0;
}

/*****
    END OF FILE
**********/


