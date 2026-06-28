/*****

References
    Asynchronous Programming with C++ | Javier Reguera-Salgado & Juan Antonio Rufes
    https://www.boost.org/doc/libs/latest/doc/html/boost_asio/reference/io_context.html
    https://www.boost.org/doc/libs/latest/doc/html/boost_asio.html
    https://www.boost.org/doc/libs/latest/doc/html/boost_asio/overview/core/strands.html
    https://www.boost.org/doc/libs/latest/doc/html/boost_asio/reference/strand.html

Chapter 9 | Asynchronous Programming Using Boost.Asio

Serializing workload with strands

    A strand is a strict sequential and non-concurrent invocation of completion handlers.
    
    Strands can be implicit or explicit.
    
    If we execute boost::asio::io_context::run() from only one thread, 
    all event handlers will execute in an implicit strand

    Another implicit strand happens when there are chained asynchronous operations where one 
    asynchronous operation schedules the next asynchronous operation, and so on.

    We can use explicit strands by using boost::asio::strand or its specialization for 
    I/O context execution objects, boost::asio::io_context::strand. 
    
    Posted work using these strand objects will serialize their handler execution in 
    the order they enter the I/O execution context queue.

**********/

#include <boost/asio.hpp>
#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include <syncstream>

std::osyncstream sync_cout(std::cout);

class Counter {
    int count{0};

    public:
    
    void increment() {
        //sync_cout << "Incrementing from thread: " << std::this_thread::get_id() << '\n';
        ++count;
    }

    auto getCount() const {
        return count;
    }
};

void processWithoutStrand() {

    std::vector<std::thread>    threads;
    boost::asio::io_context l_io_context;
    auto work_guard = boost::asio::make_work_guard(l_io_context);

    auto count_obj = std::make_shared<Counter>();

    for(int i = 0; i < 128; ++i) {

        boost::asio::post(l_io_context, [&]{
            // THIS MIGHT CAUSE DATA RACE AS IT MIGHT BE PROCESSED FROM MULTIPLE THREAD SIMULTANEOUS
            count_obj->increment();
        });

    }

    work_guard.reset();

    for(int i = 0; i < 4; ++i) {
        threads.emplace_back([&l_io_context]{
            l_io_context.run_for(std::chrono::seconds(3));
        });
    }

    for(auto & th: threads) {
        th.join();
    }

    sync_cout << "Counter value in case not using strand : " << count_obj->getCount() << '\n';

}

void processWithStrand() {

    std::vector<std::thread>    threads;
    boost::asio::io_context l_io_context;
    auto work_guard = boost::asio::make_work_guard(l_io_context);

    auto count_obj = std::make_shared<Counter>();


    boost::asio::io_context::strand l_strand{l_io_context};
    for(int i = 0; i < 128; ++i) {

        boost::asio::post(l_strand, [&]{
            // Two handlers associated with the same strand will never execute concurrently.
            // So this will create a data race for shared data
            count_obj->increment();
        });

    }

    work_guard.reset();

    for(int i = 0; i < 4; ++i) {
        threads.emplace_back([&l_io_context]{
            l_io_context.run_for(std::chrono::seconds(3));
        });
    }

    for(auto & th: threads) {
        th.join();
    }

    sync_cout << "Counter value in case using strand : " << count_obj->getCount() << '\n';

}


int main() {

    processWithoutStrand();

    processWithStrand();


    return 0;
}

/*****
    END OF FILE
**********/

