/*********
  This example demonstrates about static and constexpr static 

  Following is conclusion of this episode:
  With optimizations enabled:
 * clang is the same code in both cases
 * gcc is faster with static when size >= 144 bytes

 With optimizations disabled:
 * clang is always faster with static
 * gcc is always faster with static 

 Your default of constexor data should still be static


 To check run this code in 
 - https://quick-bench.com/ to compare performance
 - https://gcc.godbolt.org/ to check generated assembly

 For more info visit:
https://www.youtube.com/watch?v=IDQ0ng8RIqs&list=PLs3KjaCtOwSZ2tbuV1hx8Xz-rFZTan2J1&index=316
https://en.cppreference.com/w/cpp/language/constexpr
 ********/

#include <benchmark/benchmark.h>

#include <cstdint>
#include <array>

constexpr auto arr_size = 512;

uint32_t to_ascii_base_digit(uint32_t digit) {
	constexpr std::array<char, arr_size> larr = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
	return larr[digit];
}

uint32_t to_ascii_base_digit_static(uint32_t digit) {
	static constexpr std::array<char, arr_size> larr = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
	return larr[digit];
}

static void without_static(benchmark::State & state) {
	auto i = 0;
	for(auto _ : state) {
		i = (i + 1) % arr_size;
		benchmark::DoNotOptimize(to_ascii_base_digit(i));
	}
}
BENCHMARK(without_static);

static void with_static(benchmark::State & state) {
	auto i = 0;
	for(auto _ : state) {
		i = (i + 1) % arr_size;
		benchmark::DoNotOptimize(to_ascii_base_digit_static(i));
	}
}
BENCHMARK(with_static);

/*******
  END OF FILE
 ******/
