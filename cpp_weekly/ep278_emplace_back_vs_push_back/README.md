
#emaplace_back vs push_back

/********************
  This example demonstraes about the use of emplace_back and push_back.
  This benchmark is to compare performance for other semantic chck code.

	Open the code i quick-bench.
	https://quick-bench.com/ 
********************/


static void EmplaceBack(benchmark::State& state) {
  // Code inside this loop is measured repeatedly
  for (auto _ : state) {
    std::vector<std::string> vec;
    vec.reserve(20);
    for(int i = 0; i < 20; ++i) {
      vec.emplace_back(100, 'c');
    }
  }
}
// Register the function as a benchmark
BENCHMARK(EmplaceBack);


static void PushBack(benchmark::State& state) {
  // Code inside this loop is measured repeatedly
  for (auto _ : state) {
    std::vector<std::string> vec;
    vec.reserve(20);
    for(int i = 0; i < 20; ++i) {
      std::string lstr(100, 'c');
      vec.push_back(lstr);
    }
  }
}
// Register the function as a benchmark
BENCHMARK(PushBack);

static void PushBackByMove(benchmark::State& state) {
  // Code inside this loop is measured repeatedly
  for (auto _ : state) {
    std::vector<std::string> vec;
    vec.reserve(20);
    for(int i = 0; i < 20; ++i) {
      std::string lstr(100, 'c');
      // NOTE:  making lstr const would cause move via copy and hence similar to above PushBack
      vec.push_back(std::move(lstr));
    }
  }
}
// Register the function as a benchmark
BENCHMARK(PushBackByMove);


/*********
    END OF FILE
 *******/
