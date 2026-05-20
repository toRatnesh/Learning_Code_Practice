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
