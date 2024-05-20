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


7.2.1 Writing a thread-safe stack without locks
==========================================
Stack using linked list; the head pointer identifies the first node (which will be the next to retrieve), and each node then points to the next node in turn.

Pushing a node:
1 Create a new node
2 Set its next pointer to the current head node
3 Set the head node to point to it

if two threads are adding nodes, there’s a race condition between steps 2 and 3: 
a second thread could modify the value of head between when your thread reads it in step 2 and you update it in step 3

use an atomic compare/exchange operation at step 3 to ensure that head hasn’t been modified since you read it in step 2
If it has, you can loop and try again

void push(T const& data) {
	node* const new_node=new node(data);
	new_node->next=head.load();
	while(!head.compare_exchange_weak(new_node->next,new_node));
}

Explanation:
create a new node, set the node’s next pointer to the current head, and set the head pointer to the new node

you use compare_exchange_weak() to ensure that the head pointer still has the same value as you stored in new_node->next, and you set it to new_node if so
if compare/exchange returns false to indicate that the comparison failed (for example, because head was modified by another thread), 
the value supplied as the first parameter (new_node->next) is updated to the current value of head
You therefore don’t have to reload head each time through the loop, because the compiler does that for you
Also, because you’re looping directly on failure, you can use compare_exchange_weak, 
which can result in more optimal code than compare_exchange_strong on some architectures


Poping a node:
1 Read the current value of head
2 Read head->next
3 Set head to head->next
4 Return the data from the retrieved node
5 Delete the retrieved node

Issue:
1.  If there are two threads removing items from the stack, they both might read the same value of head at step 1
	If one thread then proceeds all the way through to step 5 before the other gets to step 2, the second thread will be dereferencing a dangling pointer	
2.	if two threads read the same value of head, they’ll return the same node. This violates the intent of the stack data structure

Solution:
use compare/exchange to update head
If the compare/exchange fails, either a new node has been pushed on or another thread popped the node you were trying to pop
Either way, you need to return to step 1 (although the compare/exchange call rereads head for you)
Once the compare/exchange call succeeds, you know you’re the only thread that’s popping the given node off the stack

void pop(T& result) {
	node* old_head=head.load();
	while(!head.compare_exchange_weak(old_head,old_head->next));
	result=old_head->data;
}


Issue with this implementaion of Stack
1. it doesn’t work on an empty list: if head is a null pointer, it will cause undefined behavior as it tries to read the next pointer
	To fix, check for nullptr in the while loop and either throwing an exception on an empty stack or returning a bool to indicate success or failure.
2. if an exception is thrown when copying the return value, the value is lost
	To fix, use the other option from chapter 3: return a (smart) pointer to the data value
	Returning std::shared_ptr<> won’t throw an exception, so pop() is now safe

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

    public:
    void push(const T & data) {
        auto new_node = new Node(data);
        new_node->m_next = m_head.load();
        while(not m_head.compare_exchange_weak(new_node->m_next, new_node));
    }

    std::shared_ptr<T> pop() {
        Node * old_head = m_head.load();
        while(old_head && not m_head.compare_exchange_weak(old_head, old_head->m_next));
        return old_head ? old_head->m_data : std::shared_ptr<T>{};
        // memory leak
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

    const std::size_t           count = 5;
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
    END OF FILE
**********/
 


