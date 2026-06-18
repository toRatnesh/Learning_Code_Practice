13	Improving Asynchronous Software Performance
=================================================

# Performance measurement tools

To know whether your program meets its performance requirements (either latency or throughput), you need to measure
Once you have the data from your performance tests, you’ll know the hotspots in your code

## In-code profiling

in-code profiling, which consists of adding some extra code to measure the execution time of some code sections
we can use clock e.g. std::chrono::high_resolution_clock to measure execution time of our code

## Code micro-benchmarks

we can use a benchmark (also called a micro-benchmark) library to do just that – execute small parts of our code in different conditions

Example:

```
	...
	
	void BM_vector_push_back(benchmark::State & state) {
		for(auto _ : state) {
			std::vector<int>	vec;
			for(int i = 0; i < state.range(0); ++i) {
				vec.emplace_back(i);
			}
		}
	}
	
	...
	
	BENCHMARK(BM_vector_push_back)->Range(1, 1000);
	
	...

```

The benchmark::State parameter has a dual purpose:

1. Controlling the iteration loop:	to control how many times a benchmarked function or piece of code should be executed
2. Measuring time and statistics:	keeps track of how long the benchmarked code takes to run, and it provides mechanisms to report metrics such as elapsed time, iterations, and custom counters

to tell the library that they must be run as a benchmark:

**BENCHMARK(BM_vector_push_back)->Range(1, 1000);**

BENCHMARK_CAPTURE macro: This macro allows us to pass parameters to our benchmark functions

**BENCHMARK_CAPTURE(BM_vector_sort, vector, rv1)->Iterations(1)->Unit(benchmark::kMillisecond);**


## The Linux perf tool

With the Linux perf tool, we can analyze the execution of a program without changing any of its code.

The Linux perf tool is a powerful, flexible, and widely used performance analysis and profiling utility for Linux systems.

It provides detailed insights into system performance at the kernel and user space levels.


**CPU profiling:** perf tool allows you to capture the execution profile of a process, measuring which functions consume most of the CPU time

**Call Graph**

We can generate call graph and flame graph to analyze binary

    perf record --call-graph dwarf ./binary_name

**--call-graph** option records the data of the function call hierarchy in a file called perf.
data

**dwarf** option instructs perf to use the dwarf file format to debug symbols (to get
the function names)

    perf script > out.perf

This will dump the recorded data (including the call stack) into a text file called out.perf

    gprof2dot -f perf out.perf -o callgraph.dot

This will generate a file called callgraph.dot that can be visualized using Graphviz.

    dot -Tpng callgraph.dot -o callgraph.png

This will generate callgraph.png picture


**Flame Graph**

Install FlameGraph

In the FlameGraph folder, you’ll find the scripts to generate the flame graphs.

    FlameGraph/stackcollapse-perf.pl out.perf > out.folded

This command will collapse the stack traces into a format that can be used by the FlameGraph tool.

    Flamegraph/flamegraph.pl out.folded > flamegraph.svg

You can visualize the flame graph with a web browser


**Performance statistics**

    perf stat -e instructions,cycles ./binary_name

This command will show the number of instructions that have been executed and CPU cycles that were used during the execution of 13x05-sort_perf.

The **number of instructions per cycle** is the average number of instructions the CPU executes in each clock cycle.

This metric is generally used to measure and optimize code executed in a single CPU core.

The number must be interpreted as how busy we keep the CPU because it depends on many factors, such as the number of memory reads/writes, memory access patterns (linear consecutive/no linear), level of branching in the code, and so on.

    perf list

get the list of all the predefined events you can analyze with perf

    perf stat -e branches ./binary_name

measures the number of branch instructions that have been executed

A CPU will run instructions much faster if there are no branches or there are just a few. 

The main issue with branches is that the CPU may need to rebuild the pipeline and that can be costly, especially if branches are in inner/critical loops.

    perf stat -e all_data_cache_accesses ./binary_name

report the number of L1 cache data accesses

    perf stat -e cpu-migrations ./binary_name

**CPU migrations:** that is, the number of times a thread was moved from one CPU core to another.

Thread migration between cores can degrade cache performance since threads lose the benefit of cached data when moving to a new core.

    perf stat -e context-switches ./binary_name

**Context switches** It counts the number of context switches (how many times a thread is swapped out and another thread is scheduled) during the execution.

High-context switching can indicate that too many threads are competing for CPU time, leading to performance degradation.

# False sharing

We already know that the ideal implementation of a multithreaded application is minimizing the data that’s shared among its different threads.

Ideally, we should share data just for read access because in that case, we don’t need to synchronize the threads to access the shared data and thus we don’t need to pay the runtime cost and deal with issues such as deadlock and livelock.

**False sharing:** The variables are shared because of the way the cache and the cache coherency protocol work even though they don’t from the program’s point of view.

# CPU memory cache

**CPU cache or memory cache**, which is memory in the chip to store both data and instructions. This memory is **much faster than RAM** and allows the CPU to retrieve data much faster, significantly boosting overall performance.

Cache memory is very fast (much faster than RAM), but it’s also very expensive.

Modern CPUs employ a hierarchical cache structure, typically consisting of three levels called L1, L2, and L3:

**L1 cache**

- smallest and fastest
- typically 64Kb
- closest to the CPU
- most expensive
- two parts 1. instruction cache 2. data cache
- access time 1 ~ 3 ns
- per core

**L2 cache**

- larger and slightly slower than L1
- typically 128 Kb - 512 Kb
- access time 3 ~ 5 ns
- per core

**L3 cache**

- largest and slowest of the three
- **shared by more than one core**
- typically 32 Mb of L3 cache shared by each group of eight cores
- access time 10 ~ 15 ns

Example

```
$ lscpu | grep -i cache
L1d cache:             32K
L1i cache:             32K
L2 cache:              256K
L3 cache:              20480K
```

## Cache coherency

The CPU doesn’t access RAM directly. This access is always done through the cache, and RAM is accessed only if the CPU doesn’t find the data required in the cache.

In multi-core systems, each core having its own cache means that one piece of RAM may be present in the cache of multiple cores at the same time. These copies need to be synchronized all the time; otherwise, computation results
could be incorrect.

**Cache line** CPU will always read and write 64 bytes in one
go (something called a cache line – you can think of it as the smallest memory access unit).

**Cache coherency**
Even if the threads don’t share the variables, the
CPU can’t possibly know that, and it updates all the cache lines for all the cores to keep the values
consistent. This is called cache coherency. If the threads shared the variables, it would be incorrect
not to propagate the changes to all the cores.


**False sharing:** The variables are shared because of the way the cache and the cache coherency protocol work even though they don’t from the program’s point of view.

We can use perf command to see how many times
the program accesses the cache and how many times there’s a cache miss

    perf stat -e cache-references,cache-misses ./binary_name

# SPSC lock-free queue

In example for SPSC lock free queue

https://github.com/toRatnesh/Learning_Code_Practice/tree/main/books/Juan_Antonio_Asynchronous_Programming_with_CPP/05_Atomic_Operations/05_SPSC_lock_free_queue


We used two atomic variables to represent the head and tail of the queue:

```
std::atomic<std::size_t> head_ { 0 };
std::atomic<std::size_t> tail_ { 0 };
```

To avoid false sharing, we can change the code to the following:

```
alignas(64) std::atomic<std::size_t> head_ { 0 };
alignas(64) std::atomic<std::size_t> tail_ { 0 };
```

Here, the producer is the only thread writing tail_ and the consumer is the only thread writing head_. Still, both threads need to read tail_ and head_.

We’ve declared both atomic variables as aligned(64) so that they’re guaranteed to be in different cache lines and there’s no false sharing. However, there is true sharing. 

**True sharing also generates
cache coherency traffic.**

True sharing means that both threads have shared access to both variables, even if each variable is just written by one thread (and always the same thread). In this case, to improve performance, we must reduce sharing, avoiding as much of the read access from each thread to both variables as we can. 

We can’t avoid data sharing, but we can reduce it. Use cache data to store shared data value and update cache only when needed to reduce data sharing between threads.

# Reference

Asynchronous Programming with C++ | Javier Reguera-Salgado & Juan Antonio Rufes  
https://en.cppreference.com/cpp/language/alignas  
https://en.cppreference.com/cpp/thread/hardware_destructive_interference_size  
Optimizing a Lock-Free Ring Buffer | https://david.alvarezrosa.com/posts/optimizing-a-lock-free-ring-buffer/
