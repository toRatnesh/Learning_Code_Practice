12 Sanitizing and Testing Asynchronous Software
=================================================

# Sanitizing code to analyze the software and find potential issues

**Sanitizers** are tools, originally developed by Google, used to detect and prevent various types of issues or security vulnerabilities in code, helping developers catch bugs early in the development process, reducing the cost of issues being fixed late, and increasing software stability and security.

As extra instructions are injected into the program’s binary code, there is a **performance penalty** of around 1.5x to 4x slowdowns depending on the sanitizer type.  
Also, there is an overall **memory overhead** of 2x to 4x and a stack size increase of up to 3x.

Valgrind, which imposes a much higher slowdown of up to 50 times slower than production binaries.  
On the other hand, the benefit of using Valgrind is that no recompilation is needed.

## Compiler options

**--fsanitize=sanitizer_name**

- **address: AddressSanitizer(ASan)**, to detect memory errors such as buffer overflows and use-after-free bugs
- **thread: ThreadSanitizer(TSan)**, to identify data races and other thread synchronization issues in multi-threaded programs by monitoring thread interactions
- **leak: LeakSanitizer (LSan)**, to spot memory leaks by tracking memory allocations and ensuring that all allocated memory is properly freed
- **memory: MemorySanitizer (MSan)**, to uncover the use of uninitialized memory
- **undefined: UndefinedBehaviorSanitizer (UBSan)**, to detect undefined behavior, such as integer overflows, invalid type casts, and other erroneous operations

Clang also includes dataflow, cfi (control flow integrity), safe_stack, and realtime.

GCC adds kernel-address, hwaddress, kernel-hwaddress, pointer-compare,
pointer-subtract, and shadow-call-stack.

**-fno-omit-frame-pointer:** A frame pointer is a register used by compilers to track the current stack frame, containing, among other information, the base address of the current function. Omitting frame pointers might increase the performance of the program but at the cost of making debugging significantly harder; it makes it more difficult to locate local variables
and reconstruct stack traces.

**–g[level],** Include debug information and display filenames and line numbers in the warning messages  
[level] being a value from 0 to 3, adding more debug information at
each level increase. The default level is 2.

**–ggdb** option might be desirable as the compiler can produce more expressive symbols to be used when debugging


**–fsanitize-recover:** These options cause the sanitizer to attempt to continue running
the program as if no error was detected.

**–fno-sanitize-recover:** The sanitizer will detect only the first error, and the program
will exit with a non-zero exit code.

    As different sanitizers and compilers recommend specific optimization levels, check their documentation

    Note that enabling –Werror with certain sanitizers can lead to false positives


### Avoiding sanitizing part of the code

- use suppression files
- exclude the code area by using some macro instructions


**Suppression files**

create a text file listing the areas of the code where we don’t want the sanitizer to run

typically, the structure is as follows:

    type:location_pattern

example of a suppression file for an ASan:


    # Suppress known memory leaks in third-party function Func1 in library
    Lib1
    leak:Lib1::Func1
    # Ignore false-positive from function Func2 in library Lib2
    race:Lib2::Func2
    # Suppress issue from libc
    leak:/usr/lib/libc.so.*


Let’s call this file myasan.supp. Then, compile and pass this suppression file to the sanitizer via
[X]SAN_OPTIONS as follows:


    $ clang++ -O0 -g -fsanitize=address -fno-omit-frame-pointer test.cpp
    –o test

    $ ASAN_OPTIONS=suppressions=myasan.supp ./test



**Macros**

to exclude specific functions to be sanitized by using __
attribute__((no_sanitize("<sanitizer_name>"))) as follows:

```
#if defined(__clang__) || defined (__GNUC__)
# define ATTRIBUTE_NO_SANITIZE_ADDRESS __attribute__((no_sanitize_
address))
#else
# define ATTRIBUTE_NO_SANITIZE_ADDRESS
#endif
...
ATTRIBUTE_NO_SANITIZE_ADDRESS
void ThisFunctionWillNotBeInstrumented() {...}
```

## AddressSanitizer

ASan is to detect memory-related errors happening due to buffer overflows (heap, stack, and global) during out-of-bounds accesses of arrays, using a block of memory after being released with free or delete operations, and other memory leaks

**–fsanitize-address-use-after-scope** to detect the memory used after moving out of scope

**ASAN_OPTIONS=detect_stack_use_after_return=1**
environment variable to detect use after return

    ASAN_OPTIONS=detect_stack_use_after_return=1,print_stacktrace=1,log_path=asan.log

**ASan can be combined with UBSan**

## LeakSanitizer

LSan is used to detect memory leaks happening when memory has been allocated but not properly freed.

**LSan is integrated into ASan and enabled by default on Linux systems.**

**For macOS**

to enable,  ASAN_OPTIONS=detect_leaks=1
to disable, ASAN_OPTIONS=detect_leaks=0.

## ThreadSanitizer

TSan is used to detect threading issues, especially data races and synchronization issues.

**It cannot be combined with ASan or LSan.**

to stop after the first error

    TSAN_OPTIONS=halt_on_error=1

TSan only reports race conditions happening at runtime, thus it won’t alert on race conditions present in code paths not executed at runtime. Therefore, we need to design tests that provide good coverage and use a realistic workload.

## UndefinedBehaviorSanitizer

UBSan can detect undefined behavior in code, for example, when shifting bits by an excessive amount, integer overflows, or misuse of null pointers.

Its behavior can be modified at runtime by setting the UBSAN_OPTIONS variable.

**Many errors that can be detected by UBSan are also detected by the compiler during compilation.**

## MemorySanitizer

MSan can detect uninitialized memory usage, for example, when using variables or pointers before
they have been assigned a value or address. 

**It can also track uninitialized bits in a bitfield.**

It can also track each uninitialized value to the memory allocation from where it was created by specifying the **-fsanitize-memory-track-origins** option.

GCC has no support for MSan, so the -fsanitize=memory flag is not valid when using this compiler.

## Other sanitizers

**Hardware-assisted AddressSanitizers (HWASan):** A new variant of ASan that consumes much less memory by using the hardware ability to ignore the top byte of a pointer. It can be enabled by specifying the **–fsanitize=hwaddress** option.

**RealTimeSanitizer (RTSan):** Real-time testing tool to detect real-time violations when calling methods that are not safe in functions with deterministic runtime requirements.

**FuzzerSanitizer:** A sanitizer that detects potential vulnerabilities by feeding large volumes of random data into the program, checking if the program crashes, and looking for memory corruption or other security vulnerabilities.

**Kernel-related sanitizers:** To track issues by kernel developers

- Kernel Address Sanitizer (KASAN)
- Kernel Concurrency Sanitizer (KCSAN)
- Kernel Electric-Fence (KFENCE)
- Kernel Memory Sanitizer (KMSAN)
- Kernel Thread Sanitizer (KTSAN)



# Testing asynchronous code

We will use GoogleTest and GoogleTest Mock (gMock) libraries to compile.

**Unit testing** is the practice of writing small and isolated tests that verify the functionality and behavior of a single unit of code.

Unit testing helps to find and fix bugs, refactor and improve your code quality, document and communicate the underlying code design, and facilitate collaboration
and integration.

## Testing a simple asynchronous function

Check example

    TEST(test_suite_name, test_name)

TEST() macro, where its first parameter is the test suite name (in this example, AsyncTests) and the second parameter is the test name (TestHandleAsyncOperation).

    EXPECT_EQ(result.get(), 42);

EXPECT_EQ compares the result and expected value

GoogleTest library is initialized by calling

    ::testing::InitGoogleTest(&argc, argv);

This function parses the command line for the flags that GoogleTest recognizes.

RUN_ALL_TESTS(), which collects and runs all tests and returns 0 if all tests are successful or 1 otherwise

## Limiting test durations by using timeouts

Check example

a timer can be used,  
Setting its timeout period to a reasonable value to give enough time for the test to complete successfully  
Therefore, if the timer times out, the test will fail

    FAIL() << "Test timed out!";

FAIL() macro will be called, in case test failes due to timeout

    EXPECT_LT(elapsed.count(), 200);

This checks that time taken is less than 200 ms

## Testing callbacks

Testing callback is a relevant task, especially when implementing libraries and application programming interfaces (APIs).

We can set up the test to inject callbacks and validate the result after they are called.

    EXPECT_TRUE(callback_called);

To check if a variable is set

## Testing event-driven software

As in the previous example, We can set up the test to inject callbacks and validate the result after they are called.

## Mocking external resources

If the asynchronous code also depends on external resources, such as file access, network servers, timers, or other modules, we might need to mock them and avoid unwanted failures due to any resource issues translated into the tests.

Instead of fully defining the mock class, we **can also use the gMock library** and mock only the needed methods.

    MOCK_METHOD(int, runTask, (std::function<int()> task), (override));

    EXPECT_CALL(scheduler, runTask(_)).WillOnce(Invoke(task));

Now, MockTaskScheduler also inherits from AsyncTaskScheduler, where the interface is defined, but instead of overriding its methods, the MOCK_METHOD macro is used instead, where the return type, the mocked method name, and its parameters are passed.

Then, the TestMockMethod test uses the EXPECT_CALL macro to define an expected call to the runTask() mocked method in MockTaskScheduler, which will happen only once and invoke the lambda function task, which returns the value 42.

## Testing exceptions and failures

**EXPECT_ANY_THROW()** macro to check if an exception happens when trying to retrieve the result from the future result by calling its get() method

## Testing multiple threads

Check example

Let’s start by defining some necessary global variables, such as the total number of threads (num_threads), counter as an atomic variable that will increase each time the asynchronous task is invoked, and the condition variable, cv, and its associated mutex, mtx, which will help to unblock the main thread once all asynchronous tasks have been completed

```
...

std::unique_lock<std::mutex> lock(mtx);
cv.wait_for(lock, 150ms, [] {
    return counter == num_threads;
});
sync_cout << "All threads have finished."

...

EXPECT_EQ(counter, num_threads);

```

## Testing coroutines

Coroutinebased code can be tested by using a similar approach to other asynchronous code, but with the subtle difference that coroutines can suspend and be resumed.

we need to define some helper functions

## Stress testing

A race condition detector can be achieved by performing stress testing. For highly concurrent or multi-threaded asynchronous code, stress testing is crucial.  
We can simulate high load with multiple asynchronous tasks to check if the system behaves correctly under stress. Also, it’s important to use random delays, thread interleaving, or stress-testing tools, to reduce deterministic conditions, increasing the test coverage.

## Parallelizing tests

To run test suites quicker we can parallelize the tests running in different threads, but tests must be independent, each running in a specific thread as a synchronous single-threaded solution.

When using CMake together with GoogleTest, we can run all detected tests in parallel by specifying the number of concurrent jobs we want to use with the following command:

    $ ctest –j <num_jobs>

# References

Asynchronous Programming with C++ | Javier Reguera-Salgado & Juan Antonio Rufes  
Sanitizers | https://github.com/google/sanitizers  
Google Test | https://github.com/google/googletest
