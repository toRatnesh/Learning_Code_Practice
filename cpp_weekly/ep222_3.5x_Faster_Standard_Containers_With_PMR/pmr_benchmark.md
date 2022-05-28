#   Run this in https://quick-bench.com/ or any other benchmark tool


#include <array>
#include <vector>
#include <memory_resource>

static void simple_vec(benchmark::State& state) {
    // Code inside this loop is measured repeatedly
    for (auto _ : state) {
        std::vector<int>
            lv{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
    }
}
// Register the function as a benchmark
BENCHMARK(simple_vec);

static void pmr_vec_nobuf(benchmark::State& state) {
    // Code before the loop is not measured
    for (auto _ : state) {
        std::pmr::monotonic_buffer_resource mbr;
        std::pmr::polymorphic_allocator<int> pa{&mbr};
        std::pmr::vector<int>
            lv{{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20},
                pa};
    }
}
BENCHMARK(pmr_vec_nobuf);


static void pmr_vec_buf(benchmark::State& state) {
    // Code before the loop is not measured
    for (auto _ : state) {
        std::byte buffer[20 * sizeof(int)];
        std::pmr::monotonic_buffer_resource mbr{buffer,
            sizeof(buffer)};
        std::pmr::polymorphic_allocator<int> pa{&mbr};
        std::pmr::vector<int>
            lv{{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20},
                pa};
    }
}
BENCHMARK(pmr_vec_buf);

#   END OF FILE

