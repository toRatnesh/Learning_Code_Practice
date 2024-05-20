
[7.3 Guidelines for writing lock-free data structures](#73-guidelines-for-writing-lock-free-data-structures)

[7.3.1 Guideline: use std::memory_order_seq_cst for prototyping](#731-guideline-use-stdmemory_order_seq_cst-for-prototyping)

[7.3.2 Guideline: use a lock-free memory reclamation scheme](#732-guideline-use-a-lock-free-memory-reclamation-scheme)

[7.3.3 Guideline: watch out for the ABA problem](#733-guideline-watch-out-for-the-aba-problem)

[7.3.4 Guideline: identify busy-wait loops and help the other thread](#734-guideline-identify-busy-wait-loops-and-help-the-other-thread)

[References](#references)


# 7. Designing lock-free concurrent data structures

## 7.3 Guidelines for writing lock-free data structures


#### 7.3.1 Guideline: use std::memory_order_seq_cst for prototyping

std::memory_order_seq_cst is much easier to reason about than any other memory ordering because all these operations form a total order

using other memory orderings is an optimization, and as such you need to avoid doing it prematurely you can only determine which operations can be relaxed when you can see the full set of code
	
Attempting to do otherwise makes your life harder

This is complicated by the fact that the code may work when tested but isn’t guaranteed
	
#### 7.3.2 Guideline: use a lock-free memory reclamation scheme

It’s essential to avoid deleting objects when other threads might still have references to them but you still want to delete the object as soon as possible in order to avoid excessive memory consumption
	
Techniques for ensuring that memory can safely be reclaimed:
	
- Waiting until no threads are accessing the data structure and deleting all objects that are pending deletion
- Using hazard pointers to identify that a thread is accessing a particular object
- Reference counting the objects so that they aren’t deleted until there are no outstanding references
	
Another alternative is to recycle nodes and only free them completely when the data structure is destroyed

The downside here is ABA problem
	
#### 7.3.3 Guideline: watch out for the ABA problem

ABA problem:

1. Thread 1 reads an atomic variable, x, and finds it has value A.
2. Thread 1 performs some operation based on this value, such as dereferencing it (if it’s a pointer) or doing a lookup,or something.
3. Thread 1 is stalled by the operating system.
4. Another thread performs some operations on x that change its value to B.
5. A thread then changes the data associated with the value A such that the value held by thread 1 is no longer valid.This may be as drastic as freeing the pointed-to memory or changing an associated value.
6. A thread then changes x back to A based on this new data. If this is a pointer, it may be a new object that happensto share the same address as the old one.
7. Thread 1 resumes and performs a compare/exchange on x, comparing against A. The compare/exchange succeeds (because the value is indeed A), but this is the wrong A value. The data originally read at step 2 is no longer valid, but thread 1 has no way of telling and will corrupt the data structure.

The most common way to avoid this problem is to include an ABA counter alongside the variable x.

The compare/exchange operation is then done on the combined structure of x plus the counter as a single unit.

Every time the value is replaced, the counter is incremented, so even if x has the same value, the compare/exchange will fail if another thread has modified x.

#### 7.3.4 Guideline: identify busy-wait loops and help the other thread

If you end up with a busy-wait loop, you effectively have a blocking operation and might as well use mutexes and locks.

A thread with busy-wait loop, will be wasting CPU time while failing to proceed.
	
By modifying the algorithm so that the waiting thread performs the incomplete steps  if it’s scheduled to run before the original thread completes the operation, you can remove the busy-wait and the operation is no longer blocking.
	
# References

Anthony Williams - C++ Concurrency in Action


