/*******

References
    Juan Antonio Rufes - Asynchronous Programming with C++
    https://en.cppreference.com/w/cpp/thread/latch.html

std::latch
    The latch class is a downward counter of type std::ptrdiff_t which can be used to synchronize threads.
    The value of the counter is initialized on creation.
    Threads may block on the latch until the counter is decremented to zero.
    There is no possibility to increase or reset the counter, which makes the latch a single-use barrier.

    Concurrent invocations of the member functions of std::latch, 
    except for the destructor, do not introduce data races.

**********/

#include <iostream>
#include <latch>
#include <thread>
#include <vector>

std::latch  guest_count{5};
void arriveHere(const unsigned tval) {

    sleep(tval);
    
    std::cout << "I'm thread: " << std::this_thread::get_id() << '\n';

    guest_count.arrive_and_wait();

    std::cout << "Thread: " << std::this_thread::get_id() << " arrived\n";

}


std::latch  resource_count{5};

void producer() {
    std::cout << "Thread: " << std::this_thread::get_id() << " using resource\n";
    resource_count.count_down();

    std::cout << "Thread: " << std::this_thread::get_id() << " doing some other work\n";
}


void consumer() {
    resource_count.wait();
    std::cout << "All resources consumed\n";
}

int main() {

    {
        std::vector<std::jthread> threads;
        for(unsigned i = 0; i < 5; ++i) {
            threads.push_back(std::jthread(&arriveHere, i));
        }
    }
    std::cout << '\n';

    {
        std::vector<std::jthread> threads;
        for(unsigned i = 0; i < 5; ++i) {
            threads.push_back(std::jthread(&producer));
        }
        threads.push_back(std::jthread(&consumer));
    }

    return 0;
}

/*****
    END OF FILE
**********/
