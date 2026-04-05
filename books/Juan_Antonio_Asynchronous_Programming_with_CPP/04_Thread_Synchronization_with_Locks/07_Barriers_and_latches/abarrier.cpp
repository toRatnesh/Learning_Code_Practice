/*******

References
    Juan Antonio Rufes - Asynchronous Programming with C++
    https://en.cppreference.com/w/cpp/thread/barrier.html

std::barrier
    The class template std::barrier provides a thread-coordination mechanism that blocks 
    a group of threads of known size until all threads in that group have reached the barrier.

Diffrence from std::latch
    Unlike std::latch, barriers are reusable: once a group of arriving threads are unblocked, the barrier can be reused.
    Unlike std::latch, barriers execute a possibly empty callable before unblocking threads.

**********/

#include <iostream>
#include <barrier>
#include <thread>
#include <vector>

std::barrier  guest_count{5};
void arriveHere(const unsigned tval) {

    sleep(tval);
    
    std::cout << "Thread: " << std::this_thread::get_id() << " running\n";
    guest_count.arrive_and_wait();
    std::cout << "Thread: " << std::this_thread::get_id() << " arrived\n";

    sleep(tval);
    std::cout << "Thread: " << std::this_thread::get_id() << " running again\n";
    guest_count.arrive();
    std::cout << "Thread: " << std::this_thread::get_id() << " finished\n";

}


std::barrier  resource_count{5 + 1, []{std::cout << "All resources consumed\n";}};    // 5 producer + 1 consumer

void producer() {
    std::cout << "Thread: " << std::this_thread::get_id() << " using resource\n";
    resource_count.arrive();

    std::cout << "Thread: " << std::this_thread::get_id() << " doing some other work\n";
}


void consumer() {
    resource_count.arrive_and_wait();
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
