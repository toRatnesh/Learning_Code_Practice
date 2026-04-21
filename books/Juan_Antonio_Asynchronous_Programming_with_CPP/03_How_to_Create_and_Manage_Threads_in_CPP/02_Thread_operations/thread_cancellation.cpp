/*******

References
    Juan Antonio Rufes - Asynchronous Programming with C++
    https://en.cppreference.com/cpp/thread/jthread
    https://en.cppreference.com/cpp/thread/stop_source
    https://en.cppreference.com/cpp/thread/stop_token

**********/

#include <iostream>
#include <string>
#include <thread>
#include <chrono>


int main() {
    
    auto l_run = std::jthread([](const std::stop_token & stop_run){
        while(not stop_run.stop_requested()) {
            
            std::cout << "Thread " << std::this_thread::get_id() << " running ...\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }

        std::cout << "Thread " << std::this_thread::get_id() << " stopping\n";
        return ;        
    });
    
    std::this_thread::sleep_for(std::chrono::seconds(1));
    
    l_run.request_stop();

	return 0;
}

/*****
    END OF FILE
**********/
