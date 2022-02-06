
In this episode Jason talks about string clear vs empty assignment.

string clear method has better performance than empty assignment

For more info visit:
https://www.youtube.com/watch?v=3X9qK7HWxjk&list=PLs3KjaCtOwSZ2tbuV1hx8Xz-rFZTan2J1&index=273&t=1s


/***********
  CODE FROM QUICK BENCH

 ***************/



#include <benchmark/benchmark.h>

static void stringEmptyAssignment(benchmark::State& state) {
	// Perform setup here
	for (auto _ : state) {
		// This code gets timed
		std::string l_str("string clear vs =");
		l_str = "";
		benchmark::DoNotOptimize(l_str);
	}
}
// Register the function as a benchmark
BENCHMARK(stringEmptyAssignment);


static void stringClear(benchmark::State& state) {
	// Perform setup here
	for (auto _ : state) {
		// This code gets timed
		std::string l_str("string clear vs =");
		l_str.clear();
		benchmark::DoNotOptimize(l_str);
	}
}
// Register the function as a benchmark
BENCHMARK(stringClear);


// Run the benchmark
//BENCHMARK_MAIN();

/***********
	END OF FILE
********/
