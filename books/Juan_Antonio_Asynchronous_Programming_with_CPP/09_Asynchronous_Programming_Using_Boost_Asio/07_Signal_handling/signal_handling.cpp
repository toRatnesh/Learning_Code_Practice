/*****

References
    Asynchronous Programming with C++ | Juan Antonio Rufes
    https://www.boost.org/doc/libs/latest/doc/html/boost_asio/reference/io_context.html
    https://www.boost.org/doc/libs/latest/doc/html/boost_asio.html
    https://www.boost.org/doc/libs/latest/doc/html/boost_asio/reference/signal_set.html
    
Chapter 9 | Asynchronous Programming Using Boost.Asio

Signal handling

boost::asio::signal_set class for this purpose, which starts an asynchronous wait for one or more signals to occur
If the application is multithreaded, the signals event handler must run in the same thread as the io_context object, typically being the main thread

**********/

#include <boost/asio.hpp>
#include <iostream>
#include <chrono>
#include <thread>


int main() {

    boost::asio::io_context l_io_context;

    auto l_signal_handler = [&l_io_context]
    (const boost::system::error_code & ec, int signal) {
        if(ec) {
            std::cout << "Error in signal handling, error: " << ec.message() << '\n';
        } else {
            std::cout << "Caught signal " << signal << '\n';
        }

        l_io_context.stop();
    };

    boost::asio::signal_set l_sig_set(l_io_context, SIGINT, SIGTERM, SIGSEGV);
    try {
        l_sig_set.async_wait(l_signal_handler);    
    } catch(const std::exception & exp) {
        std::cout << "Exception: " << exp.what() << '\n';
    } catch(...) {
        std::cout << "Unknown exception\n";
    }
    
    l_io_context.run();

    return 0;
}

/*****
    END OF FILE
**********/

