/*****

References
    Asynchronous Programming with C++ | Javier Reguera-Salgado & Juan Antonio Rufes
	https://github.com/google/googletest

    Code https://godbolt.org/z/3rzszWEnz


Chapter 12 | Sanitizing and Testing Asynchronous Software

Testing asynchronous code

Testing multiple threads



    Following is list of a few macros to use in test

    EXPECT_EQ(expected, actual)
    EXPECT_NE(expected, actual)
    EXPECT_LE(val1, val2)
    EXPECT_LT(val1, val2)
    EXPECT_GE(val1, val2)
    EXPECT_GT(val1, val2)

    ASSERT_EQ(val1, val2)
    ASSERT_NE(val1, val2)
    ASSERT_LE(val1, val2)
    ASSERT_LT(val1, val2)
    ASSERT_GE(val1, val2)
    ASSERT_GT(val1, val2)

    EXPECT_STREQ(expected, actual)
    EXPECT_STRNE(s1, s2)
    EXPECT_STRCASEEQ(expected, actual)
    EXPECT_STRCASENE(s1, s2)

    ASSERT_STREQ(expected, actual)
    ASSERT_STRNE(s1, s2)
    ASSERT_STRCASEEQ(expected, actual)
    ASSERT_STRCASENE(s1, s2)

**********/

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <thread>
#include <chrono>
#include <exception>
#include <condition_variable>


std::atomic<int>     counter{0};

std::condition_variable      cv{};
std::mutex                  mtx{};

void fun() {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    ++counter;
    cv.notify_one();
}

TEST(ThreadTest, ThreadTest1) {

    const int thread_count{10};
    std::vector<std::jthread>   threads;
    for(int i = 0; i < thread_count; ++i) {
        threads.emplace_back(fun);
    }

    {
        std::unique_lock    l_lock{mtx};
        cv.wait_for( l_lock, std::chrono::milliseconds(200), [] {
            return counter == thread_count;
        });
    }

    EXPECT_EQ(counter, thread_count);
}


int main() {

    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();

}

/*****
    END OF FILE
**********/

