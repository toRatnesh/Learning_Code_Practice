/*******

References
    Juan Antonio Rufes - Asynchronous Programming with C++
    https://en.cppreference.com/w/cpp/thread/condition_variable.html


Thread Safe Ring Buffer:
    Implementing a thread safe ring buffer using std::vector, std::mutex and std::condition_variable

***********/

#include <vector>
#include <mutex>
#include <condition_variable>

template <typename T, std::size_t CAPACITY = 1>
class RingBuffer
{

    std::size_t m_capacity{CAPACITY};
    std::vector<T> m_buffer;

    std::size_t m_head{0};
    std::size_t m_tail{0};

    std::mutex m_buffer_mutex;
    std::condition_variable m_not_full_cv;
    std::condition_variable m_not_empty_cv;

public:
    RingBuffer() : m_buffer(m_capacity) {}

    RingBuffer(const std::size_t capacity)
        : m_capacity(capacity), m_buffer(m_capacity) {}

    std::size_t next(const std::size_t index) const
    {
        return (index + 1) % m_capacity;
    }

    bool isFull() const
    {
        //std::cout << "m_tail: " << m_tail << ", next(m_tail): " << next(m_tail) << ", m_head: " << m_head << '\n';

        return next(m_tail) == m_head;
    }

    bool isEmpty() const { return (m_head == m_tail); }

    bool push(const T &data)
    {

        std::unique_lock l_lock(m_buffer_mutex);
        m_not_full_cv.wait(l_lock, [this]
                           { return not isFull(); });

        m_buffer[m_tail] = data;
        m_tail = next(m_tail);

        l_lock.unlock();
        m_not_empty_cv.notify_one();

        return true;
    }

    bool tryPush(const T &data)
    {

        std::unique_lock l_lock(m_buffer_mutex, std::try_to_lock);
        if ((not l_lock) or
            (isFull()))
        {
            return false;
        }

        m_buffer[m_tail] = data;
        m_tail = next(m_tail);

        l_lock.unlock();
        m_not_empty_cv.notify_one();

        return true;
    }

    bool pop(T &data)
    {

        std::unique_lock l_lock(m_buffer_mutex);
        m_not_empty_cv.wait(l_lock, [this]
                            { return not isEmpty(); });

        data = m_buffer[m_head];
        m_head = next(m_head);

        l_lock.unlock();
        m_not_full_cv.notify_one();

        return true;
    }

    bool tryPop(T &data)
    {

        std::unique_lock l_lock(m_buffer_mutex, std::try_to_lock);
        if ((not l_lock) or
            (isEmpty()))
        {
            return false;
        }

        data = m_buffer[m_head];
        m_head = next(m_head);

        l_lock.unlock();
        m_not_full_cv.notify_one();

        return true;
    }

    void displayAllElements() const
    {
        for (const auto &elem : m_buffer)
        {
            std::cout << elem << '\n';
        }
    }
};


/*******
	END OF FILE
***********/

