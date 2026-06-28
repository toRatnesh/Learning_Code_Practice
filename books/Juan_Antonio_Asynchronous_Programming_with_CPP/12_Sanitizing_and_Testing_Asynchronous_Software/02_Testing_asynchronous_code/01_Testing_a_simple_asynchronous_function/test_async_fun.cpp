/*****

References
    Asynchronous Programming with C++ | Javier Reguera-Salgado & Juan Antonio Rufes
	https://github.com/google/googletest

    Code https://godbolt.org/z/6W1fMrMjs

Chapter 12 | Sanitizing and Testing Asynchronous Software

Testing asynchronous code

Testing a simple asynchronous function

    
    TEST() macro, where its first parameter is the test suite name and the second parameter is the test name
        TEST(test_suite_name, test_name);

    EXPECT_EQ compares the result and expected value
        EXPECT_EQ(result.get(), 42);

    GoogleTest library is initialized by calling
        ::testing::InitGoogleTest(&argc, argv);
    This function parses the command line for the flags that GoogleTest recognizes.

    RUN_ALL_TESTS(), which collects and runs all tests and returns 0 if all tests are successful or 1 otherwise

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

std::string getValue() {
    return std::string("testing simple async function");
}

TEST(AsyncTestSuite, AsyncTestSuite_SimpleFuncTestOK) {

    auto result = std::async(
        std::launch::async, getValue
    );

    EXPECT_EQ(result.get(), std::string("testing simple async function"));
    //EXPECT_STREQ(result.get().c_str(), "testing simple async function");

}

TEST(AsyncTestSuite, AsyncTestSuite_SimpleFuncTestNOK) {

    auto result = std::async(
        std::launch::async, getValue
    );

    EXPECT_NE(result.get(), std::string("testing simple async function  FAIL IT"));
    //EXPECT_STRNE(result.get().c_str(), "testing simple async function FAIL IT");

}

TEST(AsyncTestSuite, AsyncTestSuite_SimpleFuncTestFail) {

    auto result = std::async(
        std::launch::async, getValue
    );

    EXPECT_EQ(result.get(), std::string("testing simple async function NOT MATCH"));
    //EXPECT_STREQ(result.get().c_str(), "testing simple async function NOT MATCH");

}

int main() {
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();

    return 0;
}

/*****
    END OF FILE
**********/

