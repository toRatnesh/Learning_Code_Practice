
[8. Designing concurrent code](#8-designing-concurrent-code)

[8.4 Additional considerations when designing for concurrency](#84-additional-considerations-when-designing-for-concurrency)

[8.4.1 Exception safety in parallel algorithms](#841-exception-safety-in-parallel-algorithms)

[8.4.2 Scalability and Amdahl’s law](#842-scalability-and-amdahls-law)

[8.4.3 Hiding latency with multiple threads](#843-hiding-latency-with-multiple-threads)

[8.4.4 Improving responsiveness with concurrency](#844-improving-responsiveness-with-concurrency)

[References](#references)



# 8. Designing concurrent code


Think carefully about the design of concurrent code

Think about the usual factors, such as encapsulation, coupling, and cohesion also need to consider which data to share, how to synchronize accesses to that data, which threads need to wait for which other threads to complete certain operations, and so on

## 8.4 Additional considerations when designing for concurrency

Code is said to be scalable if the performance increases as more processing cores are added to the system.


### 8.4.1 Exception safety in parallel algorithms


In a parallel algorithm many of the operations will be running on separate threads. 

In this case, the exception can’t be allowed to propagate because it’s on the wrong call stack.

If a function spawned on a new thread exits with an exception, the application is terminated.

**ADDING EXCEPTION SAFETY**

identify all the possible throw points and the nasty consequences of exceptions

incorporate techniques which can eliminate risk of exception at those points

For example check book and code

**EXCEPTION SAFETY WITH STD::ASYNC()**

with std::async() the library takes care of managing the threads for you, and any threads spawned are completed when the future is ready

exception safety is that if you destroy the future without waiting for it, the destructor will wait for the thread to complete

this neatly avoids the problem of leaked threads that are still executing and holding references to the data


### 8.4.2 Scalability and Amdahl’s law


Scalability is all about ensuring that your application can take advantage of additional processors in the system it’s running on.

**Amdahl’s law**

divide the program into
 
**“serial” sections** where only one thread is doing any useful work and 

**“parallel” sections** where all the available processors are doing useful work

if the “serial” sections constitute a fraction, fs, of the program, then the performance gain, P, from using N processors can be estimated as

P = 1 / fs + ((1-fs) / N) 

This is Amdahl’s law, which is often cited when talking about the performance of concurrent code.


Scalability is about reducing the time it takes to perform an action or increasing the amount of data that can be processed in a given time as more processors are added.

Sometimes these are equivalent (you can process more data if each element is processed faster), but not always.


### 8.4.3 Hiding latency with multiple threads


Depending on the application, it might be possible to use up this spare CPU time without running additional threads. For example, if a thread is blocked because it’s waiting for an I/O operation to complete, it might make sense to use asynchronous I/O if that’s available, and then the thread can perform other useful work while the I/O is performed in the background.


### 8.4.4 Improving responsiveness with concurrency


By separating the concerns with concurrency, you can put the lengthy task on a whole new thread and leave a dedicated thread to process the events. The threads can then communicate through simple mechanisms rather than having to somehow mix the event-handling code in with the task code.



# References

Anthony Williams - C++ Concurrency in Action

