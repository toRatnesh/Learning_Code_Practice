/*******

References
    Juan Antonio Rufes - Asynchronous Programming with C++
    https://en.cppreference.com/w/cpp/thread/latch.html


**********/

#include <iostream>
#include <atomic>
#include <vector>
#include <thread>
#include <string>
#include <cassert>
#include <chrono>

template <typename T>
class spsc_lock_free_queue
{

    const std::size_t m_capacity;

    std::size_t m_cache_windex{0};
    std::size_t m_cache_rindex{0};

    alignas(std::hardware_destructive_interference_size) std::atomic<std::size_t> m_windex{0};
    alignas(std::hardware_destructive_interference_size) std::atomic<std::size_t> m_rindex{0};

    std::vector<T> m_data;

public:
    explicit spsc_lock_free_queue(const std::size_t capacity) : m_capacity{capacity}, m_data(m_capacity)
    {
    }

    spsc_lock_free_queue(const spsc_lock_free_queue &) = delete;
    spsc_lock_free_queue &operator=(const spsc_lock_free_queue &) = delete;

    std::size_t next(const std::size_t index) const
    {
        return (index + 1) % m_capacity;
    }

    bool tryPush(const T &data)
    {
        bool l_ret{false};

        const auto l_windex = m_windex.load(std::memory_order_relaxed);
        const auto l_next_windex = next(l_windex);

        if (l_next_windex == m_cache_rindex)
        {
            m_cache_rindex = m_rindex.load(std::memory_order_acquire);

            if (l_next_windex == m_cache_rindex)
            {
                // queue is full
                return false;
            }
        }
        else
        {
            m_data[l_windex] = data;
            m_windex.store(l_next_windex, std::memory_order_release);
            l_ret = true;
        }

        return l_ret;
    }

    bool tryPop(T &data)
    {
        bool l_ret{false};
        const std::size_t l_rindex = m_rindex.load(std::memory_order_relaxed);

        if (l_rindex == m_cache_windex)
        {
            m_cache_windex = m_windex.load(std::memory_order_acquire);
            if (l_rindex == m_cache_windex)
            {
                // queue is empty
                return l_ret;
            }
        }
        else
        {
            data = m_data[l_rindex];
            const std::size_t l_next_rindex = next(l_rindex);
            m_rindex.store(l_next_rindex, std::memory_order_release);

            l_ret = true;
        }

        return l_ret;
    }
};

struct Data
{
    std::string data;
};

constexpr std::size_t qsize{1024 * 1024};
spsc_lock_free_queue<Data> shared_queue{qsize};

void producer()
{

    std::size_t push_cnt{0};

    for (std::size_t i = 0; i < qsize; ++i)
    {
        if (shared_queue.tryPush(Data{std::string("data-") + std::to_string(i)}))
        // if (shared_queue.tryPush(i))
        {
            ++push_cnt;
        }
    }

    std::cout << "Push count: " << push_cnt << '\n';
}

void consumer()
{

    std::size_t pop_cnt{0};

    for (std::size_t i = 0; i < qsize; ++i)
    {
        Data l_data;
        if (shared_queue.tryPop(l_data))
        {
            ++pop_cnt;
        }
    }

    std::cout << "Pop count: " << pop_cnt << '\n';
}

int main()
{
    std::jthread l_pth(&producer);
    std::this_thread::sleep_for(std::chrono::nanoseconds(100));
    std::jthread l_cth(&consumer);

    return 0;
}

/*****
    END OF FILE
**********/
