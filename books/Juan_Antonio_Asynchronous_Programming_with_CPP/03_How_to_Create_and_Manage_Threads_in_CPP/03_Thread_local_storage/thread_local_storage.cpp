/*******

References
    Juan Antonio Rufes - Asynchronous Programming with C++
    https://en.cppreference.com/w/cpp/language/storage_duration.html

Thread storage duration:
    All variables declared with thread_local have thread storage duration.
    The storage for these entities lasts for the duration of the thread in which they are created. 
    There is a distinct object or reference per thread, and use of the declared name refers 
    to the entity associated with the current thread.

**********/

#include <iostream>
#include <thread>
#include <vector>

thread_local int global{1};

void routine(const int value) {
    sleep(value);
    thread_local int local{2};

    global = global * value;
    local  = local * value;

    std::cout << "global: " << global << ", local: " << local << '\n';
}


int main() {

    std::vector<std::jthread>   threads;

    for(int i = 1; i <= 5; ++i) {
        threads.emplace_back(routine, i);
    }

    return 0;
}

/*****
    END OF FILE
**********/
