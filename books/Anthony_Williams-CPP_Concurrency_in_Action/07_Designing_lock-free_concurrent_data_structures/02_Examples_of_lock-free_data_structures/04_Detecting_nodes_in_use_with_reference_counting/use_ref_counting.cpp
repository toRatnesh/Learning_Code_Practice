/*****

References
    Anthony Williams - C++ Concurrency in Action

7. Designing lock-free Concurrent Data Structures
==========================================
    The memory-ordering properties of the atomic operations can be used to build
lock-free data structures You need to take extreme care when designing these
data structures, because they’re hard to get right, and the conditions that
cause the design to fail may occur very rarely

7.2 Examples of lock-free data structures
==========================================
lock-free data structures rely on the use of atomic operations and the
associated memory-ordering guarantees in order to ensure that data becomes
visible to other threads in the correct order

7.2.4 Detecting Nodes in use with reference counting
==========================================

Reference counting tackles the problem by storing a count of the number of
threads accessing each Node.

something like std::shared_ptr<> would be up to the task; after all, it’s a
reference-counted pointer Unfortunately, although some operations on
std::shared_ptr<> are atomic, they aren’t guaranteed to be lock-free

If your platform supplies an implementation for which
std::atomic_is_lock_free(&some_ shared_ptr) returns true, the whole memory
reclamation issue goes away

Not only is it rare for an implementation to provide lock-free atomic operations
on std::shared_ptr<>, but remembering to use the atomic operations consistently
is hard.

Solution for this std::experimental::atomic_shared_ptr<T>

**********/

#include <atomic>
#include <format>
#include <iostream>
#include <memory>
#include <syncstream>
#include <thread>
#include <vector>

template <typename T>
class lf_stack_using_sp {
    struct Node {
        std::shared_ptr<T> data;
#ifdef USE_ASP
        std::atomic<std::shared_ptr<Node>> next = nullptr;
#else
        std::shared_ptr<Node> next = nullptr;
#endif

        Node(const T& data) : data(std::make_shared<T>(data)) {}
    };

#ifdef USE_ASP
    std::atomic<std::shared_ptr<Node>> head;
#else
    std::shared_ptr<Node> head;
#endif

   public:
    static void info() {
        std::cout
            << std::format(
                   "std::atomic<std::shared_ptr<Node>>::is_always_lock_free {}",
                   std::atomic<std::shared_ptr<Node>>::is_always_lock_free)
            << '\n';
    }
    void push(const T& data) {
        auto new_Node = std::make_shared<Node>(data);

#ifdef USE_ASP
        new_Node->next = head.load();
        auto temp = new_Node->next.load();
        while (not head.compare_exchange_weak(temp, new_Node));
#else
        new_Node->next = std::atomic_load(&head);
        while (not std::atomic_compare_exchange_weak(&head, &(new_Node->next),
                                                     new_Node));
#endif
    }

    std::shared_ptr<T> pop() {
#ifdef USE_ASP
        auto old_head = head.load();
        while (old_head &&
               not head.compare_exchange_weak(old_head, old_head->next.load()));
        if (old_head) {
            old_head->next = std::shared_ptr<Node>{};
            return old_head->data;
        }
#else
        auto old_head = std::atomic_load(&head);
        while (old_head &&
               not std::atomic_compare_exchange_weak(
                   &head, &old_head, std::atomic_load(&old_head->next)));
        if (old_head) {
            std::atomic_store(&old_head->next, std::shared_ptr<Node>{});
            return old_head->data;
        }
#endif

        return std::shared_ptr<T>{};
    }

    ~lf_stack_using_sp() { while (pop()); }

    /*
    Not only is it rare for an implementation to provide lock-free atomic
    operations on std::shared_ptr<>, but remembering to use the atomic
    operations consistently is hard.

    Solution for this td::experimental::atomic_shared_ptr<T>
    */
};

lf_stack_using_sp<std::string> gstack;

void writer(const std::string& data) { gstack.push(data); }

std::osyncstream scout(std::cout);
void reader() {
    auto val = gstack.pop();
    if (val) {
        scout << "Popped value is " << *val << '\n';
    }
}

void use_smart_pointer() {
    lf_stack_using_sp<std::string>::info();

    const std::size_t count = 10;
    std::vector<std::thread> threads;

    for (std::size_t i = 0; i < count; ++i) {
        threads.push_back(
            std::thread(writer, std::string("sample-") + std::to_string(i)));
    }

    for (std::size_t i = 0; i < count; ++i) {
        threads.push_back(std::thread(reader));
    }

    for (auto& th : threads) {
        th.join();
    }
}

int main() { 
    use_smart_pointer();
    return 0; 
}

/*****
    END OF FILE
**********/

