/*****

References

    Asynchronous Programming with C++ | Javier Reguera-Salgado & Juan Antonio Rufes
    https://en.cppreference.com/cpp/thread/async
    code: https://godbolt.org/z/9xbejGY6E

Performance measurement tools

Code micro-benchmarks:
    we can use a benchmark (also called a micro-benchmark) library 
    to do just that – execute small parts of our code in different conditions

    The benchmark::State parameter has a dual purpose:

    1. Controlling the iteration loop: to control how many times a benchmarked function or piece of code should be executed
    2. Measuring time and statistics: keeps track of how long the benchmarked code takes to run, and it provides mechanisms 
        to report metrics such as elapsed time, iterations, and custom counters to tell the library that they must be run as a benchmark

        BENCHMARK(BM_vector_push_back)->Range(1, 1000);

    BENCHMARK_CAPTURE macro: This macro allows us to pass parameters to our benchmark functions

        BENCHMARK_CAPTURE(BM_vector_sort, vector, rv1)->Iterations(1)->Unit(benchmark::kMillisecond);

**********/

#include <benchmark/benchmark.h>

#include <iostream>
#include <vector>

void BM_vector_push_back(benchmark::State & state) {
    for(auto _ : state) {
        std::vector<int> lvec;
        for(int i = 0; i < state.range(0); ++i) {
            lvec.push_back(i);
        }
    }
}

void BM_vector_emplace_back(benchmark::State & state) {
    for(auto _ : state) {
        std::vector<int> lvec;
        for(int i = 0; i < state.range(0); ++i) {
            lvec.emplace_back(i);
        }
    }
}

void BM_vector_insert(benchmark::State & state) {
    for(auto _ : state) {
        std::vector<int> lvec;
        for(int i = 0; i < state.range(0); ++i) {
            lvec.insert(lvec.end(), i);
        }
    }
}

BENCHMARK(BM_vector_push_back)->Range(1, 1000);
BENCHMARK(BM_vector_emplace_back)->Range(1, 1000);
BENCHMARK(BM_vector_insert)->Range(1, 1000);

int main(int argc, char * argv[]) {

    benchmark::Initialize(&argc, argv);
    benchmark::RunSpecifiedBenchmarks();

    return 0;
}

/*****
    END OF FILE
**********/
