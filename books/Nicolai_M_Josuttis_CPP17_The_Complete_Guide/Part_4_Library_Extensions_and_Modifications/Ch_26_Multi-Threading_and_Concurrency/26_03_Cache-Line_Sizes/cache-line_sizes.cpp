/**********

References

    C++17 - The Complete Guide | Nicolai M. Josuttis
    https://en.cppreference.com/w/cpp/thread/hardware_destructive_interference_size

Chapter 26 Multi-Threading and Concurrency

26.3 Cache-Line Sizes

• On one hand, it is important for concurrency that different objects accessed by different threads don’t belong to the same cache-line. Otherwise the same amount of memory has to be synchronized between different threads when they are accessed concurrently.
• On the other hand, you might have the goal to place multiple objects in the same cache-line so accessing the first object gives direct access to the others instead of loading them in the cache.

C++ standard library introduces two inline variables in header <new>:
	namespace std {
		inline constexpr size_t hardware_destructive_interference_size;
		inline constexpr size_t hardware_constructive_interference_size;
	}
These objects have the following implementation-defined values:
• hardware_destructive_interference_size is the recommended minimum offset between two objects that might be accessed by different threads concurrently to avoid worse performance because the same L1 cache line is affected.
• hardware_constructive_interference_size is the recommended maximum size of contiguous memory within two objects are placed in the same L1 cache line.


you should use them accordingly as follows:
• If you want to access two different (atomic) objects by different threads:
	struct Data {
		alignas(std::hardware_destructive_interference_size) int valueForOneThread;
		alignas(std::hardware_destructive_interference_size) int valueForAnotherThread;
	};
• If you want to access two different (atomic) objects by the same thread:
	struct Data {
		int valueForOneThread;
		int valueForTheSameThread;
	};

// double-check we have best performance due to shared cache-line
static_assert(sizeof(Data) <= std::hardware_constructive_interference_size);

// ensure objects are properly aligned:
alignas(sizeof(Data)) Data myDataForAThread;

*************/


// example code is from
// https://en.cppreference.com/w/cpp/thread/hardware_destructive_interference_size

#include <atomic>
#include <chrono>
#include <cstddef>
#include <iomanip>
#include <iostream>
#include <mutex>
#include <new>
#include <thread>

#ifdef __cpp_lib_hardware_interference_size
    using std::hardware_constructive_interference_size;
    using std::hardware_destructive_interference_size;
#else
    // 64 bytes on x86-64 │ L1_CACHE_BYTES │ L1_CACHE_SHIFT │ __cacheline_aligned │ ...
    constexpr std::size_t hardware_constructive_interference_size = 64;
    constexpr std::size_t hardware_destructive_interference_size = 64;
#endif

std::mutex cout_mutex;
 
constexpr int max_write_iterations{10'000'000}; // the benchmark time tuning
 
struct alignas(hardware_constructive_interference_size)
OneCacheLiner { // occupies one cache line
    std::atomic_uint64_t x{};
    std::atomic_uint64_t y{};
} oneCacheLiner;
 
struct TwoCacheLiner { // occupies two cache lines
    alignas(hardware_destructive_interference_size) std::atomic_uint64_t x{};
    alignas(hardware_destructive_interference_size) std::atomic_uint64_t y{};
} twoCacheLiner;
 
inline auto now() noexcept { return std::chrono::high_resolution_clock::now(); }
 
template<bool xy>
void oneCacheLinerThread() {
    const auto start { now() };
 
    for (uint64_t count{}; count != max_write_iterations; ++count)
        if constexpr (xy)
             oneCacheLiner.x.fetch_add(1, std::memory_order_relaxed);
        else oneCacheLiner.y.fetch_add(1, std::memory_order_relaxed);
 
    const std::chrono::duration<double, std::milli> elapsed { now() - start };
    std::lock_guard lk{cout_mutex};
    std::cout << "oneCacheLinerThread() spent " << elapsed.count() << " ms\n";
    if constexpr (xy) 
        oneCacheLiner.x = elapsed.count();
    else 
        oneCacheLiner.y = elapsed.count();
}
 
template<bool xy>
void twoCacheLinerThread() {
    const auto start { now() };
 
    for (uint64_t count{}; count != max_write_iterations; ++count)
        if constexpr (xy)
             twoCacheLiner.x.fetch_add(1, std::memory_order_relaxed);
        else twoCacheLiner.y.fetch_add(1, std::memory_order_relaxed);
 
    const std::chrono::duration<double, std::milli> elapsed { now() - start };
    std::lock_guard lk{cout_mutex};
    std::cout << "twoCacheLinerThread() spent " << elapsed.count() << " ms\n";
    if constexpr (xy)
        twoCacheLiner.x = elapsed.count();
    else
        twoCacheLiner.y = elapsed.count();
}
 
int main() {
    std::cout << "__cpp_lib_hardware_interference_size "
#   ifdef __cpp_lib_hardware_interference_size
        " = " << __cpp_lib_hardware_interference_size << '\n';
#   else
        "is not defined, use " << hardware_destructive_interference_size << " as fallback\n";
#   endif
 
    std::cout
        << "hardware_destructive_interference_size == "
        << hardware_destructive_interference_size << '\n'
        << "hardware_constructive_interference_size == "
        << hardware_constructive_interference_size << "\n\n";
 
    std::cout
        << std::fixed << std::setprecision(2)
        << "sizeof( OneCacheLiner ) == " << sizeof( OneCacheLiner ) << '\n'
        << "sizeof( TwoCacheLiner ) == " << sizeof( TwoCacheLiner ) << "\n\n";
 
    constexpr int max_runs{4};
 
    uint64_t oneCacheLiner_average{0};
    for (auto i{0}; i != max_runs; ++i) {
        std::thread th1{oneCacheLinerThread<0>};
        std::thread th2{oneCacheLinerThread<1>};
        th1.join(); th2.join();
        oneCacheLiner_average += oneCacheLiner.x + oneCacheLiner.y;
    }
    std::cout << "Average T1 time: " << (oneCacheLiner_average / max_runs / 2) << " ms\n\n";
 
    uint64_t twoCacheLiner_average{0};
    for (auto i{0}; i != max_runs; ++i) {
        std::thread th1{twoCacheLinerThread<0>};
        std::thread th2{twoCacheLinerThread<1>};
        th1.join(); th2.join();
        twoCacheLiner_average += twoCacheLiner.x + twoCacheLiner.y;
    }
    std::cout << "Average T2 time: " << (twoCacheLiner_average / max_runs / 2) << " ms\n\n";
 
    std::cout << "Ratio T1/T2:~ " << 1.0*oneCacheLiner_average/twoCacheLiner_average << '\n';
    
    return 0;
}

/**********
    END OF FILE
*************/


