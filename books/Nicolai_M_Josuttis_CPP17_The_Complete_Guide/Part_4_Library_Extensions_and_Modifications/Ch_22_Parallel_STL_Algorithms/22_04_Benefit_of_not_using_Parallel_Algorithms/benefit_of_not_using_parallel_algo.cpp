/**********

References

    C++17 - The Complete Guide | Nicolai M. Josuttis
    https://en.cppreference.com/w/cpp/header/execution

Chapter 22 Parallel STL Algorithms
    
    C++17 allow STL standard algorithms to run 
    using multiple threads to deal with different elements in parallel.

22.4 Benefit of not using Parallel Algorithms

	Input and output iterators can be used
	Algorithms do not terminate() on exceptions
	Algorithms may avoid side effects due to an unintended use of elements
	Algorithms might provide additional functionality, such as for_each() 
	returning the passed callable to be able to deal with its resulting state

*************/

#include <iostream>
#include <vector>
#include <execution>
#include <algorithm>

using my_data_t = class MyData {
    int m_data;
    public:
    MyData()                    : m_data{0}     {}
    explicit MyData(int data)   : m_data{data}  {}
    int operator++()        { throw 42; return ++m_data; }
    int operator++(int)     { auto temp = m_data++; return temp; }
};

template<typename T, size_t SIZE>
class MyColl {
    T coll[SIZE];
    size_t  active_i = 0;
    public:
    MyColl()    {}
    auto begin()    { return coll; }
    auto end()      { return coll+SIZE; }
    auto push_back(T val) { coll[active_i] = val; ++active_i; return coll[active_i-1]; }

};

int main(const int argc, const char * argv[]) {

    if(2 != argc) { std::cout << "Usage: <binary> num_of_elems\n"; }
    
    const size_t num_of_elems = std::stol(argv[1]);
    MyColl<my_data_t, 100> coll;
    for(size_t i = 0; i < num_of_elems; ++i) {
        coll.push_back(my_data_t{i % 100});
    }

    try {
        std::cout << "=== Non parallel algorithm ===\n";
        std::for_each(coll.begin(), coll.end(), 
                    [](auto & val){ ++val;});

    } catch (const std::bad_alloc & exp) {
        std::cout << "Exception: " << exp.what() << '\n';
    }
    catch (...) {
        std::cout << "Exception: operation failed due to unknown exception\n";
    } 

    auto fun = std::for_each(coll.begin(), coll.end(), 
                    [](auto & val){ val++;});
    int val = 5;
    std::cout << "value before: " << val << '\n';
    fun(val);
    std::cout << "value after: " << val << '\n';
    
    try {
        std::cout << "\n=== Parallel algorithm ===\n";
        //std::for_each(std::execution::par, coll.begin(), coll.end(), 
        //              [](auto & val){ ++val;});
        std::cout << " causes program termination by calling std::terminate()\n";
    } catch (const std::bad_alloc & exp) {
        std::cout << "Exception: " << exp.what() << '\n';
    }
    catch (...) {
        std::cout << "Exception: sorting failed due to unknown exception\n";
    }

    

    return 0;
}

/**********
    END OF FILE
*************/


