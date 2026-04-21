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

