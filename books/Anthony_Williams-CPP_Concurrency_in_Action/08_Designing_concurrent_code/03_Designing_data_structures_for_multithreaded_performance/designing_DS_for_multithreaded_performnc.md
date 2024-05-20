
[8. Designing concurrent code](#8-designing-concurrent-code)

[8.3 Designing data structures for multithreaded performance](#83-designing-data-structures-for-multithreaded-performance)

[8.3.1 Dividing array elements for complex operations](#831-dividing-array-elements-for-complex-operations)

[8.3.2 Data access patterns in other data structures](#832-data-access-patterns-in-other-data-structures)

[References](#references)


# 8. Designing concurrent code

Think carefully about the design of concurrent code

Think about the usual factors, such as encapsulation, coupling, and cohesion also need to consider which data to share, how to synchronize accesses to that data, which threads need to wait for which other threads to complete certain operations, and so on

## 8.3 Designing data structures for multithreaded performance

Key things to consider contention, false sharing, and data proximity


### 8.3.1 Dividing array elements for complex operations


Check book


### 8.3.2 Data access patterns in other data structures


Try to adjust the data distribution between threads so that data that’s close together is worked on by the same thread.

Try to minimize the data required by any given thread.

Try to ensure that data accessed by separate threads is sufficiently far apart to avoid false sharing using std::hardware_destructive_interference_size as a guide.

# References

Anthony Williams - C++ Concurrency in Action

