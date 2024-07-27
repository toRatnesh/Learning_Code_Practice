
#ifndef THSAFE_QUEUE
#define THSAFE_QUEUE

#include <condition_variable>
#include <exception>
#include <mutex>
#include <queue>
#include <thread>

template <typename T>
class thsafe_queue {
    struct Node {
        std::shared_ptr<T> m_data;
        std::unique_ptr<Node> m_next;
    };

    std::unique_ptr<Node> m_head;
    Node* m_tail;

    std::mutex m_mutex_head;
    std::mutex m_mutex_tail;
    std::condition_variable m_condv;

    Node* get_tail() {
        const std::lock_guard l_tail_lock(m_mutex_tail);
        return m_tail;
    }

    std::unique_ptr<Node> pop_head() {
        auto l_head = std::move(m_head);
        m_head = std::move(l_head->m_next);
        return l_head;
    }

    std::unique_ptr<Node> try_pop_head() {
        const std::lock_guard l_head_lock(m_mutex_head);
        if (m_head.get() == get_tail()) {
            return std::unique_ptr<Node>();
        }
        return pop_head();
    }

    std::unique_ptr<Node> try_pop_head(T& val) {
        const std::lock_guard l_head_lock(m_mutex_head);
        if (m_head.get() == get_tail()) {
            return std::unique_ptr<Node>();
        }
        val = std::move(*(m_head->m_data));
        return pop_head();
    }

    std::unique_lock<std::mutex> wait_for_data() {
        std::unique_lock l_head_lock(m_mutex_head);
        m_condv.wait(l_head_lock, [&]() { return m_head.get() != get_tail(); });
        return std::move(l_head_lock);
    }

    std::unique_ptr<Node> wait_and_pop_head() {
        std::unique_lock l_head_lock(wait_for_data());
        return pop_head();
    }

    std::unique_ptr<Node> wait_and_pop_head(T& val) {
        std::unique_lock l_head_lock(wait_for_data());
        val = std::move(*(m_head->m_data));
        return pop_head();
    }

   public:
    thsafe_queue() : m_head(std::make_unique<Node>()), m_tail(m_head.get()) {}

    thsafe_queue(const thsafe_queue&) = delete;
    thsafe_queue& operator=(const thsafe_queue&) = delete;

    bool empty() {
        const std::lock_guard l_head_lock(m_mutex_head);
        if (m_head.get() == get_tail()) {
            return true;
        }
        return false;
    }

    void push(T val) {
        auto l_data = std::make_shared<T>(std::move(val));
        auto l_node = std::make_unique<Node>();
        auto l_tail = l_node.get();
        {
            const std::lock_guard l_tail_lock(m_mutex_tail);
            m_tail->m_data = l_data;
            m_tail->m_next = std::move(l_node);
            m_tail = l_tail;
        }
        m_condv.notify_one();
    }

    std::shared_ptr<T> try_pop() {
        /*
        const std::lock_guard       l_head_lock(m_mutex_head);
        if(m_head.get() == get_tail()) {
            std::shared_ptr<T>();
        }
        */

        /*
            auto l_head = std::move(m_head);
            m_head = std::move(l_head->next);
        */

        auto l_head = try_pop_head();
        return l_head ? (l_head->m_data) : std::shared_ptr<T>();
    }

    bool try_pop(T& val) {
        /*
        const std::lock_guard       l_head_lock(m_mutex_head);
        if(m_head.get() == get_tail()) {
            std::shared_ptr<T>();
        }
        */

        // auto l_head = std::move(m_head);
        // m_head = std::move(l_head->next);

        const auto l_head = try_pop_head(val);
        return l_head ? true : false;
    }

    std::shared_ptr<T> wait_and_pop() {
        /*
        const std::unique_lock        l_head_lock(m_mutex_head);
        m_condv.wait(l_head_lock, [&](){return m_head.get() != get_tail();});
        */

        // auto l_head = std::move(m_head);
        // m_head = std::move(l_head->next);

        auto l_head = wait_and_pop_head();
        return l_head->m_data;
    }

    void wait_and_pop(T& val) {
        /*
        const std::unique_lock        l_head_lock(m_mutex_head);
        m_condv.wait(l_head_lock, [&](){return m_head.get() != get_tail();});
        */

        // auto l_head = std::move(m_head);
        // m_head = std::move(l_head->next);

        auto l_head = wait_and_pop_head(val);
        return;
    }
};

#endif


