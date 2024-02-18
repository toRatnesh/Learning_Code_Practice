/*****

References
    Anthony Williams - C++ Concurrency in Action
    https://en.cppreference.com/w/cpp/atomic/atomic
    https://en.cppreference.com/w/cpp/atomic/memory_order

5.3 Synchronizing operations and enforcing ordering
    For two threads, one of which is populating a data structure to be read by the second. 
    In order to avoid a problematic race condition, 
        the first thread sets a flag to indicate that the data is ready, 
        and the second thread doesn’t read the data until the flag is set.

    Example
    std::vector<int> data;
    std::atomic<bool> data_ready(false);

    void reader_thread() {
        while(!data_ready.load()) {
            std::this_thread::sleep(std::chrono::milliseconds(1));
        }
        std::cout<<”The answer=”<<data[0]<<”\n”;
    }

    void writer_thread() {
        data.push_back(42);
        data_ready=true;
    }

    The required enforced ordering comes from the operations on the std::atomic<bool> variable, data_ready;, they provide the necessary ordering by virtue of the memory model relations happens-before and synchronizes-with.
    Because happens-before is transitive, the write to the data happens before the write to the flag, which happens before the read of the true value from the flag, which happens before the read of the data, and you have an enforced ordering.

5.3.3 Memory ordering for atomic operations

There are six ordering options, they represent three models:

1. sequentially consistent ordering
	i.	memory_order_seq_cst
2. acquire-release ordering
	ii.	memory_order_consume,
	iii.memory_order_acquire,
	iv.	memory_order_release,
	v.	memory_order_acq_rel
3. relaxed ordering
	vi.	memory_order_relaxed

Default memory order for all operations on atomic types is
	memory_order_seq_cst

These distinct memory-ordering models can have varying costs on different CPU architectures.
The distinct memory-ordering models allows experts to take advantage of the increased performance
    of the more fine-grained ordering relationships where they’re advantageous


SEQUENTIALLY CONSISTENT ORDERING
->	It implies that the behavior of the program is consistent with a simple sequential view of the world.
->	If all operations on instances of atomic types are sequentially consistent, the behavior of a multithreaded program is as 
    if all these operations were performed in some particular sequence by a single thread.
->  The easiest memory ordering to understand
->  From the point of view of synchronization, a sequentially consistent store synchronizes with 
    a sequentially consistent load of the same variable that reads the value stored.
->  Sequential consistency is the most straightforward and intuitive ordering, 
    but it’s also the most expensive memory ordering because it requires global synchronization between all threads.


NON-SEQUENTIALLY CONSISTENT MEMORY ORDERINGS
->  Single biggest issue
		There’s no longer a single global order of events
		This means that different threads can see different views of the same operations
	
->  It’s not just that the compiler can reorder the instructions
->  Even if the threads are running the same bit of code, they can disagree on the order of events 
    because of operations in other threads in the absence of explicit ordering constraints
->  In the absence of other ordering constraints, the only requirement is that 
    all threads agree on the modification order of each individual variable.


RELAXED ORDERING
->  Operations on atomic types performed with relaxed ordering don’t participate in synchronizes-with relationships.
->  Relaxed operations on different variables can be freely reordered provided 
    they obey any happens-before relationships they’re bound by (for example, within the same thread).


UNDERSTANDING RELAXED ORDERING
->  Its like a list of numbers written on paper.
->  To write down a new value, one writes it at the bottom of the list
->  To get a value from list, one may give you any value from the list he has on his pad at the time
->  If you then ask him for another value, he may give you the same one again or a value from farther down the list. 
    He’ll never give you a value from farther up the list.
->  Relaxed atomic operations must be used in combination with atomic operations 
    that feature stronger ordering semantics in order to be useful for inter-thread synchronization.
	
	NOTE: Avoid relaxed atomic operations unless they’re absolutely necessary


ACQUIRE-RELEASE ORDERING
->  Under this ordering model, 
->  atomic loads are acquire operations (memory_order_acquire), 
->  atomic stores are release operations (memory_order_release), and 
->  atomic read-modify-write operations (such as fetch_add() or exchange()) are either acquire, release, or both (memory_order_acq_rel).
	
->  A release operation synchronizes-with an acquire operation that reads the value written.
->  This means that different threads can still see different orderings, but these orderings are restricted.
	
->  In order to provide any synchronization, acquire and release operations must be paired up.

->  Inter-thread happens-before is transitive: if A inter-thread happens before B and B inter-thread happens before C, then A inter-thread happens before C.
->  This means that acquire-release ordering can be used to synchronize data across several threads, even when the “intermediate” threads haven’t touched the data.

TRANSITIVE SYNCHRONIZATION WITH ACQUIRE-RELEASE ORDERING
->  To see transitive ordering, you need at least three threads, and two shared variables.
->  1st thread modifies 1st shared variable and does a store-release
->  2nd thread then reads the 1st shared variable with a load-acquire and performs a store-release on 2nd shared variable
->  3rd thread does a load-acquire on that 2nd shared variable
->  Provided that the load-acquire operations see the values written by the store-release operations to ensure 
    the synchronizes-with relationships, 3rd thread can read the values of the other variables stored by the 1st thread, 
    even if the intermediate thread didn’t touch any of them


	A fetch_sub operation with memory_order_acquire semantics doesn’t synchronize with anything, even though it stores a value, because it isn’t a release operation.
	Likewise, a store can’t synchronize with a fetch_or with memory_order_release semantics, because the read part of the fetch_or isn’t an acquire operation.
	Read-modify-write operations with memory_order_acq_rel semantics behave as both an acquire and a release, 
        so a prior store can synchronize with such an operation, and it can synchronize with a subsequent load,
	
	If you mix acquire-release operations with sequentially consistent operations, the sequentially consistent 
		loads behave like loads with acquire semantics,
		stores behave like stores with release semantics. 
	Sequentially consistent read-modify-write operations behave as both acquire and release operations.
	Relaxed operations are still relaxed but are bound by the additional synchronizes-with and consequent happens-before relationships 
        introduced through the use of acquire release semantics.
	
	Your acquire and release operations have to be on the same variable to ensure an ordering.
	The pairwise synchronization of acquire-release ordering has the potential for a much lower synchronization cost than 
        the global ordering required for sequentially consistent operations.
	
	
DATA DEPENDENCY WITH ACQUIRE-RELEASE ORDERING AND MEMORY_ORDER_CONSUME
	C++17 standard explicitly recommends that you do not use it.
	
	memory_order_consume introduces the data-dependency nuances to the inter-thread happens-before relationship
	Data dependency: there is a data dependency between two operations if the second one operates on the result of the first.
	two new relations that deal with data dependencies: 
		dependency-ordered-before and 
		carries-a-dependency-to
	
	carries-a-dependency-to
		Like sequenced-before, carries-a-dependency-to applies strictly within a single thread and models the data dependency between operations; 
		if the result of an operation (A) is used as an operand for an operation (B), then A carries a dependency to B.
		
		This operation is also transitive, so if A carries a dependency to B, and B carries a dependency to C, then A carries a dependency to C.
		
	dependency-ordered-before
		can apply between threads
		introduced by using atomic load operations tagged with memory_order_consume
		
		a store operation (A) tagged with memory_order_release, memory_order_acq_rel, or memory_order_seq_cst is dependency-ordered-before a load operation (B) tagged with memory_order_consume if the consume reads the value stored
		
		This operation is also transitive
		
		if A is dependency-ordered-before B, then A also inter-thread happens-before B.
		
		Use for this kind of memory ordering is where the atomic operation loads a pointer to some data
		
		use std::kill_dependency() to explicitly break the dependency chain
		std::kill_dependency() is a simple function template that copies the supplied argument to the return value but breaks the dependency chain in doing so
		
	NOTE:
		In real code, you should always use memory_order_acquire where you might be tempted to use memory_order_consume, and 
		std::kill_dependency is unnecessary


**********/

#include <iostream>
#include <atomic>
#include <thread>
#include <vector>
#include <chrono>
#include <cassert>

std::atomic_int     data;
std::atomic_bool    x_flag;
std::atomic_bool    y_flag;

void set_x_flag() {
    x_flag.store(true, std::memory_order_seq_cst);
}
void set_y_flag() {
    y_flag.store(true, std::memory_order_seq_cst);
}

void read_x_then_y() {
    while(not x_flag.load(std::memory_order_seq_cst)) {}
    if(y_flag.load(std::memory_order_seq_cst))
        ++data;
}
void read_y_then_x() {
    while(not y_flag.load(std::memory_order_seq_cst)) {}
    if(x_flag.load(std::memory_order_seq_cst))
        ++data;
}

int main() {

    x_flag  = false;
    y_flag  = false;
    data    = 0;

    std::thread th_setx(set_x_flag);
    std::thread th_sety(set_y_flag);
    std::thread th_readxy(read_x_then_y);
    std::thread th_readyx(read_y_then_x);
    
    th_setx.join();
    th_sety.join();
    th_readxy.join();
    th_readyx.join();

    assert(data.load() != 0);
    std::cout << "After threads completion data is " << data << '\n';
    
    return 0;
}

/*****
Explanation

The assert can never fire, because either the store to x or the store to y must happen first, even though it’s not specified which.
If the load of y in read_x_then_y returns false, the store to x must occur before the store to y, 
    in which case the load of x in read_y_then_x must return true, because the while loop ensures that the y is true at this point.

**********/

/*****
    END OF FILE
**********/



