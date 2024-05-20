/*****

References
    Anthony Williams - C++ Concurrency in Action

7. Designing lock-free Concurrent Data Structures
==========================================
    The memory-ordering properties of the atomic operations can be used to build lock-free data structures
    You need to take extreme care when designing these data structures, because they’re hard to get right, and the conditions that cause the design to fail may occur very rarely

7.2 Examples of lock-free data structures
==========================================
lock-free data structures rely on the use of atomic operations and the associated memory-ordering guarantees 
in order to ensure that data becomes visible to other threads in the correct order

7.2.2 Managing memory in lock-free data structures
==========================================
in section 7.2.1 pop(), you opted to leak nodes in order to avoid the race condition where 
	one thread deletes a node while another thread still holds a pointer to it that it’s about to dereference

the only threads that can access a given node are the thread that added that node to the stack, and  any threads that call pop()
push() doesn’t touch the node once it’s been added to the stack, so that leaves the threads that call pop()

if you need to handle multiple threads calling pop() on the same stack instance, you need some way to track when it’s safe to delete a node
This means you need to write a special-purpose garbage collector for nodes

If there are no threads calling pop(), it’s perfectly safe to delete all the nodes currently awaiting deletion
If you increment a counter on entry and decrement that counter on exit, 
	it’s safe to delete the nodes from the “to be deleted” list when the counter is zero
It will have to be an atomic counter so it can safely be accessed from multiple threads

Following code has been updated from 7.2.1 to fix memory leak

**********/

#include <iostream>
#include <atomic>
#include <memory>
#include <vector>
#include <thread>
#include <syncstream>

template<typename T>
class lock_free_stack {
    struct Node {
        std::shared_ptr<T>      m_data;
        Node *                  m_next = nullptr;
        
        Node(const T & data) : m_data(std::make_shared<T>(data)) { }
    };
    std::atomic<Node *>     m_head;

    // following private section is to handle memory leak
    std::atomic<unsigned>   m_threads_in_pop;
    std::atomic<Node *>     node_list_to_delete;

    void delete_nodes(Node * nodes) {
        while(nodes) {
            Node * next_node = nodes->m_next;
            delete nodes;
            nodes = nullptr;

            nodes = next_node;
        }
    }

    void chain_pending_nodes(Node * first, Node * last) {
        last->m_next = node_list_to_delete;
        while(not node_list_to_delete.compare_exchange_weak(last->m_next, first));
    }

    void chain_pending_nodes(Node * nodes) {
        Node * last_node = nodes;
        //Node * next_node = nullptr;
        while(Node * const next_node = last_node->m_next) {
            last_node = next_node;
        }
        chain_pending_nodes(nodes, last_node);
    }

    void chain_pending_node(Node * node) {
        chain_pending_nodes(node, node);   
    }

    void try_reclaim(Node * old_head) {

        if(1 == m_threads_in_pop) {
            Node * node_list = node_list_to_delete.exchange(nullptr);

            if(not --m_threads_in_pop) {
                delete_nodes(node_list);
            } else if(node_list) {
                chain_pending_nodes(node_list);
            }

            delete old_head;
            old_head    = nullptr;

        } else {
            chain_pending_node(old_head);
            --m_threads_in_pop;
        }
    }


    public:
    void push(const T & data) {
        auto new_node = new Node(data);
        new_node->m_next = m_head.load();
        while(not m_head.compare_exchange_weak(new_node->m_next, new_node));
    }

    std::shared_ptr<T> pop() {
        ++m_threads_in_pop;
        Node * old_head = m_head.load();
        while(old_head && not m_head.compare_exchange_weak(old_head, old_head->m_next));
        std::shared_ptr<T>  res;
        if(old_head) {
            res.swap(old_head->m_data);   
        }
        try_reclaim(old_head);
        return res;
    }

};


lock_free_stack<std::string> gstack;

void writer(const std::string & data) {
    gstack.push(data);
}

std::osyncstream scout(std::cout);
void reader() {
    auto val = gstack.pop();
    if(val) {
        scout << "Popped value is " << *val << '\n';
    }
}

int main() {

    const std::size_t           count = 10;
    std::vector<std::thread>    threads;

    for(std::size_t i = 0; i < count; ++i) {
        threads.push_back(std::thread(writer, std::string("sample-") + std::to_string(i)));
    }

    for(std::size_t i = 0; i < count; ++i) {
        threads.push_back(std::thread(reader));
    }

    for(auto & th : threads) {
        th.join();
    }

    return 0;
}

/*****
This works reasonably well in low-load situations, where there are suitable quiescent points at which no threads are in pop().
But this is potentially a transient situation, which is why you need to test that the threads_in_pop count decrements to zero 
before doing the reclaim and why this test occurs before you delete the just removed node.

In high-load situations, there may never be this quiescent state, because other threads have entered pop() before all the threads initially in pop() have left.
In such scenarios, the key is to identify when no more threads are accessing a particular node so that it can be reclaimed.
By far the easiest such mechanism to reason about is the use of hazard pointers.
**********/


/*****
    END OF FILE
**********/
 


