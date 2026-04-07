/*******

References
    Juan Antonio Rufes - Asynchronous Programming with C++
    https://en.cppreference.com/w/cpp/thread/counting_semaphore.html


Thread Safe Ring Buffer:
    Implementing a thread safe ring buffer using std::vector, std::mutex and std::semaphore

***********/

#ifndef RING_BUFFER_HPP
#define RING_BUFFER_HPP

#include <vector>
#include <semaphore>
#include <mutex>

template <typename T, std::size_t CAPACITY = 1>
class RingBuffer
{

    const std::size_t m_capacity;
    std::vector<T> m_buffer;

    std::size_t m_windex{0};
    std::size_t m_rindex{0};

    std::counting_semaphore<> m_empty_count;
    std::counting_semaphore<> m_full_count;

    std::mutex m_buffer_mutex;

public:
    RingBuffer() : m_capacity{CAPACITY},
                   m_buffer(m_capacity),
                   m_empty_count{static_cast<std::ptrdiff_t>(m_capacity)},
                   m_full_count{0} {}

    RingBuffer(const std::size_t capacity) : m_capacity{capacity},
                                             m_buffer(m_capacity),
                                             m_empty_count{static_cast<std::ptrdiff_t>(m_capacity)},
                                             m_full_count{0} {}

    std::size_t next(const std::size_t index) const
    {
        return ((index + 1) % m_capacity);
    }

    bool push(const T &data)
    {
        m_empty_count.acquire();

        std::unique_lock l_lock{m_buffer_mutex};
        m_buffer[m_windex] = data;
        m_windex = next(m_windex);
        l_lock.unlock();

        m_full_count.release();

        return true;
    }

    bool tryPush(const T &data)
    {
        if (m_empty_count.try_acquire())
        {

            std::unique_lock l_lock{m_buffer_mutex};
            m_buffer[m_windex] = data;
            m_windex = next(m_windex);
            l_lock.unlock();

            m_full_count.release();

            return true;
        }

        return false;
    }

    bool pop(T &data)
    {
        m_full_count.acquire();

        std::unique_lock l_lock{m_buffer_mutex};
        data = m_buffer[m_rindex];
        m_rindex = next(m_rindex);
        l_lock.unlock();

        m_empty_count.release();

        return true;
    }

    bool tryPop(T &data)
    {
        if (m_full_count.try_acquire())
        {
            std::unique_lock l_lock{m_buffer_mutex};
            data = m_buffer[m_rindex];
            m_rindex = next(m_rindex);
            l_lock.unlock();

            m_empty_count.release();
            return true;
        }

        return false;
    }
};

#endif

/*******
    END OF FILE
***********/
