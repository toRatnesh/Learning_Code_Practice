/*******

References
    Asynchronous Programming with C++ | Javier Reguera-Salgado & Juan Antonio Rufes
    https://en.cppreference.com/w/cpp/thread/latch.html
    https://david.alvarezrosa.com/posts/optimizing-a-lock-free-ring-buffer/#single-threaded-ring-buffer

**********/

#include <iostream>
#include <atomic>
#include <vector>
#include <thread>
#include <string>
#include <cassert>
#include <chrono>

template <typename T, std::size_t capacity>
class spsc_lock_free_queue
{
    static_assert((capacity >= 2), "capacity must be at least 2");
    static_assert((capacity & (capacity - 1)) == 0, "capacity must be power of 2");

    static constexpr std::size_t m_mask{capacity - 1};

    std::size_t m_cache_windex{0};
    std::size_t m_cache_rindex{0};

    alignas(std::hardware_destructive_interference_size) std::atomic<std::size_t> m_windex{0};
    alignas(std::hardware_destructive_interference_size) std::atomic<std::size_t> m_rindex{0};

    std::vector<T> m_data;

public:
    spsc_lock_free_queue() : m_data(capacity)
    {
    }

    spsc_lock_free_queue(const spsc_lock_free_queue &) = delete;
    spsc_lock_free_queue &operator=(const spsc_lock_free_queue &) = delete;

    static std::size_t next(const std::size_t index)
    {
        return (index + 1) & m_mask;
    }

    bool tryPush(const T &data)
    {
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

        m_data[l_windex] = data;
        m_windex.store(l_next_windex, std::memory_order_release);

        return true;
    }

    bool tryPop(T &data)
    {
        const std::size_t l_rindex = m_rindex.load(std::memory_order_relaxed);

        if (l_rindex == m_cache_windex)
        {
            m_cache_windex = m_windex.load(std::memory_order_acquire);
            if (l_rindex == m_cache_windex)
            {
                // queue is empty
                return false;
            }
        }
        
        
        data = std::move(m_data[l_rindex]);
        m_rindex.store(next(l_rindex), std::memory_order_release);

        return true;
    }
};

struct Data
{
    std::string data;
};

constexpr std::size_t qsize{1024};
spsc_lock_free_queue<Data, qsize> shared_queue{};

constexpr std::size_t elem_cnt{1024 * 3};

void producer()
{
    std::size_t push_cnt{0};

    for (std::size_t i = 0; i < elem_cnt; ++i)
    {
        while (not shared_queue.tryPush(Data{std::string("data-") + std::to_string(i)}))
        // if (shared_queue.tryPush(i))
        {
            std::this_thread::yield();
        }
        ++push_cnt;
    }

    std::cout << "Push count: " << push_cnt << '\n';
}

void consumer()
{

    std::size_t pop_cnt{0};

    for (std::size_t i = 0; i < elem_cnt; ++i)
    {
        Data l_data;
        while (not shared_queue.tryPop(l_data))
        {
            std::this_thread::yield();
        }
        ++pop_cnt;
    }

    std::cout << "Pop count: " << pop_cnt << '\n';
}

int main()
{
    std::jthread l_pth(&producer);
    //std::this_thread::sleep_for(std::chrono::nanoseconds(100));
    std::jthread l_cth(&consumer);

    return 0;
}

/*****
    END OF FILE
**********/
