/*****

References
    Asynchronous Programming with C++ | Javier Reguera-Salgado & Juan Antonio Rufes
    https://www.boost.org/doc/libs/latest/doc/html/boost_asio/reference/io_context.html
    https://www.boost.org/doc/libs/latest/doc/html/boost_asio.html
    https://www.boost.org/doc/libs/latest/doc/html/boost_asio/overview/core/strands.html
    https://www.boost.org/doc/libs/latest/doc/html/boost_asio/reference/strand.html

Chapter 9 | Asynchronous Programming Using Boost.Asio

Managing objects’ lifetime

    One of the main disastrous issues that can happen with asynchronous operations is that, 
    when the operation takes place, some of the required objects have been destroyed.
    Therefore, managing objects’ lifetimes is crucial.

**********/

#include <iostream>
#include <boost/asio.hpp>

constexpr boost::asio::ip::port_type PORT{8099};

class Session : public std::enable_shared_from_this<Session> {
    constexpr static size_t    BUFSIZE{1024};
    char                m_data[BUFSIZE];
    boost::asio::ip::tcp::socket    m_socket;

    void do_read() {
        auto l_self(shared_from_this());

        m_socket.async_read_some(
            boost::asio::buffer(m_data, BUFSIZE),
            [this, l_self](boost::system::error_code ec, size_t length) {
                if(!ec) {
                    do_write(length);
                }
            }
        );
    }

    void do_write(size_t length) {

        auto l_self(shared_from_this());

        boost::asio::async_write(
            m_socket, 
            boost::asio::buffer(m_data, length),
            [this, l_self](boost::system::error_code ec, size_t length) {
                if(!ec) {
                    do_read();
                }
            }
        );
    }

    public:
    Session(boost::asio::ip::tcp::socket socket) 
    : m_socket(std::move(socket)) {

    }

    void start() {
        do_read();
    }

};

class EchoServer {

    boost::asio::ip::tcp::acceptor  m_acceptor;

    void do_accept() {
        m_acceptor.async_accept(
            [this](boost::system::error_code ec, boost::asio::ip::tcp::socket socket) {
                if(!ec) {
                    std::make_shared<Session>(std::move(socket))->start();
                }
                do_accept();
            }
        );
    }

    public:
    EchoServer(boost::asio::io_context & io_context, const boost::asio::ip::port_type port)
    : m_acceptor(io_context, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)) {
        do_accept();
    }
};

int main() {

    try {
        boost::asio::io_context     l_io_context;
        EchoServer                  l_server(l_io_context, PORT);
        l_io_context.run();
    } catch (const std::exception & exp) {
        std::cout << "Exception: " << exp.what() << '\n';
    }

    return 0;
}



/*****
    END OF FILE
**********/

