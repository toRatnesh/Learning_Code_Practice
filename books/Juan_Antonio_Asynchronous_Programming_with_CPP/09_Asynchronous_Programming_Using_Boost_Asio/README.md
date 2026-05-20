# What is Boost Asio

Boost.Asio is a cross-platform C++ library created by Chris Kohlhoff that provides a portable network and low-level I/O programming, including sockets, timers, hostname resolution, socket iostreams, serial ports, file descriptors, and Windows HANDLEs, providing a consistent asynchronous model.

It also provides coroutine support

To deal with asynchronous input/output (I/O) Boost.Asio defines 

**OS services** (services belonging to and managed by the OS),

**I/O objects** (providing interfaces to OS services), and the 

**I/O execution context object** (an object that behaves as a services registry and proxy)

## I/O objects

Boost.Asio provides a mechanism composed of I/O objects and I/O execution context objects to access OS services, run asynchronous tasks on them, and collect the results or errors

The I/O objects do not directly execute their tasks in the OS. They need to communicate with the OS via an I/O execution conext object. An instance of a context object is passed as the first argument in the I/O object constructors.

Methods whose name starts with async_ trigger asynchronous operations, which will call a completion handler, a callable object passed as an argument to the method when the operation completes.

I/O objects also provide the blocking counterpart methods, which will block until completion. These methods do not need to receive a handler as a parameter.

## I/O execution context objects

I/O execution context object that represents the gateway to the OS I/O services. It’s implemented with the boost::asio::io_context class, providing the core I/O functionality of OS services to I/O objects.

boost::asio::io_context is a subclass of boost::asio::execution_context

When all the asynchronous tasks are scheduled, the program needs to call the boost::asio::io_context::run() function to execute an event processing loop, allowing the OS to deal with the tasks and pass to the program the results and trigger the handlers.

boost::io_context::run() is a blocking call. This is intended to keep the event loop running, allow the asynchronous operations to run, and prevent the program from exiting.

the io_context object can run from any thread

### Concurrency hints

implementation the number of active threads that should be used for running completion handlers.

- **BOOST_ASIO_CONCURRENCY_HINT_SAFE** default value (value 1), io_context object will run from a single thread

- **BOOST_ASIO_CONCURRENCY_HINT_UNSAFE** Disables locking so all operations on io_context or I/O objects must occur in the same thread

- **BOOST_ASIO_CONCURRENCY_HINT_UNSAFE_IO** Disables locking in the reactor but keeps it in the scheduler, so all operations in the io_context object can use different threads apart from the run() function and the other methods related to executing the event processing loop.

## The event processing loop

Using the boost::asio::io_context::run() method, io_context blocks and keeps processing I/O asynchronous tasks until all have been completed and the completion handlers have been notified.

There are other methods to control the event loop and avoid blocking until all asynchronous events
are processed. These are as follows:

- **poll:** Run the event processing loop to execute ready handlers
- **poll_one:** Run the event processing loop to execute one ready handler
- **run_for:** Run the event processing loop for a specified duration
- **run_until:** Same as the previous one but only until a specified time
- **run_one:** Run the event processing loop to execute at most one handler
- **run_one_for:** Same as the previous one but only for a specified duration
- **run_one_until:** Same as the previous one but only until a specified time

The event loop can also be stopped by calling the boost::asio::io_context::stop()

When the event loop is not running, tasks already being scheduled will continue executing. Other tasks will remain pending. Pending tasks can be resumed and pending results collected by starting the event loop with one of the methods mentioned previously again.

### Giving some work to the io_context

**boost::asio::post()** guarantees that the task will be executed

**boost::asio::dispatch()** may execute the task immediately if io_context or strand are in the same thread where the task is being dispatched, or otherwise placed in the queue for asynchronous execution

using dispatch(), we can optimize performance by reducing context switching or queuing delays

# Interacting with the OS

## Synchronous operations

create an I/O object and use its synchronous operation method

It returns the result to io_context, which then translates the result, or an error if anything went wrong, back to the I/O object (timer). Errors are of type **boost::system::error_code**. If an error occurs, an exception is thrown.

If we don’t want exceptions to be thrown, we can pass an error object by reference to the synchronous method to capture the status of the operation and check it afterward

## Asynchronous operations

we need to also pass a completion handler to the asynchronous method

the program must execute boost::asio::io_context::run() (or similar functions introduced earlier that manage the event processing loop) and block the current thread while processing any unfinished asynchronous operation

Completion handlers are required to be copy-constructible

### Error handling

two different ways:

1. error codes
2. throwing exceptions

# The Reactor and Proactor design patterns

The Reactor pattern demultiplexes and dispatches synchronously and serially service requests.

Proactor pattern allows demultiplexing and dispatching service requests in an efficient asynchronous way by immediately returning the control to the caller, indicating that the operation has been initiated.

Boost.Asio implements the Proactor design pattern by using the following elements:

- **Initiator:** An I/O object that initiates the asynchronous operation.
- **Asynchronous operation:** A task to run asynchronously by the OS.
- **Asynchronous operation processor:** This executes the asynchronous operation and queues results in the completion event queue.
- **Completion event queue:** An event queue where the asynchronous operation processor pushes events, and the asynchronous event dequeues them.
- **Asynchronous event demultiplexer:** This blocks the I/O context, waiting for events, and returning completed events to the caller.
- **Completion handler:** A callable object that will process the results of the asynchronous operation.
- **Proactor:** This calls the asynchronous event demultiplexer to dequeue events and dispatch them to the completion handler. This is what the I/O execution context does.

The Proactor pattern increases the separation of concerns at the same time as encapsulating concurrency mechanisms, simplifying application synchronization, and increasing performance.

# Threading with Boost Asio

I/O execution context objects are thread-safe

## Single-threaded approach

where the I/O execution context object runs in the same thread where the completion handlers are being processed

When the asynchronous function finishes, its completion handler will run in the same thread

## Threaded long-running tasks

keep the logic in the main thread but use other threads to pass work and get results back to the main thread

a work guard is used to avoid the io_context.run() function to immediately return before any work is posted

If we don’t call io_context.stop(), the event processing loop will continue running forever and the program will not finish, as io_context.run() will continue blocking due to the work guard.

## Multiple I/O execution context objects, one per thread

each thread has its own io_context object and processes short and non-blocking completion handlers

## Multiple threads with a single I/O execution context object

only one io_context object but it is starting the asynchronous tasks from different I/O objects from different threads

In this case, the completion handlers can be called from any of those threads

## Parallelizing work done by one I/O execution context

possible because the io_context object provides a thread-safe event dispatching system

each thread running io_context.run(), making these threads compete to pull tasks from the queue and execute them

One of the threads will pick up the task and execute it

the application better utilizes multiple cores, and reduces latency by handling asynchronous tasks concurrently

the completion handlers also must use synchronization primitives and be thread-safe if they are shared across different threads or modify shared resources

any of them can complete earlier and call its associated completion handler

there might be potential lock contention or context-switching overhead if the thread pool size is not optimal, ideally matching the number of hardware threads

# Managing objects lifetime

## Implementing an echo server – an example

# Transferring data using buffers

## Scatter-gather operations

## Stream buffers

# Signal handling

boost::asio::signal_set class for this purpose, which starts an asynchronous wait for one or more signals to occur

If the application is multithreaded, the signals event handler must run in the same thread as the io_context object, typically being the main thread

# Canceling operations

close() or cancel() methods

If an asynchronous operation is canceled, the completion handler will receive an error with the boost::asio::error::operation_aborted code

But if we want a per-operation cancellation, we need to set up a cancellation slot that will be triggered when a cancellation signal is emitted

Synchronous operations can only be canceled by using the cancel() or close() methods described earlier; they are not supported by the cancellation slots mechanism

various categories of cancellation are as follows:

- None: No cancellation is performed. It can be useful if we want to test if a cancellation should occur.
- Terminal: The operation has unspecified side effects so the only safe way to cancel the operation is to close or destroy the I/O object, being its result final, for example, completing a task or transaction.
- Partial: The operation has well-defined side effects so the completion handler can take the required actions to resolve the issue, meaning that the operation is partially completed and can be resumed or retried.
- Total or All: The operation has no side effects. Cancels both terminal and partial operations, enabling a comprehensive cancellation by stopping all ongoing asynchronous operations.

If the cancellation type is not supported by the asynchronous operation, the cancellation request is discarded

Also, cancellation requests made after the operation is initiated but before it starts, or after its completion, have no effect

# Serializing workload with strands

A strand is a strict sequential and non-concurrent invocation of completion handlers

Strands can be implicit or explicit

if we execute boost::asio::io_context::run() from only one thread, all event handlers will execute in an implicit strand

Another implicit strand happens when there are chained asynchronous operations where one asynchronous operation schedules the next asynchronous operation, and so on

## Implicit Strand

- io_context::run() from only one thread
- one async operation schedules the next async operation

## Explicit Strand

- boost::asio::strand or its specialization for I/O context execution objects
- boost::asio::io_context::strand 

Posted work using these strand objects will serialize their handler execution in the order they enter the I/O execution context queue.





# Coroutines

With newer versions (newer than 1.75.0),

boost::asio::co_spawn 
    to launch a coroutine, and 

boost::asio::use_awaitable
    to let Boost.Asio know that an asynchronous operation will use coroutines

boost::asio::awaitable<R,E>, where 
    R is the return type of the coroutine and 
    E is the exception type that might be thrown

    In this example, E is set as default, so not explicitly specified.

# References

Asynchronous Programming with C++ | Juan Antonio Rufes


