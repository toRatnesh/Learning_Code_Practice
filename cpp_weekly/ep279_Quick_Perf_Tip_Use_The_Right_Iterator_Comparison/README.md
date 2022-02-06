/*************
  This example demonstrates how using right iterator comparison results in
  better performance.

  This also demonstrates how using range based for loop (best practices)
  avoids this pitfall of iterator comparison.

  This code is for performance comparison.
 ****************/

static void WrongComparison(benchmark::State& state) {
	// Code inside this loop is measured repeatedly
	for (auto _ : state) {
		std::vector<std::string> vec;
		vec.reserve(20);
		for(auto it = vec.begin(); it < vec.end(); ++it) {
			std::puts((*it).c_str());
		}
	}
}
// Register the function as a benchmark
BENCHMARK(WrongComparison);

static void RightComparison(benchmark::State& state) {
	// Code inside this loop is measured repeatedly
	for (auto _ : state) {
		std::vector<std::string> vec;
		vec.reserve(20);
		for(auto it = vec.begin(); it != vec.end(); ++it) {
			std::puts((*it).c_str());
		}
	}
}
// Register the function as a benchmark
BENCHMARK(RightComparison);


static void RightComparison2(benchmark::State& state) {
	// Code inside this loop is measured repeatedly
	for (auto _ : state) {
		std::vector<std::string> vec;
		vec.reserve(20);
		for(auto & elem : vec) {
			std::puts(elem.c_str());
		}
	}
}
// Register the function as a benchmark
BENCHMARK(RightComparison2);


/*******
  END OF FILE 
 *******/
