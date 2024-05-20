
[8. Designing concurrent code](#8-designing-concurrent-code)
[8.2 Factors affecting the performance of concurrent code](#8.1-techniques-for-dividing-work-between-threads)
[8.2.1 How many processors?](#8.2.1-dividing-data-between-threads-before-processing-begins)
[8.2.2 Data contention and cache ping-pong](#8.1.2-dividing-data-recursively)
[8.2.3 False sharing](#8.1.3-dividing-work-by-task-type)
[8.2.4 How close is your data?](#824-how-close-is-your-data)
[8.2.5 Oversubscription and excessive task switching](#825-oversubscription-and-excessive-task-switching)
[References](#references)

# 8. Designing concurrent code

Think carefully about the design of concurrent code

Think about the usual factors, such as encapsulation, coupling, and cohesion
also need to consider which data to share, how to synchronize accesses to that data, which threads need to wait for which other threads to complete certain operations, and so on


## 8.2 Factors affecting the performance of concurrent code

If you’re using multiple threads to separate concerns, you need to ensure that this doesn’t adversely affect the performance

Many factors affect the performance of multithreaded code even something as simple as changing which data elements are processed by each thread


### 8.2.1 How many processors?

The number (and structure) of processors is the first big factor that affects the performance of a multithreaded application, and it’s a crucial one.

For example, you might be developing on a dual- or quad-core system, but your customers’ systems may have one multicore processor (with any number of cores), or multiple single-core processors, or even multiple multicore processors. 

The behavior and performance characteristics of a concurrent program can vary considerably under these different circumstances, so you need to think carefully about what the impact may be and test things where possible.

To a first approximation, a single 16-core processor is the same as 4 quad-core processors or 16 single-core processors: in each case the system can run 16 threads concurrently.

**Oversubscription:**

If you have more threads running than the system can run, the situation is called oversubscription.

In the worst-case scenario, if multiple threads call a function that uses std::thread::hardware_concurrency() for scaling at the same time, there will be huge oversubscription. 

std::async() avoids this problem because the library is aware of all calls and can schedule appropriately.

Careful use of thread pools can also avoid this problem.

But even if you take into account all threads running in your application, you’re still subject to the impact of other applications running at the same time.

If you have a massively parallel system with many processing units, an algorithm that performs more operations overall may finish more quickly than one that performs fewer operations, because each processor performs only a few operations.


### 8.2.2 Data contention and cache ping-pong


If one of the threads reading the data, and another modifies the same data, this change then has to propagate to the cache on the other core, which takes time.

In terms of CPU instructions, this can be a phenomenally slow operation, equivalent to many hundreds of individual instructions, although the exact timing depends primarily on the physical structure of the hardware.

**High Contention and Low Contention**

If the processors rarely have to wait for each other, you have low contention
	
If there are too many processors waiting for each other, you have high contention.

Consider the following code:

```cpp

    std::atomic<unsigned long> counter(0);
    void processing_loop() {
    	while(counter.fetch_add(1, std::memory_order_relaxed) < 100000000)	{
    		do_something();
    	}
    }
```

**Cache ping-pong**

In a loop like this one, the data for counter will be passed back and forth between the caches many times. 

This is called cache ping-pong, and it can seriously impact the performance of the application.

**What about mutex locks?**

If you acquire a mutex in a loop, your code is similar to the previous code from the point of view of data accesses.

In order to lock the mutex, another thread must transfer the data that makes up the mutex to its processor and modify it.

When it’s done, it modifies the mutex again to unlock it, and the mutex data has to be transferred to the next thread to acquire the mutex.

This transfer time is in addition to any time that the second thread has to wait for the first to release the mutex.	

Cache ping-pong effects can nullify the benefits of single-writer, multiple-reader mutex if the workload is unfavorable, because all threads accessing the data (even reader threads) still have to modify the mutex itself.


### 8.2.3 False sharing


**Cache lines:**

Processor caches deal in blocks of memory called cache lines.
	
These blocks of memory are typically 32 or 64 bytes in size, but the exact details depend on the particular processor model being used.
	
If a set of data accessed by a thread is in the same cache line, this is better for the performance of the application than if the same set of data was spread over multiple cache lines.

But if the data items in a cache line are unrelated and need to be accessed by different threads, this can be a major cause of performance problems.


**False Sharing:**

False sharing is caused by having data accessed by one thread too close to data accessed by another thread.


**Solution:**

Structure the data so that data items to be accessed by the same thread are close together in memory whereas those that are to be accessed by separate threads are far apart in memory and thus more likely to be in separate cache lines.

The C++17 standard defines std::hardware_destructive_interference_size in the header <new>, which specifies the maximum number of consecutive bytes that may be subject to false sharing for the current compilation target.

If you ensure that your data is at least this number of bytes apart, then there will be no false sharing.


### 8.2.4 How close is your data?

Data proximity:

If the data accessed by a single thread is spread out in memory, it’s likely that it lies on separate cache lines.

Consequently, if data is spread out, more cache lines must be loaded from memory onto the processor cache, which can increase memory access latency and reduce performance compared to data that’s located close together.

Task switching:

If there are more threads than cores in the system, each core is going to be running multiple threads.

Consequently, when the processor switches threads, it’s more likely to have to reload the cache lines if each thread uses data spread across multiple cache lines than if each thread’s data is close together in the same cache line.

If you can fit data that is needed together within std::hardware_constructive_interference_size number of bytes, it will potentially reduce the number of cache misses.

If there are more threads than cores or processors, the operating system might also choose to schedule a thread on one core for one time slice and then on another core for the next time slice.

This will therefore require transferring the cache lines for that thread’s data from the cache for the first core to the cache for the second; the more cache lines that need transferring, the more time-consuming this will be.


### 8.2.5 Oversubscription and excessive task switching

Oversubscription can arise when you have a task that repeatedly spawns new threads without limits.

This isn’t always a good thing. If you have too many additional threads, there will be more threads ready to run than there are available processors, and the operating system will have to start task switching quite heavily in order to ensure they all get a fair time slice.


# References

Anthony Williams - C++ Concurrency in Action

