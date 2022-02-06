
# This code is to benchmark various execution policy for comparison

	NOTE:	In real time there was not advantage of using execution policy


#include <benchmark/benchmark.h>
#include <execution>

static void without_parallel(benchmark::State& state) {
        // Perform setup here
        for (auto _ : state) {
                // This code gets timed
                std::vector<uint32_t> lv{1,4,9,53,17,29,23,16,28,36,66,46};
                std::sort(lv.begin(), lv.end());
                benchmark::DoNotOptimize(lv);
        }
}
// Register the function as a benchmark
BENCHMARK(without_parallel);

static void with_seq(benchmark::State& state) {
        // Perform setup here
        for (auto _ : state) {
                // This code gets timed
                std::vector<uint32_t> lv{1,4,9,53,17,29,23,16,28,36,66,46};
                std::sort(std::execution::seq, lv.begin(), lv.end());
                benchmark::DoNotOptimize(lv);
        }
}
// Register the function as a benchmark
BENCHMARK(with_seq);

static void with_parallel(benchmark::State& state) {
        // Perform setup here
        for (auto _ : state) {
                // This code gets timed
                std::vector<uint32_t> lv{1,4,9,53,17,29,23,16,28,36,66,46};
                std::sort(std::execution::par, lv.begin(), lv.end());
                benchmark::DoNotOptimize(lv);
        }
}
// Register the function as a benchmark
BENCHMARK(with_parallel);

static void with_parallel_unseq(benchmark::State& state) {
        // Perform setup here
        for (auto _ : state) {
                // This code gets timed
                std::vector<uint32_t> lv{1,4,9,53,17,29,23,16,28,36,66,46};
                std::sort(std::execution::par_unseq, lv.begin(), lv.end());
                benchmark::DoNotOptimize(lv);
        }
}
// Register the function as a benchmark
BENCHMARK(with_parallel_unseq);

static void with_unseq(benchmark::State& state) {
        // Perform setup here
        for (auto _ : state) {
                // This code gets timed
                std::vector<uint32_t> lv{1,4,9,53,17,29,23,16,28,36,66,46};
                std::sort(std::execution::unseq, lv.begin(), lv.end());
                benchmark::DoNotOptimize(lv);
        }
}
// Register the function as a benchmark
BENCHMARK(with_unseq);



# EOF
