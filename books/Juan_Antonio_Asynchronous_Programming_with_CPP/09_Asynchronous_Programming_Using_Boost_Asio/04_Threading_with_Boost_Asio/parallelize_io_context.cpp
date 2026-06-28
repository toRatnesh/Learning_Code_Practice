/*****

References
    Asynchronous Programming with C++ | Javier Reguera-Salgado & Juan Antonio Rufes
    https://www.boost.org/doc/libs/latest/doc/html/boost_asio/reference/io_context.html
    https://www.boost.org/doc/libs/latest/doc/html/boost_asio.html

    Code https://godbolt.org/z/6sscv3zr7
    
Chapter 9 | Asynchronous Programming Using Boost.Asio

Threading with Boost Asio

    I/O execution context objects are thread-safe

Single-threaded approach

    where the I/O execution context object runs in the same thread where the completion handlers are being processed
    When the asynchronous function finishes, its completion handler will run in the same thread

Threaded long-running tasks

    keep the logic in the main thread but use other threads to pass work and get results back to the main thread
    a work guard is used to avoid the io_context.run() function to immediately return before any work is posted
    If we don’t call io_context.stop(), the event processing loop will continue running forever and the program will not finish, as io_context.run() will continue blocking due to the work guard.

Multiple I/O execution context objects, one per thread

    each thread has its own io_context object and processes short and non-blocking completion handlers

Multiple threads with a single I/O execution context object

    only one io_context object but it is starting the asynchronous tasks from different I/O objects from different threads
    In this case, the completion handlers can be called from any of those threads

Parallelizing work done by one I/O execution context
    possible because the io_context object provides a thread-safe event dispatching system
    each thread running io_context.run(), making these threads compete to pull tasks from the queue and execute them
    One of the threads will pick up the task and execute it
    the application better utilizes multiple cores, and reduces latency by handling asynchronous tasks concurrently
    the completion handlers also must use synchronization primitives and be thread-safe if they are shared across different threads or modify shared resources
    any of them can complete earlier and call its associated completion handler
    there might be potential lock contention or context-switching overhead if the thread pool size is not optimal, ideally matching the number of hardware threads

**********/

#include <boost/asio.hpp>
#include <iostream>
#include <chrono>
#include <thread>


int main() {

    boost::asio::io_context l_io_context;

    auto l_work_guard = boost::asio::make_work_guard(l_io_context);

    std::vector<std::jthread> threads;
    for(unsigned i = 0; i < std::thread::hardware_concurrency(); ++i) {
        threads.emplace_back(
            [&l_io_context](){ l_io_context.run(); }
        );
    }

    boost::asio::steady_timer l_timer(l_io_context, std::chrono::seconds(2));
    l_timer.async_wait(
        [](const boost::system::error_code ){
            std::cout << "Thread " << std::this_thread::get_id() << " timer expired\n";
        }
    );

    for(int i = 0; i < 5; ++i) {
        boost::asio::dispatch(l_io_context, [i=i](){
            std::cout << "Thread " << std::this_thread::get_id() << " task " << i << " dispatched\n";
        });
    }

    for(int i = 0; i < 5; ++i) {
        boost::asio::post(l_io_context, [i=i](){
            std::cout << "Thread " << std::this_thread::get_id() << " task " << i << " posted\n";
        });
    }

    std::this_thread::sleep_for(std::chrono::seconds(3));
    l_work_guard.reset();

    return 0;
}

/*****
    END OF FILE
**********/

