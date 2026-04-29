

# What is std::async?

It is used to run a function asynchronously, allowing the main thread (or other threads) to continue running concurrently.

It immediately returns a future that will hold the value that the function or callable object will compute, as we saw in the previous chapter when using promises and futures.

Its automatic management and lack of control over the thread of execution, among other aspects, can also make it unsuitable for certain tasks where fine-grained control or cancellation is required.


# Launch policies

- **std::launch::async:** The task is executed in a separate thread.

- **std::launch::deferred:** Enables lazy evaluation by executing the task in the calling thread the first time its result is requested via the future get() or wai () method.

*Default launch policy will be std::launch::async | std::launch::deferred.*

# Handling exceptions

Exception propagation from the asynchronous task to the main thread is not supported when using std::async.

To enable exception propagation, we might need a promise object to store the exception that later can be accessed by the future returned when calling std::async. But that promise object is not accessible or provided by std::async.

We could also use nested exceptions, available since C++11, by using std::nested_exception.

## Exceptions when calling std::async

std::async might throw an exception:

- **std::bad_alloc:** If there is not enough memory to store internal data structures needed
by std::async.

- **std:system_error:** If a new thread cannot be started when using std::launch::async as the launch policy. In this case, the error condition will be std::errc::resource_unavailable_try_again.

# Async futures and performance

Futures returned by std::async behave differently from the ones obtained from promises when their destructors are called.

When these futures are destroyed, their ~future destructor is called where the wait() function is executed, causing the thread that was spawned at creation to join.

# Limiting the number of threads

use counting semaphore with initial value set to max number of allowed hardware threads

acquire semaphore and then if resource is available execute the task

# When not to use std::async

async does not provide direct control over the number of threads used or access to the thread objects themselves

automatic management of threads can reduce performance by introducing overhead

