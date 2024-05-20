[6. Designing lock-based concurrent data structures](#6-designing-lock-based-concurrent-data-structures)

[6.1 What does it mean to design for concurrency?](#61-what-does-it-mean-to-design-for-concurrency)

[6.1.1 Guidelines for designing data structures for concurrency](#611-guidelines-for-designing-data-structures-for-concurrency)

# 6. Designing lock-based concurrent data structures

In this chapter we’ll start by taking the basic building blocks of locks and condition variables and revisit the design of basic data structures

## 6.1 What does it mean to design for concurrency?

A data structure is said to be thread-safe

- if multiple threads can access the data structure concurrently, either performing the same or distinct operations, and
- each thread will see a self-consistent view of the data structure
- No data will be lost or corrupted, all invariants will be upheld, and there’ll be no problematic race conditions

**Serialization:**

A mutex protects a data structure by explicitly preventing true concurrent access to the data it protects.

This is called serialization: threads take turns accessing the data protected by the mutex; they must access it serially rather than concurrently.

The smaller the protected region, the fewer operations are serialized, and the greater the potential for concurrency

### 6.1.1 Guidelines for designing data structures for concurrency

Two aspects to consider:

- accesses are safe
- enabling genuine concurrent access

Consideration to make the data structure thread-safe

- Ensure that no thread can see a state where the invariants of the data structure have been broken by the actions of another thread
- Take care to avoid race conditions inherent in the interface
- Pay attention to how the data structure behaves in the presence of exceptions to ensure that the invariants are not broken
- Minimize the opportunities for deadlock

allow concurrent access from multiple threads that merely read the data structure,  whereas a thread that can modify the data structure must have exclusive access

This is supported by using constructs like std::shared_mutex
