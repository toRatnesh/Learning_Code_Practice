/**********

References

    C++17 - The Complete Guide | Nicolai M. Josuttis
    https://en.cppreference.com/w/cpp/header/execution

Chapter 22 Parallel STL Algorithms
    
    C++17 allow STL standard algorithms to run 
    using multiple threads to deal with different elements in parallel.

22.2 Execution Policies

-------------------------------------------------------------------
Policy						Meaning
-------------------------------------------------------------------
std::execution::seq					 sequential execution
std::execution::par			parallel sequenced execution
std::execution::par_unseq	parallel unsequenced (vectorized) execution
std::execution::unseq				 unsequenced (vectorized) execution
-------------------------------------------------------------------

Sequential execution (seq)
	the current thread of execution sequentially executes the necessary operations element by element
	taking this argument additional constraints might apply, 
    such as for_each() not returning any value or that all iterators have to be at least forward iterators
	parallel algorithms with this policy might behave slightly different than corresponding non-parallel algorithms
	
Parallel sequenced execution (par)
	multiple thread might sequentially execute the necessary operations for the elements
	In contrast to par_unseq this enables to ensure that no problems or deadlocks occur 
    because after processing a step for one element require the call of 
    another step for this element before the same thread performs the first step with another element
	
Parallel unsequenced execution (par_unseq)
	multiple thread might execute the necessary operations for multiple elements without 
    the guarantee that one thread executes all steps for the element without switching to other elements
	enables vectorized execution where a thread might first perform the 
    first step of an execution for multiple elements before it executes the next step
	
Unsequenced execution (unseq) (since C++20)
	single thread executes operations
	execution may be vectorized, e.g., executed on a single thread using instructions that operate on multiple data item

*************/

#include <iostream>
#include <vector>
#include <execution>
#include <algorithm>

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
    Timer bt_time;

    std::cout << "=== Execution Policies ===\n";
    std::vector<std::string> str_coll;
    str_coll.reserve(num_of_elems);

    const std::string my_symbol[] = {"+", "-", "*", "#"};

    {
        str_coll.clear();
        for(size_t i = 0; i < num_of_elems; ++i) {
            str_coll.push_back("string-" + my_symbol[i%4] + std::to_string(i));
        }    
        bt_time.start();
        std::sort(std::execution::seq, str_coll.begin(), str_coll.end(), std::less<std::string>{});
        bt_time.stop();
        bt_time.display("Sequential execution (seq): ");
    }

    {
        str_coll.clear();
        for(size_t i = 0; i < num_of_elems; ++i) {
            str_coll.push_back("string-" + my_symbol[i%4] + std::to_string(i));
        }    
        bt_time.start();
        std::sort(std::execution::par, str_coll.begin(), str_coll.end(), std::less<std::string>{});
        bt_time.stop();
        bt_time.display("Parallel sequenced execution (par): ");
    }

    {
        str_coll.clear();
        for(size_t i = 0; i < num_of_elems; ++i) {
            str_coll.push_back("string-" + my_symbol[i%4] + std::to_string(i));
        }    
        bt_time.start();
        std::sort(std::execution::par_unseq, str_coll.begin(), str_coll.end(), std::less<std::string>{});
        bt_time.stop();
        bt_time.display("Parallel unsequenced execution (par_unseq): ");
    }

    {
        str_coll.clear();
        for(size_t i = 0; i < num_of_elems; ++i) {
            str_coll.push_back("string-" + my_symbol[i%4] + std::to_string(i));
        }    
        bt_time.start();
        std::sort(std::execution::unseq, str_coll.begin(), str_coll.end(), std::less<std::string>{});
        bt_time.stop();
        bt_time.display("Unsequenced execution (unseq): ");
    }

    return 0;
}

/**********
    END OF FILE
*************/

