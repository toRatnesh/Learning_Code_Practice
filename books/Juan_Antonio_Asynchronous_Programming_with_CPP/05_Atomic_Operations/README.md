
Atomic operations can be used in the following cases:

- If multiple threads share a mutable state
- If synchronized access to shared state is fine-grained
- To improve performance

Atomic operations must be provided by the CPU.

Locks can be used in the following cases:

- If the protected data is not fine-grained
- If performance is not an issue
- To avoid the need to acquire low-level knowledge



# blocking data structures

Data structures synchronized with locks are called blocking data structures because threads are blocked (by the operating system), waiting until the locks become available.


# non-blocking data structures

Data structures that don’t use locks are called non-blocking data structures. Most (but not all) of them are lock-free.

A data structure or algorithm is considered lock-free if each synchronized action completes in a finite number of steps, not allowing indefinite waiting for a condition to become true or false.


Types of lock-free data structures:

- Obstruction-free
- Lock-free
- Wait-free


Reasons to use lock-free data structures are the following:

- Achieving maximum concurrency
- No deadlocks
- Performance


# Atomicity

Atomicity is the property that guarantees an operation is executed as a single, indivisible step. In other words, no other thread can observe the operation in a partially completed state.

# Visibility

Visibility refers to when a change made by one thread becomes observable by another thread.

Even if an operation is atomic, there is no guarantee that other threads will immediately see the updated value.

# Ordering
Memory ordering defines the constraints that govern how memory operations are observed across threads.

Modern CPUs and compilers are free to reorder instructions to improve performance. Without explicit constraints, there is no guarantee that operations will be observed in the order they were written in the source code.

C++ provides different memory ordering models through std::atomic operations. Each one defines how operations can be reordered and when changes become visible to other threads.

## Relaxed ordering:

- std::memory_order_relaxed

It guarantees atomicity, but provides no ordering or synchronization between threads.

Use it when operations are completely independent.

Typical use cases:

- counters and statistics
- metrics
- telemetry
- performance tracking

There is no relationship with other variables, so ordering does not matter.

## Acquire and release ordering:

- std::memory_order_acquire
- std::memory_order_release
- std::memory_order_acq_rel
- std::memory_order_consume (deprecated in C++26)

### std::memory_order_acquire

This is used when a thread consumes data.

It ensures that no reads or writes after the load are moved before it.

Use it when:

- a consumer waits for a signal
- then reads data written by another thread

### std::memory_order_release

This is used when a thread publishes data.

It guarantees that all writes before the store become visible before the store itself.

Use it when:

- a producer thread prepares data
- then signals availability

Acquire and Release are meant to be used as a pair.
This establishes a well-defined relationship between threads.
Once the consumer observes the flag, it is guaranteed to see all prior writes from the producer.

### std::memory_order_acq_rel

## Sequential consistency ordering:

- std::memory_order_seq_cst

This is the strongest ordering.

It enforces a single global order of operations across all threads.

Use it when:

- simplicity is more important than performance
- correctness must be guaranteed without subtle reasoning
- debugging or prototyping

*It is also the default ordering in C++.*

# References

Asynchronous Programming with C++ | Juan Antonio Rufes
https://en.cppreference.com/cpp/atomic/memory_order
https://www.linkedin.com/pulse/beyond-atomicity-understanding-visibility-ordering-c-michel-tonetti-aaqwe/

