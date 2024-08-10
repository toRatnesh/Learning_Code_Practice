.. contents:: Table of Contents


10. Parallel Algorithms
=======================

We’ll look at the parallel algorithms provided by the C++17 standard

10.1 Parallelizing the standard library algorithms
---------------------------------------------------

C++17 standard added the concept of parallel algorithms to the C++ STL

The parallel versions have the same signature as the “normal” single-threaded versions, except for the addition of a new first parameter, which specifies the execution policy to use. 

For example:

.. code:: cpp

	std::vector<int> my_data;
	std::sort(std::execution::par,my_data.begin(),my_data.end());

This is permission, not a requirement—the library may still execute the code on a single thread if it wishes


10.2 Execution policies
------------------------

The standard specifies three execution policies:

- std::execution::sequenced_policy
- std::execution::parallel_policy
- std::execution::parallel_unsequenced_policy

These are classes defined in the <execution> header. 

Corresponding policy objects to pass to the algorithms:

- std::execution::seq
- std::execution::par
- std::execution::par_unseq

You cannot define your own execution policies.


10.2.1 General effects of specifying an execution policy
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Behavior of the algorithm is governed by the execution policy

- The algorithm’s complexity
- The behavior when an exception is thrown
- Where, how, and when the steps of the algorithm are executed

EFFECTS ON ALGORITHM COMPLEXITY
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

If an execution policy is supplied to an algorithm, then that algorithm’s complexity may be changed: in addition to the scheduling overhead of managing the parallel execution, many parallel algorithms will perform more of the core operations of the algorithm, with the intention that this provides an overall improvement in the performance in terms of total elapsed time.


EXCEPTIONAL BEHAVIOR
~~~~~~~~~~~~~~~~~~~~~

All the standard supplied execution policies will call std::terminate if there are any uncaught exceptions. 
The only exception that may be thrown by a call to a STL algorithm with one of the standard execution policies is std::bad_alloc, which is thrown if the library cannot obtain sufficient memory resources for its internal operations.


For example, 
the following call to std::for_each, without an execution policy, will propagate the exception

.. code:: cpp

	std::for_each(v.begin(), v.end(), [](auto x){ throw my_exception(); });

whereas the corresponding call with an execution policy will terminate the program:

.. code:: cpp

	std::for_each(std::execution::seq, v.begin(), v.end(), [](auto x){ throw my_exception(); });

WHERE AND WHEN ALGORITHM STEPS ARE EXECUTED
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

This is the fundamental aspect of an execution policy, and is the only aspect that differs between the standard execution policies.

The policy specifies which execution agents are used to perform the steps of the algorithm, be they “normal” threads, vector streams, GPU threads, or anything else.

The execution policy will also specify whether there are any ordering constraints on how the algorithm steps are run: whether or not they are run in any particular order, whether or not parts of separate algorithm steps may be interleaved with each other, or run in parallel with each other, and so forth.


10.2.2 std::execution::sequenced_policy
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Using it forces the implementation to perform all operations on the thread that called the function, so there is no parallelism

The precise order is unspecified, and may be different between different invocations of the function

The order of execution of the operations is not guaranteed to be the same as that of the corresponding overload without an execution policy

The sequenced policy imposes few requirements on the iterators, values, and callable objects used with the algorithm: they may freely use synchronization mechanisms, and may rely on all operations being invoked on the same thread, though they cannot rely on the order of these operations

10.2.3 std::execution::parallel_policy
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Parallel policy provides basic parallel execution across a number of threads
Operations may be performed either on the thread that invoked the algorithm, or on threads created by the library
iterators, values, and callable objects used with the algorithm they must not cause data races if invoked in parallel, and must not rely on being run on the same thread as any other operation, or indeed rely on not being run on the same thread as any other operation

Incrementing all the values in a vector can be done in parallel:

.. code:: cpp

	std::for_each(std::execution::par,v.begin(),v.end(),[](auto& x){++x;});

Following example of populating a vector is not OK if done with the parallel execution policy; specifically, it is undefined behavior:

.. code:: cpp

	int count=0;
	std::for_each(std::execution::seq,v.begin(),v.end(), [&](int& x){ x=++count; });

Here, the variable count is modified from every invocation of the lambda, so if the library were to execute the lambdas across multiple threads, this would be a data race, and thus undefined behavior.


10.2.4 std::execution::parallel_unsequenced_policy
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

An algorithm invoked with the parallel unsequenced policy may perform the algorithm steps on unspecified threads of execution, unordered and unsequenced with respect to one another.
This means that operations may now be interleaved with each other on a single thread, such that a second operation is started on the same thread before the first has finished, and may be migrated between threads, so a given operation may start on one thread, run further on a second thread, and complete on a third.

If you use the parallel unsequenced policy, then the operations invoked on the iterators, values, and callable objects supplied to the algorithm must not use any form of synchronization or call any function that synchronizes with another, or any function such that some other code synchronizes with it.


10.3 The parallel algorithms from the C++ Standard Library
-----------------------------------------------------------

Most of the algorithms have overloads that take an execution policy. Visit

https://en.cppreference.com/w/cpp/header/numeric

https://en.cppreference.com/w/cpp/header/algorithm

For some algorithms: if the “normal” algorithm allows Input Iterators or Output Iterators, then the overloads with an execution policy require Forward Iterators instead.

This is important for parallelism: it means that the iterators can be freely copied around, and used equivalently.

Also, the requirement that incrementing a Forward Iterator does not invalidate other copies is important, as it means that separate threads can operate on their own copies of the iterators.


10.3.1 Examples of using parallel algorithms
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

With a compiler that supports OpenMP, you might write

.. code:: cpp

	#pragma omp parallel for
	for(unsigned i=0; i< v.size(); ++i){
		do_stuff(v[i]);
	}


With the C++ STL algorithms, you can instead write
std::for_each(std::execution::par, v.begin(), v.end(), do_stuff);

CHOICE OF EXECUTION POLICY
~~~~~~~~~~~~~~~~~~~~~~~~~~

std::execution::par is the policy that you’ll want to use most often

In some circumstances, you may be able to use std::execution::par_unseq instead

This may do nothing at all, but it may give the library additional scope to improve the performance of the code by reordering and interleaving the tasks, in exchange for the tighter requirements on your code

There is no synchronization used in accessing the elements, or performing the operations on the elements

If needed, use external synchronization outside the call to the parallel algorithm to prevent other threads accessing the data.


References
----------

Anthony Williams - C++ Concurrency in Action

