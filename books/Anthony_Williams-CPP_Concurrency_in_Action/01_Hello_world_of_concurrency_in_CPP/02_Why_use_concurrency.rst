
.. contents:: Table of Contents

Hello, world of concurrency in C++
===================================

1.2 Why use concurrency?
--------------------------

Two main reasons:

#. separation of concerns
#. performance

1.2.1 Using concurrency for separation of concerns
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

You can use concurrency to separate distinct areas of functionality, even when the operations in these distinct areas need to happen at the same time.

In this case, the number of threads is independent of the number of CPU cores available, because the division into threads is based on the conceptual design rather than an attempt to increase throughput.

1.2.2 Using concurrency for performance: task and data parallelism
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

There are two ways to use concurrency for performance

#. **Task parallelism:** divide a single task into parts and run each in parallel, reducing the total runtime.
#. **Data parallelism:** each thread performs the same operation on different parts of the data.

Algorithms that are readily susceptible to such parallelism are frequently called embarrassingly parallel.

1.2.3 When not to use concurrency
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

There’s an inherent overhead associated with launching a thread, because the OS has to allocate the associated kernel resources and stack space and then add the new thread to the scheduler, all of which takes time.

So, do not use thread in following situation

- when the benefit isn’t worth the cost
- cost to writing and maintaining multithreaded code, and the additional complexity can also lead to more bugs
- If you have too many threads running at once, this consumes OS resources and may make the system as a whole run slower.
- The more threads you have running, the more context switching the operating system has to do. Each context switch takes time that could be spent doing useful work, so at some point, adding an extra thread will reduce the overall application performance rather than increase it.

If you’re trying to achieve the best possible performance of the system, it’s necessary to adjust the number of threads running to take into account the available hardware concurrency (or lack of it).

References
----------

Book | Anthony Williams - C++ Concurrency in Action





