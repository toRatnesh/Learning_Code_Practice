
.. contents:: Table of Contents

11. Testing and debugging multithreaded applications
====================================================

11.2 Techniques for locating concurrency-related bugs
-----------------------------------------------------

11.2.1 Reviewing code to locate potential bugs
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

If you get one of your colleagues to review the code, they’ll be coming at it fresh. They’ll therefore see things from a different point of view and may spot things that you can’t.

Also writing detailed notes can be hugely beneficial. As you explain, think about each line, what could happen, which data it accesses, and so forth. Ask yourself questions about the code, and explain the answers.

These questions can be helpful for any code review, not just when reviewing your own code.


**QUESTIONS TO THINK ABOUT WHEN REVIEWING MULTITHREADED CODE**

- Which data needs to be protected from concurrent access?
- How do you ensure that the data is protected?
- Where in the code could other threads be at this time?
- Which mutexes does this thread hold?
- Which mutexes might other threads hold?
- Are there any ordering requirements between the operations done in this thread and those done in another? How are those requirements enforced?
- Is the data loaded by this thread still valid? Could it have been modified by other threads?
- If you assume that another thread could be modifying the data, what would that mean and how could you ensure that this never happens?


11.2.2 Locating concurrency-related bugs by testing
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Testing multithreaded code is an order of magnitude harder, because the precise scheduling of the threads is indeterminate and may vary from run to run.

It’s also worth eliminating the concurrency from the test in order to verify that the problem is concurrency-related.

If you can reduce your application to a single thread, you can eliminate concurrency as a cause. On the flip side, if the problem goes away on a single-core system (even with multiple threads running) but is present on multicore systems or multiprocessor systems, you have a race condition and possibly a synchronization or memory-ordering issue.

There’s more to testing concurrent code than the structure of the code being tested; the structure of the test is just as important, as is the test environment.

**Consider additional factors about the test environment:**

- What you mean by “multiple threads” in each case?
- Whether there are enough processing cores in the system for each thread to run on its own core?
- Which processor architectures the tests should be run on?
- How you ensure suitable scheduling for the “while” parts of your tests?

There are additional factors to think about specific to your particular situation.


11.2.3 Designing for testability
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Code is easier to test if the following factors apply:

- The responsibilities of each function and class are clear
- The functions are short and to the point
- Your tests can take complete control of the environment surrounding the code being tested
- The code that performs the particular operation being tested is close together rather than spread throughout the system
- You thought about how to test the code before you wrote it

If you can break down the code into those parts that are responsible for the communication paths between threads and those parts that operate on the communicated data within a single thread, then you’ve greatly reduced the problem.

Alternatively, if you can divide your code into multiple blocks of read shared data/transform data/update shared data, you can test the transform data portions using all the usual single-threaded techniques, because this is now single-threaded code. The hard problem of testing a multithreaded transformation will be reduced to testing the reading and updating of the shared data, which is much simpler.


11.2.4 Multithreaded testing techniques
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

BRUTE-FORCE TESTING OR STRESS TESTING
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Brute-force testing is to stress the code to see if it breaks.

This typically means running the code many times, possibly with many threads running at once. 

If there’s a bug that manifests only when the threads are scheduled in a particular fashion, then the more times the code is run, the more likely the bug is to appear.

The worst example is where the problematic circumstances can’t occur on your test system because of the way the particular system you’re testing on happens to run.

Different processor architectures provide different synchronization and ordering facilities. For example, on x86 and x86-64 architectures, atomic load operations are always the same, whether tagged memory_order_relaxed or memory_order_seq_cst. This means that code written using relaxed memory ordering may work on systems with an x86 architecture, where it would fail on a system with a finer-grained set of memory-ordering instructions, such as SPARC.


COMBINATION SIMULATION TESTING
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The idea is that you run your code with a special piece of software that simulates the real runtime environment of the code.

The simulation software records the sequences of data accesses, locks, and atomic operations from each thread. It then uses the rules of the C++ memory model to repeat the run with every permitted combination of operations and identify race conditions and deadlocks.

It will take a huge amount of time, because the number of combinations increases exponentially with the number of threads and the number of operations performed by each thread. This technique is best reserved for fine-grained tests of individual pieces of code rather than an entire application.


DETECTING PROBLEMS EXPOSED BY TESTS WITH A SPECIAL LIBRARY
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

You can identify many problems by using a special implementation of the library synchronization primitives such as mutexes, locks, and condition variables.

For example, it’s common to require that all accesses to a piece of shared data be done with a particular mutex locked. By marking your shared data in some way, you can allow the library to check this for you.

This library implementation can also record the sequence of locks if more than one mutex is held by a particular thread at once. If another thread locks the same mutexes in a different order, this could be recorded as a potential deadlock even if the test didn’t deadlock while running.


11.2.5 Structuring multithreaded test code
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

In the most basic case you have two threads, but this could easily be extended to more. 

In the first step, you need to identify the distinct parts of each test:

- The general setup code that must be executed before anything else
- The thread-specific setup code that must run on each thread
- The code for each thread that you want to run concurrently
- The code to be run after the concurrent execution has finished, possibly including assertions on the state of the code

To explain further, let’s consider one thread calling push() on an empty queue while another thread calls pop().

The general setup code is simple: you must create the queue. The thread executing pop() has no thread-specific setup code. The thread-specific setup code for the thread executing push() depends on the interface to the queue and the type of object being stored. If the object being stored is expensive to construct or must be heap-allocated, you want to do this as part of the thread-specific setup, so that it doesn’t affect the test.

In this case, it depends on what you want pop() to do. If it’s supposed to block until there is data, then clearly you want to see that the returned data is what was supplied to the push() call and that the queue is empty afterward. If pop() is not blocking and may complete even when the queue is empty, you need to test for two possibilities: either the pop() returned the data item supplied to the push() and the queue is empty or the pop() signaled that there was no data and the queue has one element. In order to simplify the test, assume you have a blocking pop().

Now, having identified the various chunks of code, you need to do the best you can to ensure that everything runs as planned. One way to do this is to use a set of std::promises to indicate when everything is ready. Each thread sets a promise to indicate that it’s ready and then waits on a (copy of a) std::shared_future obtained from a third std::promise; the main thread waits for all the promises from all the threads to be set and then triggers the threads to go. This ensures that each thread has started and comes before the chunk of code that should be run concurrently; any thread-specific setup should be done before setting that thread’s promise.

.. code:: cpp

	void test_concurrent_push_and_pop_on_empty_queue() {
		threadsafe_queue<int> q;
		std::promise<void> go, push_ready, pop_ready;
		std::shared_future<void> ready(go.get_future());
		std::future<void> push_done;
		std::future<int> pop_done;
		try {
			push_done = std::async(std::launch::async, [&q, ready, &push_ready]() {
				push_ready.set_value();
				ready.wait();
				q.push(42);
			});
			pop_done = std::async(std::launch::async, [&q, ready, &pop_ready]() {
				pop_ready.set_value();
				ready.wait();
				return q.pop();
			});
			push_ready.get_future().wait();
			pop_ready.get_future().wait();
			go.set_value();
			push_done.get();
			assert(pop_done.get() == 42);
			assert(q.empty());
		} catch (...) {
			go.set_value();
			throw;
		}
	}


11.2.6 Testing the performance of multithreaded code
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The particular issue with using concurrency for performance is the scalability—you want code that runs approximately 24 times faster or processes 24 times as much data on a 24-core machine as on a single-core machine, all else being equal.

As you’ve already seen in previous chapters, contention between processors for access to a data structure can have a big performance impact. Something that scales nicely with the number of processors when that number is small may perform badly when the number of processors is much larger because of the huge increase in contention.

