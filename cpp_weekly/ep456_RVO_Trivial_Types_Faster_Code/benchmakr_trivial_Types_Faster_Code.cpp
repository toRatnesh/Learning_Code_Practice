
#include <array>
#include <numeric>

constexpr size_t num_of_elems = 1024;

auto get_inc_data(int inval) {
    std::array<int, num_of_elems> result;
    for(auto & elem : result) { elem = inval; ++inval;}
    return result;
}

auto get_dec_data(int inval) {
    std::array<int, num_of_elems> result;
    for(auto & elem : result) { elem = inval; --inval;}
    return result;
}

std::array<int, num_of_elems> get_data_rvo(int inval, const bool inc_flag = true) {
    if(inc_flag) {
        return get_inc_data(inval);
    } else {
        return get_dec_data(inval);
    }
}

std::array<int, num_of_elems> get_data(int inval, const bool inc_flag = true) {
    std::array<int, num_of_elems> result;
    if(inc_flag) {
        for(auto & elem : result) { elem = inval; ++inval;}
    } else {
        for(auto & elem : result) { elem = inval; --inval;}
    }
    return result;
}


std::array<int, num_of_elems> get_data_02(int inval, const bool inc_flag = true) {
    
    if(inc_flag) {
        std::array<int, num_of_elems> result;
        for(auto & elem : result) { elem = inval; ++inval;}
        return result;
    } else {
        std::array<int, num_of_elems> result;
        for(auto & elem : result) { elem = inval; --inval;}
        return result;
    }
}



static void GetDataRvo(benchmark::State& state) {
  // Code inside this loop is measured repeatedly
  for (auto _ : state) {
    auto data = get_data_rvo(state.iterations(), (state.iterations() % 2 == 0));
    auto res = std::accumulate(data.begin(), data.end(), 0);

    benchmark::DoNotOptimize(res);
  }
}
// Register the function as a benchmark
BENCHMARK(GetDataRvo);


static void GetData(benchmark::State& state) {
  // Code inside this loop is measured repeatedly
  for (auto _ : state) {
    auto data = get_data(state.iterations(), (state.iterations() % 2 == 0));
    auto res = std::accumulate(data.begin(), data.end(), 0);

    benchmark::DoNotOptimize(res);
  }
}
// Register the function as a benchmark
BENCHMARK(GetData);

static void GetData02(benchmark::State& state) {
  // Code inside this loop is measured repeatedly
  for (auto _ : state) {
    auto data = get_data_02(state.iterations(), (state.iterations() % 2 == 0));
    auto res = std::accumulate(data.begin(), data.end(), 0);
    benchmark::DoNotOptimize(res);
  }
}
// Register the function as a benchmark
BENCHMARK(GetData02);


