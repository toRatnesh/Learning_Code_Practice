
[7. Designing lock-free Concurrent Data Structures](#7-designing-lock-free-concurrent-data-structures)

[7.1 Definitions and consequences](#71-definitions-and-consequences)

[7.1.1 Types of nonblocking data structures](#711-types-of-nonblocking-data-structures)

[7.1.2 Lock-free data structures](#712-lock-free-data-structures)

[7.1.3 Wait-free data structures](#713-wait-free-data-structures)

[7.1.4 The pros and cons of lock-free data structures](#714-the-pros-and-cons-of-lock-free-data-structures)

[References](#references)




# 7. Designing lock-free Concurrent Data Structures

The memory-ordering properties of the atomic operations can be used to build lock-free data structures

You need to take extreme care when designing these data structures, because they’re hard to get right, and the conditions that cause the design to fail may occur very rarely


# 7.1 Definitions and consequences

Algorithms and data structures that use mutexes, condition variables, and futures to synchronize the data are called blocking data structures and algorithms.

Data structures and algorithms that don’t use blocking library functions are said to be nonblocking.
    Not all these data structures are lock-free.


# 7.1.1 Types of nonblocking data structures

We have seen code for a basic mutex using std::atomic_flag as a spin lock

``` cpp
    class spinlock_mutex {
        std::atomic_flag flag;

    public:
        spinlock_mutex() : flag(ATOMIC_FLAG_INIT) {}
        void lock()		{ while (flag.test_and_set(std::memory_order_acquire)); }
        void unlock()	{ flag.clear(std::memory_order_release); }
    };

```


lock() keeps looping until the call to test_and_set() returns false

This is why it gets the name spin lock—the code “spins” around the loop

There are no blocking calls, so any code that uses this mutex to protect shared data is consequently nonblocking.

It’s not lock-free, though.


More specific terms defined:

**Obstruction-Free**

If all other threads are paused, then any given thread will complete its operation in a bounded number of steps.

**Lock-Free**

If multiple threads are operating on a data structure, then after a bounded number of steps one of them will complete its operation.

**Wait-Free**

Every thread operating on a data structure will complete its operation in a bounded number of steps, even if other threads are also operating on the data structure.

Obstruction-free algorithms aren't particularly useful


# 7.1.2 Lock-free data structures

For a data structure to qualify as lock-free, more than one thread must be able to access the data structure concurrently.

They don’t have to be able to do the same operations; a lock-free queue might allow one thread to push and one to pop but break if two threads try to push new items at the same time.

Algorithms that use compare/exchange operations on the data structure often have loops in them.

This code can still be lock-free if the compare/exchange would eventually succeed if the other threads were suspended. 

If it didn’t, you’d have a spin lock, which is nonblocking but not lock-free.

Lock-free algorithms with these loops can result in one thread being subject to starvation.

If another thread performs operations with the “wrong” timing, the other thread might make progress but the first thread continually has to retry its operation.

Data structures that avoid this problem are wait-free as well as lock-free.


# 7.1.3 Wait-free data structures

A wait-free data structure is a lock-free data structure with the additional property that every thread accessing the data structure can complete its operation within a bounded number of steps, regardless of the behavior of other threads.

Algorithms that can involve an unbounded number of retries because of clashes with other threads are not wait-free.

Writing wait-free data structures correctly is extremely hard.


# 7.1.4 The pros and cons of lock-free data structures

With a lock-free data structure, some thread makes progress with every step.

With a wait-free data structure, every thread can make forward progress, regardless of what the other threads are doing; there’s no need for waiting.

This is a desirable property to have but hard to achieve.

If a thread dies while holding a lock, that data structure is broken forever.

But if a thread dies partway through an operation on a lock-free data structure, nothing is lost except that thread’s data; other threads can proceed normally.
        
You must be careful to ensure that the invariants are upheld or choose alternative invariants that can be upheld

All this means that writing thread-safe data structures without using locks is considerably harder than writing them with locks.

Because there aren’t any locks, deadlocks are impossible with lock-free data structures, although there is the possibility of live locks instead.
    
A live lock occurs when two threads each try to change the data structure, but for each thread, the changes made by the other require the operation to be restarted, so both threads loop and try again.

By definition, wait-free code can’t suffer from live lock because  there’s always an upper limit on the number of steps needed to perform an operation. 
    
The flip side here is that the algorithm is likely more complex than the alternative and may require more steps even when no other thread is accessing the data structure.

Another downside of lock-free and wait-free code: it may well decrease overall performance.

First, the atomic operations used for lock-free code can be much slower than nonatomic operations, and there’ll likely be more of them in a lock-free data structure than in the mutex locking code for a lock-based data structure.
        
Not only that, but the hardware must synchronize data between threads that access the same atomic variables. 

As you’ll see in chapter 8, the cache ping-pong associated with multiple threads accessing the same atomic variables can be a significant performance drain.


# References

Anthony Williams - C++ Concurrency in Action

