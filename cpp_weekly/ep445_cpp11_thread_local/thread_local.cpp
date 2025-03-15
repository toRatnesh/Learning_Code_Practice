/*****

References
    episode https://www.youtube.com/watch?v=q9_vljSaBDg
    https://en.cppreference.com/w/cpp/language/storage_duration

thread_local

    All variables declared with thread_local have thread storage duration.
    The storage for these entities lasts for the duration of the thread in which they are created. 
    There is a distinct object or reference per thread, and use of the declared name refers to the entity associated with the current thread.


    thread_local variable is global to a single thread

    begin its lifetime the first time this line is executed in a given thread
    ends its lifetime when the thread ends

    static thread_local variable corresponse to thread_local variable 

**********/

#include <iostream>
#include <thread>
#include <vector>
#include <syncstream>

std::osyncstream scout(std::cout);

void routine() {
    thread_local int tlval = 0;
    scout << "thread: " << std::this_thread::get_id() << ", value " << tlval << '\n';
    ++tlval;
}

void multicall() {
    for(size_t i = 0; i < 5; ++i) {
        routine();   
    }        
}

int main() {
    std::vector<std::jthread> thvec;

    for(size_t i = 0; i < 5; ++i) {
        thvec.push_back(std::jthread(routine));    
    }
    thvec.push_back(std::jthread(multicall));

    return 0;
}

/*****
    END OF FILE
**********/


