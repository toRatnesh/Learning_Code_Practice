/*****

References
    Juan Antonio Rufes - Asynchronous Programming with C++

**********/

#include <iostream>
#include <thread>

class xTimer {
    std::jthread timer_th;

    public:
    xTimer(const auto duration, const auto callback) {

        timer_th = std::jthread([=](const std::stop_token & stopit){
            while(not stopit.stop_requested()) {
                callback();
                std::this_thread::sleep_for(std::chrono::milliseconds(duration));
            }
        });

    }

    void stop() {
        timer_th.request_stop();
    }

};

int main() {

    xTimer timer_print(std::chrono::seconds(1), [](){
        std::puts("Running using a timer with interval of 1 seconds");
    });

    std::this_thread::sleep_for(std::chrono::seconds(6));

    timer_print.stop();

    std::this_thread::sleep_for(std::chrono::seconds(2));

	return 0;
}

/*****
    END OF FILE
**********/

