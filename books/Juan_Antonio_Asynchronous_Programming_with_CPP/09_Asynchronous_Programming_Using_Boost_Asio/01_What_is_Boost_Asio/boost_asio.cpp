/*****

References
    Asynchronous Programming with C++ | Juan Antonio Rufes
    https://www.boost.org/doc/libs/latest/doc/html/boost_asio/reference/io_context.html
    https://www.boost.org/doc/libs/latest/doc/html/boost_asio.html
    
Chapter 9 | Asynchronous Programming Using Boost.Asio
    
What is Boost Asio

    Boost.Asio is a cross-platform C++ library created by Chris Kohlhoff that provides a portable network and low-level I/O programming, including sockets, timers, hostname resolution, socket iostreams, serial ports, file descriptors, and Windows HANDLEs, providing a consistent asynchronous model.

    It also provides coroutine support

    To deal with asynchronous input/output (I/O) Boost.Asio defines
        OS services: (services belonging to and managed by the OS),
        I/O objects: (providing interfaces to OS services), and the 
        I/O execution context object: (an object that behaves as a services registry and proxy)

I/O objects

    Boost.Asio provides a mechanism composed of I/O objects and I/O execution context objects to access OS services, run asynchronous tasks on them, and collect the results or errors
    The I/O objects do not directly execute their tasks in the OS. They need to communicate with the OS via an I/O execution conext object. An instance of a context object is passed as the first argument in the I/O object constructors.
    Methods whose name starts with async_ trigger asynchronous operations, which will call a completion handler, a callable object passed as an argument to the method when the operation completes.
    I/O objects also provide the blocking counterpart methods, which will block until completion. These methods do not need to receive a handler as a parameter.

I/O execution context objects

    I/O execution context object that represents the gateway to the OS I/O services. It’s implemented with the boost::asio::io_context class, providing the core I/O functionality of OS services to I/O objects.
    boost::asio::io_context is a subclass of boost::asio::execution_context
    When all the asynchronous tasks are scheduled, the program needs to call the boost::asio::io_context::run() function to execute an event processing loop, allowing the OS to deal with the tasks and pass to the program the results and trigger the handlers.
    boost::io_context::run() is a blocking call. This is intended to keep the event loop running, allow the asynchronous operations to run, and prevent the program from exiting.
    the io_context object can run from any thread

    Concurrency hints:

    implementation the number of active threads that should be used for running completion handlers.

    BOOST_ASIO_CONCURRENCY_HINT_SAFE: default value (value 1), io_context object will run from a single thread
    BOOST_ASIO_CONCURRENCY_HINT_UNSAFE: Disables locking so all operations on io_context or I/O objects must occur in the same thread
    BOOST_ASIO_CONCURRENCY_HINT_UNSAFE_IO: Disables locking in the reactor but keeps it in the scheduler, so all operations in the io_context object can use different threads apart from the run() function and the other methods related to executing the event processing loop.

The event processing loop

    Using the boost::asio::io_context::run() method, io_context blocks and keeps processing I/O asynchronous tasks until all have been completed and the completion handlers have been notified.

    There are other methods to control the event loop and avoid blocking until all asynchronous events
    are processed. These are as follows:

    poll: Run the event processing loop to execute ready handlers
    poll_one: Run the event processing loop to execute one ready handler
    run_for: Run the event processing loop for a specified duration
    run_until: Same as the previous one but only until a specified time
    run_one: Run the event processing loop to execute at most one handler
    run_one_for: Same as the previous one but only for a specified duration
    run_one_until: Same as the previous one but only until a specified time

    The event loop can also be stopped by calling the boost::asio::io_context::stop()
    When the event loop is not running, tasks already being scheduled will continue executing. Other tasks will remain pending. Pending tasks can be resumed and pending results collected by starting the event loop with one of the methods mentioned previously again.

    Giving some work to the io_context:

    boost::asio::post()     guarantees that the task will be executed
    boost::asio::dispatch() may execute the task immediately if io_context or strand are in the same thread where the task is being dispatched, or otherwise placed in the queue for asynchronous execution
        using dispatch(), we can optimize performance by reducing context switching or queuing delays

**********/


#include <boost/asio.hpp>
#include <iostream>
#include <chrono>
#include <thread>

int main() {

    boost::asio::io_context l_io_context;

    auto l_io_gurad = boost::asio::make_work_guard(l_io_context);

    std::jthread l_run_th(
        [&]{
            l_io_context.run();
        }
    );

    boost::asio::defer(l_io_context, []{
        std::cout << "Submiting a deferred work to io context\n";
    });

    boost::asio::post(l_io_context, []{
        std::cout << "Posting work to io context\n";
    });

    boost::asio::dispatch(l_io_context, []{
        std::cout << "Dispatching work to io context\n";
    });

    l_io_gurad.reset();     //removes the work guard
    
    return 0;
}

/*****
    END OF FILE
**********/

