
.. contents:: Table of Contents

11. Testing and debugging multithreaded applications
====================================================

11.1 Types of concurrency-related bugs
--------------------------------------

Concurrency-related bugs fall into two categories:

#. Unwanted blocking
#. Race conditions

11.1.1 Unwanted blocking
^^^^^^^^^^^^^^^^^^^^^^^^

A thread is blocked when it’s unable to proceed because it’s waiting for something.

why is this blocking unwanted? 

Typically, this is because some other thread is also waiting for the blocked thread to perform some action, and so that thread in turn is blocked.
 
There are several variations on this theme:

Deadlock
~~~~~~~~

One thread is waiting for another, which is in turn waiting for the first

If your threads deadlock, the tasks they’re supposed to be doing won’t get done


Livelock
~~~~~~~~~

One thread is waiting for another, which is in turn waiting for the first

The wait is not a blocking wait but an active checking loop, such as a spin lock
CPU usage is high because threads are still running but blocking each other

In not-so-serious cases, the livelock will eventually resolve because of the random scheduling, but there will be a long delay in the task that got livelocked, with a high CPU usage during that delay.

Blocking on I/O or other external input
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

If your thread is blocked waiting for external input, it can’t proceed, even if the waited-for input is never going to come.

It’s therefore undesirable to block on external input from a thread that also performs tasks that other threads may be waiting for.

11.1.2 Race conditions
^^^^^^^^^^^^^^^^^^^^^^

many concurrency bugs are due to race conditions

many deadlocks and livelocks only manifest because of a race condition

In particular, race conditions often cause the following types of problems:

Data races
~~~~~~~~~~

A race condition that results in undefined behavior because of unsynchronized concurrent access to a shared memory location.

Data races usually occur through incorrect usage of atomic operations to synchronize threads or through access to shared data without locking the appropriate mutex.

Broken invariants
~~~~~~~~~~~~~~~~~

These can manifest as dangling pointers (because another thread deleted the data being accessed), random memory corruption (due to a thread reading inconsistent values resulting from partial updates), and doublefree (such as when two threads pop the same value from a queue, and so both delete some associated data), among others.

If operations on separate threads are required to execute in a particular order, incorrect synchronization can lead to a race condition in which the required order is sometimes violated.

Lifetime issues
~~~~~~~~~~~~~~~

Issue is the thread outlives the data that it accesses, so it is accessing data hat has been deleted or otherwise destroyed

If you manually call join() in order to wait for the thread to complete, you need to ensure that the call to join() can’t be skipped if an exception is thrown. This is basic exception safety applied to threads.



It’s the problematic race conditions that are the killers. With deadlock and livelock, the application appears to hang and become completely unresponsive or takes too long to complete a task.

