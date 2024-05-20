/*****

References
    Anthony Williams - C++ Concurrency in Action
    https://en.cppreference.com/w/cpp/algorithm/find

8. Designing concurrent code

Think carefully about the design of concurrent code

Think about the usual factors, such as encapsulation, coupling, and cohesion
also need to consider which data to share, how to synchronize accesses to that
data, which threads need to wait for which other threads to complete certain
operations, and so on

8.5 Designing concurrent code in practice

8.5.2 A parallel implementation of std::find

it’s one of several algorithms that can complete without every element having
been processed For algorithms such as std::find, the ability to complete “early”
is an important property and not something to squander You therefore need to
design your code to make use of it—to interrupt the other tasks in some way when
the answer is known, so that the code doesn’t have to wait for the other worker
threads to process the remaining elements

If you don’t interrupt the other threads, the serial version may outperform your
parallel implementation

One way in which you can interrupt the other threads is by making use of an
atomic variable as a flag and checking the flag after processing every element.
If the flag is set, one of the other threads has found a match, so you can cease
processing and return. The downside to this is that atomic loads can be slow
operations, so this can impede the progress of each thread.

If you want to stop on the first exception (even if you haven’t processed all
elements), you can use std::promise to set both the value and the exception. On
the other hand, if you want to allow the other workers to keep searching, you
can use std::packaged_task, store all the exceptions, and then rethrow one of
them if a match isn’t found.

**********/

#include <algorithm>
#include <atomic>
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
        if (m_thread.joinable()) m_thread.join();
    }
    jthread() {}
    jthread(std::thread athread) : m_thread(std::move(athread)) {}

    jthread(const jthread &) = delete;
    jthread &operator=(const jthread &) = delete;

    jthread(jthread &&other) : m_thread(std::move(other.m_thread)) {}

    jthread &operator=(jthread &&other) {
        if (this != &other) {
            m_thread = std::move(other.m_thread);
        }
        return *this;
    }
};
}  // namespace nonstd

template <typename It, typename Value>
It parallel_find(It begin, It end, Value val) {

    const auto length = std::distance(begin, end);
    if(! length)
        return begin;

    const size_t hardware_threads_count = std::thread::hardware_concurrency();
    const size_t per_thread_count = 100;
    const size_t max_threads = (length + per_thread_count - 1)/per_thread_count;
    const size_t threads_count = std::min(hardware_threads_count?hardware_threads_count:2, max_threads);
    const size_t block_size = length/threads_count;

    
    std::promise<It>                result;
    std::atomic_bool                done{false};

    It block_start  = begin;
    It block_end    = block_start;

    auto find_h = [&](It begin, It end, Value val) {
        if(done.load()) {
            
        } else {
            auto it = std::find(begin, end, val);
            if(it == end) {

            } else {
                done = true;
                result.set_value(it);
            }
        }

    };

    {
        std::vector<nonstd::jthread>    tvec(threads_count-1);
        for(size_t i = 0; i < (threads_count - 1); ++i) {
            std::advance(block_end, block_size);
            tvec[i] = std::thread(find_h, block_start, block_end, val);
            block_start = block_end;
        }
        find_h(block_start, end, val);
    }

    if(done.load()) {
        return result.get_future().get();
    }
    return end;
}

template <typename It, typename Value>
It parallel_find_using_async(It begin, It end, Value val) {

    const auto length = std::distance(begin, end);
    if(! length)
        return begin;

    const size_t per_thread_count = 100;

    static std::atomic_bool  done{false};

    if (length < (2 * per_thread_count)) {
        if(done.load()) {
            return end;
        } else {
            auto it = std::find(begin, end, val);
            if(it == end) {

            } else {
                done = true;
            }
            return it;
        }
    } else {
        const auto mid_point = begin + (length / 2);
        auto fut = std::async(&parallel_find_using_async<It, Value>, mid_point, end, val);
        auto it = parallel_find_using_async(begin, mid_point, val);
        return (it == mid_point) ? fut.get() : it;      
    }
}


int main() {
    constexpr size_t count = 1000;
    std::vector<std::string> svec;
    for (size_t i = 0; i < count; ++i) {
        svec.push_back("string-" + std::to_string(i));
    }

    const std::string elem = "string-633";
    {
        std::cout << "=== using std::find\n";
        auto it = std::find(svec.begin(), svec.end(), elem);
        if (it == svec.end()) {
            std::cout << elem << " not found\n";
        } else {
            std::cout << elem << " found, index " << it - svec.begin() << '\n';
        }
    }

    {
        std::cout << "=== using parallel_find_using_async\n";
        auto it = parallel_find_using_async(svec.begin(), svec.end(), elem);
        if (it == svec.end()) {
            std::cout << elem << " not found\n";
        } else {
            std::cout << elem << " found, index " << it - svec.begin() << '\n';
        }
    }

    
    {
        std::cout << "=== using parallel_find\n";
        auto it = parallel_find(svec.begin(), svec.end(), elem);
        if (it == svec.end()) {
            std::cout << elem << " not found\n";
        } else {
            std::cout << elem << " found, index " << it - svec.begin() << '\n';
        }
    }


    return 0;
}

/*****
    END OF FILE
**********/

