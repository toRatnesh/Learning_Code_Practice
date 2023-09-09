/*****

References
    Anthony Williams - C++ Concurrency in Action

3.2 Protecting shared data with mutexes
    mutex (mutual exclusion)
        You could mark all the pieces of code that access the data structure as mutually exclusive, so that if any thread was running one of them, any other thread that tried to access that data structure had to wait until the first thread was finished
        Mutexes also has issue of deadlock and protecting either too much or too little data

3.2.1 Using mutexes in C++

    To use 
        create a mutex by constructing an instance of std::mutex
        to lock call lock() member function
        to unlock call unlock() member function

    std::lock_guard
        Standard C++ implements RAII idiom for a mutex
        it locks the supplied mutex on construction and unlocks it on destruction
        ensuring a locked mutex is always correctly unlocked

        since C++17 CTAD is present, so there is no need to provide template argument for std::lock_gurad
        std::lock_guard guard(some_mutex);

    std::scoped_lock
        since C++17, an enhanced version of lock guard
        mutex wrapper that provides a convenient RAII-style mechanism for owning zero or more mutexes for the duration of a scoped block

    Any code that has access to that pointer or reference can now access (and potentially modify) the protected data without locking the mutex.
    Protecting data with a mutex therefore requires careful interface design to ensure that the mutex is locked before there’s any access to the protected data and that there are no backdoors.

**********/

#include <iostream>
#include <vector>
#include <mutex>
#include <thread>

std::vector<int>    gvec;
std::mutex          gvec_mutex;

void add_to_vector(int val) {
    std::cout << "setting value " << val << '\n';
    // using member functions lock and unlock for mutex
    gvec_mutex.lock();      // lock mutex
    gvec.push_back(val);
    gvec_mutex.unlock();    // unlock mutex
    return;
}

int get_vec_val(int index) {
    // using lock_gurad for mutex
    //std::lock_guard<std::mutex>     mt_guard(gvec_mutex); // pre C++17
    std::lock_guard     mt_guard(gvec_mutex);     // using C++17 CTAD
    if(index >= gvec.size()) {
        return -1;
    }
    return gvec[index];
}

size_t get_vec_size() {
    // using lock_gurad for mutex
    std::scoped_lock    slock(gvec_mutex);
    return gvec.size();
}

void set() {
    for(int i = 0; i < 5; ++i) {
        add_to_vector(i+1);  
    }
    return ;
}

void get() {
    for(int i = 0; i < 5; ++i) {
        std::cout << "vector value at index " << i << ": " << get_vec_val(i) << '\n';
    }
    return ;
}

void get_size() {
    for(int i = 0; i < 5; ++i) {
        std::cout << "vector size is " << get_vec_size() << '\n';
    }
    return ;
}

void use_vector(std::vector<int> & avec) {
    for(int i = 11; i < 15; ++i) {
        avec.push_back(i);
    }
    return ;
}

void some_operations() {
    // paasing gvec as reference may lead to problem
    // because in the called function it may be modified without any protection
    use_vector(gvec);   
}

int main() {

    std::thread sth(set);
    std::thread gth(get);
    std::thread szth(get_size);

    some_operations();

    if(sth.joinable()) sth.join();
    if(gth.joinable()) gth.join();
    if(szth.joinable()) szth.join();

    return 0;
}

/*****
    END OF FILE
**********/


