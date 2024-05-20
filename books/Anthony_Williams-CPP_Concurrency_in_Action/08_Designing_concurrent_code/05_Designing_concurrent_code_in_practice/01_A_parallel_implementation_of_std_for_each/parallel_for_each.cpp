/*****

References
    Anthony Williams - C++ Concurrency in Action
    https://en.cppreference.com/w/cpp/algorithm/for_each

8. Designing concurrent code

Think carefully about the design of concurrent code

Think about the usual factors, such as encapsulation, coupling, and cohesion
also need to consider which data to share, how to synchronize accesses to that data, which threads need to wait for which other threads to complete certain operations, and so on

8.5 Designing concurrent code in practice

8.5.1 A parallel implementation of std::for_each

divide the range into sets of elements to process on each thread
use std::thread::hardware_concurrency() to determine the number of threads
the elements can be processed entirely independently, so you can use contiguous blocks to avoid false sharing
use the std::packaged_task and std::future mechanisms to transfer the exception between threads


**********/

#include <algorithm>
#include <future>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

namespace nonstd {
class jthread {
    std::thread m_thread;

   public:
    ~jthread() { 
        if(m_thread.joinable()) m_thread.join();
    }
    jthread() { }
    jthread(std::thread athread) : m_thread(std::move(athread)) {}

    jthread(const jthread &)    = delete;
    jthread & operator=(const jthread &)    = delete;

    jthread(jthread && other)
        : m_thread(std::move(other.m_thread)) { }

    jthread& operator=(jthread && other) {
        if(this != &other) {
            m_thread = std::move(other.m_thread);
        }
        return *this;
    }
};
}  // namespace nonstd


void fun(std::string arg) { std::cout << arg << '\n'; }

template <typename It, typename Callable>
void parallel_for_each(It begin, It end, Callable callable) {
    const auto length = std::distance(begin, end);
    if (not length) {
        return;
    }

    const size_t per_thread_count = 25;
    const size_t max_threads =
        (length + per_thread_count - 1) / per_thread_count;
    const size_t hardware_threads_count = std::thread::hardware_concurrency();
    const size_t threads_count = std::min(
        hardware_threads_count ? hardware_threads_count : 2, max_threads);

    const size_t block_size = length / threads_count;

    std::vector<nonstd::jthread>    tvec(threads_count - 1);
    std::vector<std::future<void>>  fvec(threads_count - 1);
    //join_threads joiner(tvec);

    It block_start = begin;
    It block_end = block_start;

    for (size_t i = 0; i < (threads_count - 1); ++i) {
        std::advance(block_end, block_size);
        std::packaged_task<void(void)> task(
            [=]() { std::for_each(block_start, block_end, callable); });

        fvec[i] = task.get_future();
        tvec[i] = nonstd::jthread(std::thread(std::move(task)));

        block_start = block_end;
    }
    std::for_each(block_start, end, callable);

    for (size_t i = 0; i < (threads_count - 1); ++i) {
        fvec[i].get();
    }
}

template <typename It, typename Callable>
void parallel_for_each_using_async(It begin, It end, Callable callable) {
    const auto length = std::distance(begin, end);
    if (not length) return;

    const long per_thread_count = 25;

    if (length < (2 * per_thread_count)) {
        std::for_each(begin, end, callable);
    } else {
        const It mid_point = begin + length / 2;

        auto first_half =
            std::async(&parallel_for_each_using_async<It, Callable>, begin,
                       mid_point, callable);

        parallel_for_each_using_async(mid_point, end, callable);

        first_half.get();
    }
}

int main() {
    constexpr size_t count = 1000;
    std::vector<std::string> svec;
    for (size_t i = 0; i < count; ++i) {
        svec.push_back("string-" + std::to_string(i));
    }

    // std::for_each(svec.begin(), svec.end(), fun);
    // parallel_for_each_using_async(svec.begin(), svec.end(), fun);
    parallel_for_each(svec.begin(), svec.end(), fun);

    return 0;
}

/*****
    END OF FILE
**********/


