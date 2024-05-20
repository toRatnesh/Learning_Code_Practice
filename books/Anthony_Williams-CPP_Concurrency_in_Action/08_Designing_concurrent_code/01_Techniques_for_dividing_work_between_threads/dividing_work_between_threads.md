
[8. Designing concurrent code](#8-designing-concurrent-code

[8.1 Techniques for dividing work between threads](##81-techniques-for-dividing-work-between-threads)

[8.1.1 Dividing data between threads before processing begins](###811-dividing-data-between-threads-before-processing-begins)

[8.1.2 Dividing data recursively](###812-dividing-data-recursively)

[8.1.3 Dividing work by task type](###813-dividing-work-by-task-type)

[References](#references)


# 8. Designing concurrent code

Think carefully about the design of concurrent code

Think about the usual factors, such as encapsulation, coupling, and cohesion
also need to consider which data to share, how to synchronize accesses to that data, which threads need to wait for which other threads to complete certain operations, and so on


## 8.1 Techniques for dividing work between threads


You need to decide how many threads to use and what tasks they should be doing

You need to decide whether to have “generalist” threads that do whatever work is necessary at any point in time or “specialist” threads that do one thing well, or some combination

### 8.1.1 Dividing data between threads before processing begins

The simplest means of dividing the data is to allocate the first N elements to one thread, the next N elements to another thread, and so on

No matter how the data is divided, each thread then processes the elements it has been assigned without any communication with the other threads until it has completed its processing

Sometimes the data can’t be divided neatly up front because the necessary divisions become apparent only as the data is processed. This is particularly apparent with recursive algorithms such as Quicksort


### 8.1.2 Dividing data recursively

If you’re sorting a large set of data, spawning a new thread for each recursion would quickly result in a lot of threads

If you have too many threads, you might slow down the application

The idea of dividing the overall task in a recursive fashion like this is a good one; you just need to keep a tighter rein on the number of threads.

std::async() can handle this in simple cases, but it’s not the only choice

One alternative is to use the std::thread::hardware_concurrency() function to choose the number of threads

Both dividing the data before processing begins and dividing it recursively presume that the data itself is fixed beforehand, and you’re looking at ways of dividing it.

This isn’t always the case; if the data is dynamically generated or is coming from external input, this approach doesn’t work. In this case, it might make more sense to divide the work by task type rather than dividing based on the data.


### 8.1.3 Dividing work by task type


An alternative to dividing the work is to make the threads specialists, where each performs a distinct task
Threads may or may not work on the same data, but if they do, it’s for different purposes

**DIVIDING WORK BY TASK TYPE TO SEPARATE CONCERNS**

A single-threaded application has to handle conflicts with the single responsibility principle where there are multiple tasks that need to be run continuously over a period of time, or where the application needs to be able to handle incoming events in a timely fashion, even while other tasks are ongoing.

	
In the single-threaded world you end up manually writing code that performs a bit of task A, a bit of task B
	
If you add too many tasks to the loop, things might slow down too much
	
	
If you run each of the tasks in a separate thread, the operating system handles this for you
	
If everything is independent, and the threads have no need to communicate with each other, then it can be this easy
	


There are two big dangers with separating concerns with multiple threads
	
1. You’ll end up separating the wrong concerns
    The symptoms to check for are that there is a lot of data shared between the threads or the different threads end up waiting for each other
	
2. If two threads are communicating a lot with each other but much less with other threads, maybe they should be combined into a single thread

**DIVIDING A SEQUENCE OF TASKS BETWEEN THREADS**

If your task consists of applying the same sequence of operations to many independent data items, you can use a pipeline to
exploit the available concurrency of your system.

To divide the work this way, you create a separate thread for each stage in the pipeline—one thread for each of the
operations in the sequence.

This is an alternative to dividing the data between threads, as described in section 8.1.1, and is appropriate in
circumstances where the input data itself isn’t all known when the operation is started.


# References

Anthony Williams - C++ Concurrency in Action

