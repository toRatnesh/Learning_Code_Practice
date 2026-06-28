/*****

References
    Asynchronous Programming with C++ | Javier Reguera-Salgado & Juan Antonio Rufes
    https://www.boost.org/doc/libs/latest/doc/html/boost_asio/reference/io_context.html
    https://www.boost.org/doc/libs/latest/doc/html/boost_asio.html
    https://www.boost.org/doc/libs/latest/doc/html/boost_asio/overview/core/strands.html
    https://www.boost.org/doc/libs/latest/doc/html/boost_asio/reference/strand.html

Chapter 9 | Asynchronous Programming Using Boost.Asio

Transferring data using buffers

    1. mutable buffers (boost::asio::mutable_buffer), where data can be written,
    2. constant buffers (boost::asio::const_buffers), which are used to create read-only buffers
    
    Mutable buffers can be converted into constant buffers, but not the opposite.
    Both types of buffers provide protection against overruns.

    Also, note that the buffer’s ownership and lifetime are the responsibility of the program, not the Boost.Asio library.

Scatter-gather operations

    Scatter-read is the process of reading data from a unique source into different non-contiguous memory buffers.
    Gather-write is the opposite process; data is gathered from different non-contiguous memory buffers and written into a single destination.

    These techniques increase efficiency and performance as they reduce the number of system calls or data copying.

Stream buffers

    Stream buffers are defined by the boost::asio::basic_streambuf class, 
    based in the std::basic_streambuf C++ class and defined in the <streambuf> header file. 
    
    It allows a dynamic buffer where its size can adapt to the amount of data being transferred.

    If there are no errors, the stream buffers’ commit() function is used to transfer specified bytes to each of the stream buffers

    Stream buffers are useful when the size of the incoming data is variable and unknown in advance.
    These types of buffers can be used together with fixed-sized buffers.

**********/

#include <boost/asio.hpp>
#include <iostream>

constexpr boost::asio::ip::port_type PORT{8099};

class Session : public std::enable_shared_from_this<Session> {
    
    constexpr static size_t BUFSIZE{1024};
    boost::asio::ip::tcp::socket m_socket;

    boost::asio::streambuf buf1, buf2;

    void do_read() {
        auto l_self(shared_from_this());
        
        std::array<boost::asio::mutable_buffer, 2> buffers{ buf1.prepare(BUFSIZE),
                                                            buf2.prepare(BUFSIZE)};

        m_socket.async_read_some(
            buffers,
            [this, l_self](boost::system::error_code ec, size_t length) {
                if (!ec) {

                    auto first = std::min(length, BUFSIZE);
                    auto second = length - first;

                    buf1.commit(first);
                    buf2.commit(second);            

                    do_write();
                }
            });
    }

    void do_write() {
        auto l_self(shared_from_this());

        std::array<boost::asio::const_buffer, 2> buffers{ buf1.data(),
                                                            buf2.data()};

        // boost::asio::async_write(...) which continues calling write_some() internally until everything has been written.
        boost::asio::async_write(
            m_socket,
            buffers,
            [this, l_self](boost::system::error_code ec, size_t length) {
                if (!ec) {

                    auto first = std::min(length, buf1.size());
                    auto second = length - first;

                    buf1.consume(first);
                    buf2.consume(second);   

                    do_read();
                }
            });
    }

   public:
    Session(boost::asio::ip::tcp::socket socket)
        : m_socket(std::move(socket)) {}

    void start() { do_read(); }
};

class EchoServer {
    boost::asio::ip::tcp::acceptor m_acceptor;

    void do_accept() {
        m_acceptor.async_accept([this](boost::system::error_code ec,
                                       boost::asio::ip::tcp::socket socket) {
            if (!ec) {
                std::make_shared<Session>(std::move(socket))->start();
            }
            do_accept();
        });
    }

   public:
    EchoServer(boost::asio::io_context& io_context,
               const boost::asio::ip::port_type port)
        : m_acceptor(io_context, boost::asio::ip::tcp::endpoint(
                                     boost::asio::ip::tcp::v4(), port)) {
        do_accept();
    }
};

int main() {
    try {
        boost::asio::io_context l_io_context;
        EchoServer l_server(l_io_context, PORT);
        l_io_context.run();
    } catch (const std::exception& exp) {
        std::cout << "Exception: " << exp.what() << '\n';
    }

    return 0;
}

/*****
    END OF FILE
**********/
