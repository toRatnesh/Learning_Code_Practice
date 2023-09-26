/*****

References
    Anthony Williams - C++ Concurrency in Action

3.2 Protecting shared data with mutexes
    mutex (mutual exclusion)
        You could mark all the pieces of code that access the data structure as mutually exclusive, so that if any thread was running one of them, any other thread that tried to access that data structure had to wait until the first thread was finished
        Mutexes also has issue of deadlock and protecting either too much or too little data

3.2.8 Locking at an appropriate granularity
	The granularity of a lock is a hand-waving term to describe the amount of data protected by a single lock.
	A fine-grained lock protects a small amount of data, and a coarse-grained lock protects a large amount of data.
	
	Where possible, lock a mutex only while accessing the shared data.
	Don’t do any time-consuming activities like file I/O while holding a lock.
	
	Granularity isn’t only about the amount of data locked; it’s also about how long the lock is held and what operations are performed while the lock is held.
	Time consuming operations such as acquiring another lock (even if you know it won’t deadlock) or waiting for I/O to complete shouldn’t be done while holding a lock unless absolutely necessary.
	
	If you don’t hold the required locks for the entire duration of an operation, you’re exposing yourself to race conditions.

**********/

#include <iostream>
#include <mutex>
#include <thread>
#include <string>


std::string shared_data;
std::mutex	shared_data_mutex;

void update(std::string data) {
	std::unique_lock unq_lock(shared_data_mutex);
	shared_data = data;
}

void display(std::string data) {
	std::unique_lock unq_lock(shared_data_mutex, std::defer_lock);
	
	update(data);
	
	std::cout << "Shared data is: ";
	unq_lock.lock();
	std::cout << shared_data << '\n';
	unq_lock.unlock();
	
	
}

int main() {

	std::thread thr_01(display, "Updating shared data from thread-01");
	std::thread thr_02(display, "Updating shared data from thread-02");
	
	thr_01.join();
	thr_02.join();
	
    return 0;
}

/*****
    END OF FILE
**********/


