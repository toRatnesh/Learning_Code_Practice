/*****
 * 
 **********/

#include <iostream>
#include <mutex>
#include <memory>
#include <vector>
#include <string>
#include <thread>
#include <condition_variable>
#include <syncstream>
#include <vector>
#include <future>
#include <iomanip>

#define VERIFY_PRINT(C) std::cout << "Assertion failed " << std::quoted(C) << '\n';

#define VERIFY(...) if(not(__VA_ARGS__)) { VERIFY_PRINT(#__VA_ARGS__); }


template<typename T>
class ThreadSafeQueue {
    struct  Node
    {
        std::unique_ptr<T>      m_data;
        std::unique_ptr<Node>   m_next;
    };

    std::unique_ptr<Node>       m_head;
    Node *                      m_tail;

    std::mutex                  m_head_mutex;
    std::mutex                  m_tail_mutex;
    
    Node * getTail() {
        const std::lock_guard l_tail_lock{m_tail_mutex};
        return m_tail;
    }

    std::unique_ptr<Node> popHead() {
        const std::lock_guard l_head_lock{m_head_mutex};
        if(m_head.get() == getTail()) {
            return std::unique_ptr<Node>();
        }
        std::unique_ptr<Node> l_old_head = std::move(m_head);
        m_head = std::move(l_old_head->m_next);

        return l_old_head;
    }

    public:

    ThreadSafeQueue() : m_head{std::make_unique<Node>()}, m_tail{m_head.get()} {

    }

    ThreadSafeQueue(const ThreadSafeQueue &)    = delete;
    ThreadSafeQueue & operator=(const ThreadSafeQueue &)    = delete;

    void push(T val) {
        std::unique_ptr<T>      l_data          = std::make_unique<T>(std::move(val));
        std::unique_ptr<Node>   l_dummy_node    = std::make_unique<Node>();
                        Node *  l_new_tail      = l_dummy_node.get();

        {
            const std::lock_guard l_tail_lock{m_tail_mutex};
            m_tail->m_data = std::move(l_data);
            m_tail->m_next = std::move(l_dummy_node);
            m_tail = l_new_tail;
        }
        
        return ;
    }

    std::unique_ptr<T> pop() {
        std::unique_ptr<Node> l_old_head{popHead()};
        return l_old_head ? std::move(l_old_head->m_data) : std::unique_ptr<T>();
    }

    bool empty() {
        const std::lock_guard l_head_lock{m_head_mutex};
        return (m_head.get() == getTail());
    }

    /*  WITHOUT REFACTORING

    std::unique_ptr<T> pop() {
        std::unique_ptr<Node> l_old_head{nullptr};
        {
            const std::lock_guard l_head_lock{m_head_mutex};
            {
                const std::lock_guard l_tail_lock{m_tail_mutex};
                if(m_head.get() == m_tail) {
                    return std::unique_ptr<T>();
                }
            }
            
            l_old_head = std::move(m_head);
            m_head = std::move(l_old_head->m_next);
        }
        return std::move(l_old_head->m_data);
    }
    

    bool empty() {
        const std::lock_guard l_head_lock{m_head_mutex};
        const std::lock_guard l_tail_lock{m_tail_mutex};
        return (m_head.get() == m_tail);
    }    
    */

};


ThreadSafeQueue<int> gqueue;

int reader(const std::size_t count, const bool pop_using_val)
{
    int result = 0;

    for (std::size_t i = 0; i < count; ++i)
    {
            if (pop_using_val)
            {
                const auto val = gqueue.pop();
                //std::cout << "Popped value " << *val << '\n';
                result += (*val);
            }
            /*
            else
            {
                int val = 0;
                gqueue.pop(val);
                //std::cout << "Popped value " << val << '\n';
                result += val;
            }
            */
        
    }

    return result;
}

int writer(int count)
{
    int result = 0;

    for (int i = 0; i < count; ++i)
    {
        gqueue.push(i);

        result += i;
    }

    return result;
}

int main()
{
    constexpr int count = 100;
    int expected_result = 0;

    for (int i = 0; i < count; ++i)
    {
        expected_result += i;
    }
    std::cout << "Expected result is " << expected_result << '\n';

    constexpr int thread_count = 1;


    std::vector<std::future<int>> l_writer_results;
    for (int i = 0; i < thread_count; ++i)
    {
        l_writer_results.push_back(std::async(std::launch::async, writer, count / thread_count));
    }
    l_writer_results.push_back(std::async(std::launch::async, writer, count % thread_count));


    std::vector<std::future<int>> l_reader_results;
    for (int i = 0; i < thread_count; ++i)
    {
        l_reader_results.push_back(std::async(std::launch::async, reader, count / thread_count, true));
    }
    l_reader_results.push_back(std::async(std::launch::async, reader, count % thread_count, false));


    int writer_result = 0;
    for (auto &l_temp_result : l_writer_results)
    {
        writer_result += l_temp_result.get();
    }
    std::cout << "Result from writer is " << writer_result << '\n';

    int reader_result = 0;
    for (auto &l_temp_result : l_reader_results)
    {
        reader_result += l_temp_result.get();
    }

    std::cout << "Result from reader is " << reader_result << '\n';

    VERIFY(reader_result == writer_result);

    return 0;
}

/*****
    END OF FILE
**********/

