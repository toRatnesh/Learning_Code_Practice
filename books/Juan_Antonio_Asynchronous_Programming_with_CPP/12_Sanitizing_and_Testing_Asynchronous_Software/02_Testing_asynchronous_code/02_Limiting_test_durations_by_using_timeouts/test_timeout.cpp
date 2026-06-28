/*****

References
    Asynchronous Programming with C++ | Javier Reguera-Salgado & Juan Antonio Rufes
	https://github.com/google/googletest

    Code https://godbolt.org/z/3efPfTsEK

Chapter 12 | Sanitizing and Testing Asynchronous Software

Testing asynchronous code

Limiting test durations by using timeouts

    A timer can be used, setting its timeout period to a reasonable value 
    to give enough time for the test to complete successfully.
    Therefore, if the timer times out, the test will fail.

    In case of time out and the FAIL() macro will be called, making the test fail.

    After checking expected value also checks if the time spent running the asynchronous task 
    is less than the used timeout


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
#include <chrono>
#include <future>
#include <string>

std::string getValue(const bool timeout) {
    if(timeout) {
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    } else {
        std::this_thread::sleep_for(std::chrono::milliseconds(195));
    }
    
    return std::string("testing simple async function");
}

TEST(AsyncTimeout, AsyncTimeout_OK) {

    auto l_start_time = std::chrono::high_resolution_clock::now();

    auto l_result = std::async(
        std::launch::async,
        getValue,
        false
    );

    if(l_result.wait_for(std::chrono::milliseconds(200)) == std::future_status::timeout) {
        FAIL() << "Test timed out";
    }

    EXPECT_EQ(l_result.get(), std::string("testing simple async function"));

    auto l_end_time = std::chrono::high_resolution_clock::now();
    auto l_duration= std::chrono::duration_cast<std::chrono::milliseconds>(l_end_time - l_start_time);

    EXPECT_LT(l_duration.count(), 200);

}

TEST(AsyncTimeout, AsyncTimeout_Timeout) {

    auto l_start_time = std::chrono::high_resolution_clock::now();

    auto l_result = std::async(
        std::launch::async,
        getValue,
        true
    );

    if(l_result.wait_for(std::chrono::milliseconds(200)) == std::future_status::timeout) {
        FAIL() << "Test timed out";
    }

    EXPECT_EQ(l_result.get(), std::string("testing simple async function"));

    auto l_end_time = std::chrono::high_resolution_clock::now();
    auto l_duration= std::chrono::duration_cast<std::chrono::milliseconds>(l_end_time - l_start_time);

    EXPECT_LT(l_duration.count(), 200);

}


int main() {
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();

    return 0;
}

/*****
    END OF FILE
**********/

