/*******

References
    Anthony Williams - C++ Concurrency in Action

2 Managing threads

    The C++ Standard Library makes most thread-management tasks relatively easy,
    with almost everything managed through the std::thread object associated
with a given thread.

2.4 Choosing the number of threads at runtime

	std::thread::hardware_concurrency() returns an indication of the number of threads that can truly run concurrently
	On a multicore system it might be the number of CPU cores, for example
	This is only a hint, and the function might return 0 if this information isn’t available

	Oversubscription
	when you run more threads than the hardware can support
	because the context switching will mean that more threads will decrease the performance

***********/

#include <iostream>
#include <string>
#include <thread>
#include <vector>
#include <numeric>

void thread_routine() { return; }

template <typename Iterator, typename T>
struct accumulate_block {
    void operator()(Iterator first, Iterator last, T& result) {
        result = std::accumulate(first, last, result);
    }
};

template <typename Iterator, typename T>
T parallel_accumulate(Iterator first, Iterator last, T init) {
    
    unsigned long const length = std::distance(first, last);
    if (!length) return init;

    unsigned long const min_per_thread = 25;
    unsigned long const max_threads =
        (length + min_per_thread - 1) / min_per_thread;
    unsigned long const hardware_threads = std::thread::hardware_concurrency();
    // The number of threads to run is the minimum of 
    // your calculated maximum and the number of hardware threads
    unsigned long const num_threads =
        std::min(hardware_threads != 0 ? hardware_threads : 2, max_threads);
    
    unsigned long const block_size = length / num_threads;
    
    std::vector<T> results(num_threads);
    std::vector<std::thread> threads(num_threads - 1);
    
    Iterator block_start = first;
    for (unsigned long i = 0; i < (num_threads - 1); ++i) {
        Iterator block_end = block_start;
        std::advance(block_end, block_size);
        threads[i] = std::thread(accumulate_block<Iterator, T>(), 
            block_start, block_end, std::ref(results[i]));
        block_start = block_end;
    }
    accumulate_block<Iterator, T>()(block_start, last, results[num_threads - 1]);

    for (auto& entry : threads) 
        entry.join();
    
    return std::accumulate(results.begin(), results.end(), init);
}

int main() {
    std::vector<int> vec_ints;
    const int num_elems = 9999;
    
    for(size_t i = 0; i < num_elems; ++i) {
        vec_ints.emplace_back(i);
    }

    {
        auto res = parallel_accumulate(vec_ints.cbegin(), vec_ints.cend(), 0);
        std::cout << "Result is " <<  res << '\n';
    }

    {
        int res = 0;
        //auto res = accumulate_block<std::vector::const_iterator, int>()(vec_ints.cbegin(), vec_ints.cend(), 0); 
        accumulate_block<decltype(vec_ints.cbegin()), int>()(vec_ints.cbegin(), vec_ints.cend(), res);
        std::cout << "Result is " <<  res << '\n';
    }

    return 0; 
}

/*******
        END OF FILE
***********/


