/**********

References

    C++17 - The Complete Guide | Nicolai M. Josuttis
    https://en.cppreference.com/w/cpp/header/execution

Chapter 22 Parallel STL Algorithms
    
    C++17 allow STL standard algorithms to run 
    using multiple threads to deal with different elements in parallel.

22.3 Exception Handling

	parallel algorithms call std::terminate(), 
    if element access functions exit via an uncaught exception
	parallel algorithms are still might throw
	in case they fail to acquire temporary memory resources for 
    parallel execution they can throw std::bad_alloc
	
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
    bool operator<(const MyData & val2) {
        throw 42;
        return this->m_data < val2.m_data;
    }
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
        std::sort(coll.begin(), coll.end(), 
                [](auto & val1, auto & val2){ return val1 < val2; });
    } catch (const std::bad_alloc & exp) {
        std::cout << "Exception: " << exp.what() << '\n';
    }
    catch (...) {
        std::cout << "Exception: sorting failed due to unknown exception\n";
    } 

    try {
        std::cout << "\n=== Parallel algorithm ===\n";
        std::sort(std::execution::par, coll.begin(), coll.end(), 
                [](auto & val1, auto & val2){ return val1 < val2; });
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


