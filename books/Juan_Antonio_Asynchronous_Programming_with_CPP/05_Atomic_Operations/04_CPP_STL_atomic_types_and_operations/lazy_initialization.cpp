#include <atomic>
#include <iostream>
#include <vector>
#include <thread>

std::atomic<int>    init_done{0};

void init(const int i) {

    const auto l_done = init_done.load(std::memory_order_seq_cst);
    if(not l_done) {
        int expected{0};

        if(init_done.compare_exchange_strong(expected, i, std::memory_order_seq_cst)) {

            const std::string msg = "Initialized by " + std::to_string(i);
            std::puts(msg.c_str());
        }
        else {
            std::puts("Another thread initialzed");
        }
    }
    else {
        std::puts("Already initialized");
    }
}

int main() {

    std::vector<std::jthread> threads;

    for(int i = 0; i < 10; ++i) {
        threads.emplace_back(&init, i);
    }

    return 0;
}


