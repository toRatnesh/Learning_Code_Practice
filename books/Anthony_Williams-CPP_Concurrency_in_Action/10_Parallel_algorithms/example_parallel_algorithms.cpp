/*****

    References
        Anthony Williams - C++ Concurrency in Action

    10.3.1 Examples of using parallel algorithms

    1. Parallel algorithms on a class with internal synchronization
    
        code that can be used with std::execution::par, but not std::execution::par_unseq
        The use of the internal mutex for synchronization means that attempting to use 
        std::execution::par_unseq would be undefined behavior


    2. Parallel algorithms on a class without internal synchronization

        now have no synchronization, and it is safe to use std::execution::par_unseq
        The downside is that concurrent accesses from other threads 
        outside the parallel algorithm invocation must now wait for the entire operation to complete,
        rather than the per-element granularity in case of 1
    
**********/

#include <algorithm>
#include <execution>
#include <iostream>
#include <mutex>
#include <vector>

// Parallel algorithms on a class with internal synchronization
class SyncData {
    int data;
    std::mutex data_mutex;

   public:
    SyncData() : data(1) {}
    int get() {
        std::lock_guard lock(data_mutex);
        return data;
    }
    void operator++() {
        std::lock_guard lock(data_mutex);
        ++data;
    }
};

void increment_all(std::vector<SyncData>& vec) {
    std::for_each(std::execution::par, vec.begin(), vec.end(),
                  [](SyncData& sdata) { ++sdata; });
}

void display_sync_data(std::vector<SyncData>& vec, std::size_t vsize) {
    for (size_t i = 0; i < vsize; ++i) {
        std::cout << vec[i].get() << ' ';
    }
    std::cout << '\n';
}


// Parallel algorithms on a class without internal synchronization
class Data {
    int data;

   public:
    Data() : data(5) {}
    int get() { return data; }
    void operator++() { ++data; }
};

class ProtectedData {
    std::mutex m_mutex;
    std::vector<Data> vec;

    public:
    ProtectedData(std::vector<Data> & vec) : vec(vec) { }
    void lock() {
        m_mutex.lock();
    }
    void unlock() {
        m_mutex.unlock();
    }
    std::vector<Data> & get_vec() {
        return vec;
    }
};

void increment_all(ProtectedData & pdata) {
    std::lock_guard lock(pdata);
    auto & vec = pdata.get_vec();
    std::for_each(std::execution::par, vec.begin(), vec.end(),
                  [](Data& data) { ++data; });
}

void display_data(ProtectedData & pdata, std::size_t vsize) {
    auto & vec = pdata.get_vec();
    for (size_t i = 0; i < vsize; ++i) {
        std::cout << vec[i].get() << ' ';
    }
    std::cout << '\n';
}

int main() {
    {
        std::cout << "=== Parallel algorithms on a class with internal synchronization ===\n";

        std::vector<SyncData> vec{10000};
        display_sync_data(vec, 10);

        increment_all(vec);
        display_sync_data(vec, 10);
    }


    {
        std::cout << "=== Parallel algorithms on a class without internal synchronization ===\n";

        std::vector<Data> vec{10000};
        ProtectedData pdata(vec);
        display_data(pdata, 10);

        increment_all(pdata);
        display_data(pdata, 10);
    }

    return 0;
}

/*****
    END OF FILE
**********/


