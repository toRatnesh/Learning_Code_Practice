/*******

References
    Juan Antonio Rufes - Asynchronous Programming with C++
    https://en.cppreference.com/w/cpp/thread/call_once.html

std::call_once
    Executes the Callable object f exactly once, even if called concurrently from several threads.

**********/

#include <iostream>
#include <thread>
#include <mutex>
#include <vector>

class Test {

    inline static Test * m_instance{nullptr};
    inline static std::once_flag  m_init_done;

    Test() {
        std::puts("Test()");
    }

    static void init() {
        m_instance = new Test();
    }

    public:

    static Test * getInstance() {
        //init();
        std::call_once(m_init_done, &init);
        return m_instance;
    }

};

int main() {

    std::vector<std::jthread>   threads;

    for(std::size_t i = 0; i < 5; ++i) {
        threads.emplace_back(&Test::getInstance);
    }

    return 0;
}


/*****
    END OF FILE
**********/
