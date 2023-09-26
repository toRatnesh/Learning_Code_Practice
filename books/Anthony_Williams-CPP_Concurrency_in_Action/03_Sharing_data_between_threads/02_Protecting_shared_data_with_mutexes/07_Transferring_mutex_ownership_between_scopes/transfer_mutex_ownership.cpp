/*****

References
    Anthony Williams - C++ Concurrency in Action

3.2 Protecting shared data with mutexes
    mutex (mutual exclusion)
        You could mark all the pieces of code that access the data structure as mutually exclusive, so that if any thread was running one of them, any other thread that tried to access that data structure had to wait until the first thread was finished
        Mutexes also has issue of deadlock and protecting either too much or too little data

3.2.7 Transferring mutex ownership between scopes

	Because std::unique_lock instances don’t have to own their associated mutexes, the ownership of a mutex can be transferred between instances by moving the instances around.
	std::unique_lock is moveable but not copyable
	
	Uses
	One such usage is where the lock isn’t returned directly but is a data member of a gateway class used to ensure correctly locked access to some protected data.
	The flexibility of std::unique_lock also allows instances to relinquish their locks before they’re destroyed.
	

**********/

#include <iostream>
#include <mutex>
#include <thread>
#include <string>


std::string shared_data;
std::mutex	shared_data_mutex;

std::unique_lock<std::mutex> update(std::string data) {

	std::unique_lock unq_lock(shared_data_mutex);
	shared_data = data;
	return unq_lock;
}

void reset(std::unique_lock<std::mutex> unq_lock_parm) {
	std::unique_lock unq_lock(std::move(unq_lock_parm));
	shared_data.clear();   
}

void display(std::string data) {
	std::unique_lock unq_lock(update(data));
	std::cout << shared_data << '\n';
	reset(std::move(unq_lock));
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


