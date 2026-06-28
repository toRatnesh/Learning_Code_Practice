/*****

References
    Asynchronous Programming with C++ | Javier Reguera-Salgado & Juan Antonio Rufes
	https://github.com/google/googletest

    Code https://godbolt.org/z/3GcEK13Wd


Chapter 12 | Sanitizing and Testing Asynchronous Software

Testing asynchronous code

Testing exceptions and failures

    EXPECT_ANY_THROW() macro that simplifies checking if an exception has happened

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
#include <future>


bool fun(const bool throw_flag) {
    
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    if(throw_flag) {
        throw std::runtime_error("Raising runtime exception");
    }

    return true;
}

TEST(ExceptionTest, Exception1) {
    try {
        auto result = std::async(
            std::launch::async,
            fun,
            true
        );

        result.get();
        FAIL() << "No expected exception thrown";
    } catch (const std::exception &exp) {
        SUCCEED();
    }

}

TEST(ExceptionTest, Exception2) {

    auto result = std::async(
        std::launch::async,
        fun,
        true
    );

    EXPECT_ANY_THROW(result.get());

}

int main() {

    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();

}

/*****
    END OF FILE
**********/

