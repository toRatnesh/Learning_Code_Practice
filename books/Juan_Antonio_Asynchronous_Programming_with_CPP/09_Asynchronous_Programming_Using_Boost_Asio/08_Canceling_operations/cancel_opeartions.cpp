/*****

References
    Asynchronous Programming with C++ | Juan Antonio Rufes
    https://www.boost.org/doc/libs/latest/doc/html/boost_asio/reference/io_context.html
    https://www.boost.org/doc/libs/latest/doc/html/boost_asio.html
    https://www.boost.org/doc/libs/latest/doc/html/boost_asio/reference/cancellation_signal.html
    https://www.boost.org/doc/libs/latest/doc/html/boost_asio/reference/basic_waitable_timer/cancel.html
    
Chapter 9 | Asynchronous Programming Using Boost.Asio

Canceling operations

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

**********/

#include <boost/asio.hpp>
#include <iostream>
#include <chrono>
#include <thread>

int main() {

    boost::asio::io_context l_io_context;
    boost::asio::steady_timer l_timer(l_io_context, std::chrono::seconds(5));

    l_timer.async_wait(
        [](const boost::system::error_code & ec) {
            if(ec && (ec == boost::asio::error::operation_aborted)) {
                std::cout << "timer aborted\n";
            } 
            else if (ec) {
                std::cout << "timer error: " << ec.message() << '\n';
            } else {
                std::cout << "timer expired\n";
            }
        }
    );

    std::this_thread::sleep_for(std::chrono::seconds(2));
    l_timer.cancel();
    
    l_io_context.run();

    return 0;
}

/*****
    END OF FILE
**********/

