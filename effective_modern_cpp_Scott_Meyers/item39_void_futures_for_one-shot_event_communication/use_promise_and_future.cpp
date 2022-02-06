/***********
 
    This example demonstrates the use of promise and future to eliminate the use of condition variable when waiting thread needs to be notified only once.

    Use of promise and future in this case eliminates the use of condition variable and mutex.

 ************/


#include <iostream>
#include <vector>
#include <thread>
#include <future>

std::promise<void> global_prom; 
std::vector<int> global_vec;

int reader() {
    global_prom.get_future().wait();

    for(const auto elem: global_vec) {
        std::clog << elem << ' ';
    }
    std::clog << '\n';
    return 0;
}

int writer() {
    for(const auto elem : {1,2,3,4,5,6,7}) {
        global_vec.push_back(elem);
    }
    global_prom.set_value();

    return 0;
}

int main() {
    std::thread lth_writer(writer);
    std::thread lth_reader(reader);

    lth_writer.join();
    lth_reader.join();

    return 0;
}

/*******
    END OF FILE
 *******/

