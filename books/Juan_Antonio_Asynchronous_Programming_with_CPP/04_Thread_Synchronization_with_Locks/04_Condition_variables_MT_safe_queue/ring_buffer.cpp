/*******

References
    Juan Antonio Rufes - Asynchronous Programming with C++
    https://en.cppreference.com/w/cpp/thread/condition_variable.html


Thread Safe Ring Buffer:
    Implementing a thread safe ring buffer using std::vector, std::mutex and std::condition_variable

***********/

#include <iostream>
#include <string>
#include <atomic>
#include <chrono>
#include <thread>

#include "ring_buffer.hpp"

RingBuffer<std::string, 1024> rbuffer;
std::atomic_uint32_t    consumed_count{0};
std::atomic_uint32_t    produced_count{0};

void producer(const std::size_t data_size)
{
    std::string data{"Pushing data "};
    for (std::size_t i = 0; i < data_size; ++i)
    {
        if(rbuffer.tryPush(data + std::to_string(i))) {
            ++produced_count;
        }
    }
}

void consumer(const std::size_t data_size)
{
    std::string data;
    for (std::size_t i = 0; i < data_size; ++i)
    {
        if (rbuffer.tryPop(data))
        {
            ++consumed_count;
        }
    }
}

int main()
{

    const std::size_t iter_count{1024};

    std::thread pth(producer, iter_count);
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::thread cth(consumer, iter_count);

    //std::this_thread::sleep_for(std::chrono::seconds(3));

    pth.join();
    cth.join();

    std::cout << "Producer count: " << produced_count << ", Consumer count: " << consumed_count << '\n';

    return 0;
}


/*******
	END OF FILE
***********/
