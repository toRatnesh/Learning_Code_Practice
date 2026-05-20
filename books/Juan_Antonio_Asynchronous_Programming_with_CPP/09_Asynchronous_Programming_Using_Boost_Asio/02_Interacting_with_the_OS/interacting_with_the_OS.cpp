/*****

References
    Asynchronous Programming with C++ | Juan Antonio Rufes
    https://www.boost.org/doc/libs/latest/doc/html/boost_asio/reference/io_context.html
    https://www.boost.org/doc/libs/latest/doc/html/boost_asio.html
    
Chapter 9 | Asynchronous Programming Using Boost.Asio
    
Interacting with the OS

Synchronous operations

    create an I/O object and use its synchronous operation method
    It returns the result to io_context, which then translates the result, or an error if anything went wrong, back to the I/O object (timer). Errors are of type **boost::system::error_code**. If an error occurs, an exception is thrown.
    If we don’t want exceptions to be thrown, we can pass an error object by reference to the synchronous method to capture the status of the operation and check it afterward

Asynchronous operations

    we need to also pass a completion handler to the asynchronous method
    the program must execute boost::asio::io_context::run() (or similar functions introduced earlier that manage the event processing loop) and block the current thread while processing any unfinished asynchronous operation
    Completion handlers are required to be copy-constructible

    Error handling:
        two different ways:

        1. error codes
        2. throwing exceptions

**********/


#include <boost/asio.hpp>
#include <iostream>
#include <chrono>
#include <thread>

int main() {

    boost::asio::io_context l_io_context;
    boost::asio::steady_timer l_timer(l_io_context, std::chrono::seconds(2));

    boost::system::error_code l_err;
    l_timer.wait(l_err);
    if(l_err) {
        std::cout << "Error " << l_err.message() << '\n';
    } else {
        std::cout << "Time out expied in synchronous way\n";
    }

    l_timer.expires_after(std::chrono::seconds(1));
    l_timer.async_wait([](const boost::system::error_code & l_err){
        if(l_err) {
            std::cout << "Error " << l_err.message() << '\n';
        } else {
            std::cout << "Asynchronous timer expied\n";
        }
    });

    l_io_context.run();
    
    return 0;
}


/*****
    END OF FILE
**********/

