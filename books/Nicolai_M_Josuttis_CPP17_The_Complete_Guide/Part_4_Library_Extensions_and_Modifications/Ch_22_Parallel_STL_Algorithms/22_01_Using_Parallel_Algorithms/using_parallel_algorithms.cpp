/**********

References

    C++17 - The Complete Guide | Nicolai M. Josuttis
    https://en.cppreference.com/w/cpp/header/execution

Chapter 22 Parallel STL Algorithms
    
    C++17 allow STL standard algorithms to run 
    using multiple threads to deal with different elements in parallel

22.1 Using Parallel Algorithms

22.1.1 Using a Parallel for_each()

	All parallel algorithms require the iterators to be at least forward iterators

	The way the algorithms run in parallel is implementation specific
	Also using multiple threads might not always be faster, 
    because starting and dealing with multiple threads also takes its time

	The result highly depends on the hardware, C++ compiler, and C++ library used
	The key is, it’s worth with
		• long operations
		• many many elements
	
22.1.2 Using a Parallel sort()
	Because sorting criteria are used way more than once for each element, you can save significant time
	Note that still other modifications might give you more or additional benefits

*************/

#include <iostream>
#include <vector>
#include <execution>
#include <algorithm>
#include <cmath>

#include <string>
#include <chrono>

class Timer {
    std::chrono::steady_clock::time_point m_start;
    std::chrono::steady_clock::time_point m_stop;
    
    public:
    void start()    { m_start = std::chrono::steady_clock::now();   }
    void stop()     { m_stop = std::chrono::steady_clock::now();    }
    
    void display(const std::string& msg = "Timer diff: ") {
        std::chrono::duration<double, std::micro> diff{m_stop - m_start};
        std::cout << msg << diff.count() << "μs\n";
    }
};    

struct Data {
    double  value;
    double  sq_value;
};

int main(const int argc, const char * argv[]) {
    if(2 != argc) { std::cout << "Usage: <binary> num_of_elems\n"; }
    
    const size_t num_of_elems = std::stol(argv[1]);
    std::vector<Data>   data_coll;
    data_coll.reserve(num_of_elems);
    
    for(size_t i = 0; i < num_of_elems; ++i) {
        data_coll.push_back(Data{i*1.2, 0});
    }

    std::cout << "=== Using a Parallel for_each() ===\n";
    Timer bt_time;
    bt_time.start();
    std::for_each(data_coll.begin(), data_coll.end(), 
                [](auto & val){val.sq_value = std::sqrt(val.value);});
    bt_time.stop();
    bt_time.display("Without parallel execution: ");

    bt_time.start();
    std::for_each(std::execution::par, data_coll.begin(), data_coll.end(), 
                [](auto & val){val.sq_value = std::sqrt(val.value);});
    bt_time.stop();
    bt_time.display("With    parallel execution: ");


    std::cout << "\n=== Using a Parallel sort() ===\n";
    std::vector<std::string> str_coll;
    str_coll.reserve(num_of_elems);

    const std::string my_symbol[] = {"+", "-", "*", "#"};
    for(size_t i = 0; i < num_of_elems; ++i) {
        str_coll.push_back("string-" + my_symbol[i%4] + std::to_string(i));
    }    

    bt_time.start();
    std::sort(str_coll.begin(), str_coll.end(), std::less<std::string>{});
    bt_time.stop();
    bt_time.display("Without parallel execution: ");

    bt_time.start();
    std::sort(std::execution::par, str_coll.begin(), str_coll.end(), std::less<std::string>{});
    bt_time.stop();
    bt_time.display("With    parallel execution: ");

    return 0;
}

/**********
    END OF FILE
*************/

