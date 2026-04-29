# Exploring promises and futures

A future is an object that represents some undetermined result that will be completed sometime in the future.

A promise is the provider of that result.

The std::promise and std::future pair implements a one-shot producer-consumer channel with the promise as the producer and the future as the consumer.


## Promises

A promise is a facility to store a result (a value or an exception) that is later acquired asynchronously via a future.

A promise object is only intended to be used once and cannot be
modified afterward.

The promise can update its shared state using the following operations:
- **Make ready:** The promise stores the result in the shared state and makes the state of the promise to become ready unblocking any thread waiting on a future associated with the promise. Remember that the result can be a value (or even void) or an exception.

- **Release:** The promise releases its reference to the shared state, which will be destroyed if this
is the last reference.

- **Abandon:** The promise stores an exception of type std::future_error with error code std::future_errc::broken_promise, making the shared state ready and then releasing it.

When a promise object is deleted, the associated future will still have access to the shared state. If deletion happens after the promise sets the value, the shared state will be in release mode, thus the future can access the result and use it.

set_value() - to store value

set_exception() - to store exception

The result is stored atomically in the promise’s shared state, making its state ready.


set_value_at_thread_exit() and set_exception_at_thread_exit()

The result is stored immediately, but using these new functions, the state is not made ready yet. The state becomes ready when the thread exits after all thread-local variables have been destroyed.


## Futures

It provides access to the result stored by the promise.

The get() method can be used to retrieve the result.

If the shared state is still not ready, this call will block by internally calling wait().

*If for some reason get() is called when valid() is false, the behavior is undefined*

When a future is destroyed, it releases its shared state reference. If that were the last reference, the shared state would be destroyed.

### Future errors and error codes

some functions that deal with asynchronous execution and shared states can throw std::future_error exceptions

Error codes reported by futures are defined by std::future_errorc, a scoped enumeration (enum class)

- **broken_promise:** Reported when a promise is deleted before setting the result, so the shared state is released before being valid.

- **future_already_retrieved:** Occurring when std::promise::get_future()
is called more than once.

- **promise_already_satisfied:** Reported by std::promise:: set_value() if
the shared state already has a stored result.

- **no_state:** Reported when some methods are used but there is no shared state as the promise was created by using the default constructor or moved from.

### Waiting for results

wait(), wait_for(), and wait_until()

These functions must be called only when valid() is true. Otherwise, the behavior is undefined

### Future status

- **Ready:** The shared state is ready, indicating that the result can be retrieved.

- **Deferred:** The shared state contains a deferred function, meaning that the result will only be computed when explicitly requested.

- **Timeout:** The specified timeout period passed before the shared state could become ready.


### Shared futures

std::shared_future is copyable, so several shared future objects can refer to the same shared state.

Shared futures can also be used to signal multiple threads at the same time.


### Packaged tasks

A class template that wraps a callable object to be invoked asynchronously

A packaged task state can also be reset by calling reset().

**make_ready_at_thread_exit()**

To make the result ready only when the thread that runs the packaged task exits and all its thread-local objects are destroyed. This is achieved by using the make_ready_at_thread_exit() function. Even if the result is not ready until the thread exits, it is computed right away as usual. Therefore, its computation is not deferred.


# The benefits and drawbacks of promises and futures

## Benefits

- simplified and less error-prone
- improved performance and reduced execution time
- particularly useful for I/O-bound tasks


## Drawbacks

- deadlocks can happen if there are circular dependencies
- may introduce some performance overhead
- debugging code that uses futures and promises can be more challenging



