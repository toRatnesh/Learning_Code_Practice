/*****

References
    Anthony Williams - C++ Concurrency in Action

6. Designing lock-based concurrent data structures
    In this chapter we’ll start by taking the basic building blocks of locks and condition variables and revisit the design of basic data structures

6.3 Designing more complex lock-based data structures
	Not all data structures are that simple; most data structures support a variety of operations. 
	In principle, this can then lead to greater opportunities for concurrency, 
	but it also makes the task of protecting the data that much harder because 
	the multiple access patterns need to be taken into account.

6.3.2 Writing a thread-safe list using locks
    Operations require:
        -> Add
        -> Remove
        -> Find
        -> Update
        -> Copy each item in the list to another container

    The basic idea with fine-grained locking for a linked list is to have one mutex per node.
    The benefit here is that operations on separate parts of the list are truly concurrent: 
    each operation holds only the locks on the nodes it’s interested in and unlocks each node as it moves on to the next

**********/

#include <iostream>
#include <exception>
#include <memory>
#include <string>

#include <thread>
#include <mutex>
#include <syncstream>

#include <vector>
#include <algorithm>

template<typename T>
class thsafe_list {
    struct Node {
        std::shared_ptr<T>      m_data;
        std::unique_ptr<Node>   m_next;
        std::mutex              m_node_mutex;

        Node()  : m_next()  { }
        Node(T val) :   m_data(std::make_shared<T>(val))    { }
    };

    Node    m_head;
    public:
    thsafe_list()       { }
    ~thsafe_list()      { }

    thsafe_list(const thsafe_list & )               = delete;
    thsafe_list& operator=(const thsafe_list & )    = delete;

    void push_front(const T & val) {
        auto new_node   = std::make_unique<Node>(val);

        std::unique_lock   l_head_lock(m_head.m_node_mutex);
        new_node -> m_next  = std::move(m_head.m_next);
        m_head.m_next = std::move(new_node);
    }

    template<typename Predicate>
    std::shared_ptr<T>  find_first_if(Predicate p) {
        Node    * current = &m_head;
        std::unique_lock    l_lock(current->m_node_mutex);
        while(Node * next = current->m_next.get()) {
            std::unique_lock    l_next_lock(next->m_node_mutex);
            l_lock.unlock();
            if(p(*(next->m_data))) {
                return next->m_data;
            }
            else {
                current = next;
                l_lock = std::move(l_next_lock);
            }
        }
        return std::shared_ptr<T>();
    }

    template<typename Predicate>
    void  remove_first_if(Predicate p) {
        Node    * current = &m_head;
        std::unique_lock    l_lock(current->m_node_mutex);
        while(Node * next = current->m_next.get()) {
            std::unique_lock    l_next_lock(next->m_node_mutex);
            if(p(*(next->m_data))) {
                auto l_node_to_remove = std::move(current->m_next);
                current->m_next = std::move(next->m_next);
                l_next_lock.unlock();
            }
            else {
                l_lock.unlock();
                current = next;
                l_lock = std::move(l_next_lock);
            }
        }
    }

    template<typename Function>
    void for_each(Function f) {
        Node * current = &m_head;
        std::unique_lock    l_lock(current->m_node_mutex);
        while(Node * next = current->m_next.get()) {
            std::unique_lock    l_next_lock(next->m_node_mutex);
            l_lock.unlock();

            f(*(next->m_data));

            current = next;
            l_lock = std::move(l_next_lock);

        }
    }


};

std::osyncstream syn_cout(std::cout);

thsafe_list<std::string>    glist;

void push_val(std::size_t count) {
    for(std::size_t i = 0; i < count; ++i) {
        glist.push_front(std::string("sample string ") + std::to_string(i));
    }
}

void remove_val(std::size_t count) {
    for(std::size_t i = 0; i < count; ++i) {
        glist.remove_first_if([i=i](const std::string val){return not(val.compare(std::string("sample string ") + std::to_string(i)));});
    }
}

void find_val(std::size_t count) {
    for(std::size_t i = 0; i < count; ++i) {
        auto val = glist.find_first_if([i=i](const std::string val){return not(val.compare(std::string("sample string ") + std::to_string(i)));});
        if(val) {
            syn_cout << "Value is : " << *val << '\n';
        }
    }
}

void call_for_each() {
    glist.for_each(
        [](std::string  val){ 
            val = val.append(" called for it"); 
            std::cout << val << '\n';
        } 
        );
}


int main() {
    std::vector<std::thread>    vecth;

    const std::size_t count = 20;

    vecth.push_back(std::thread(push_val, count));

    vecth.push_back(std::thread(find_val, count));
    vecth.push_back(std::thread(remove_val, count/2));
    
    vecth.push_back(std::thread(call_for_each));
    vecth.push_back(std::thread(find_val, count));
    
    for(auto & th : vecth) {
        th.join();
    }

    return 0;
}

/*****
Explanation
A default-constructed node is used for the head of the list

New nodes are added with the push_front() function; first a new node is constructed
You then need to acquire the lock on the mutex for the head node in order to get the appropriate next value 
and insert the node at the front of the list by setting head.next to point to your new node
You only need to lock one mutex in order to add a new item to the list, so there’s no risk of deadlock. 
Also, the slow memory allocation happens outside the lock

for_each() operation takes a Function of some type to apply to each element in the list
In this case, the function must accept a value of type T as the sole parameter

find_first_if() is similar to for_each(); the crucial difference is that the
supplied Predicate must return true to indicate a match or false to indicate no match

*****/

/*****
    END OF FILE
**********/

