/*****

References
    Asynchronous Programming with C++ | Javier Reguera-Salgado & Juan Antonio Rufes
	https://github.com/google/googletest

    Code https://godbolt.org/z/jGKWsEfGY


Chapter 12 | Sanitizing and Testing Asynchronous Software

Testing asynchronous code

Testing event-driven software

    In event-driven programming,
    we can set up the test to inject callbacks and validate the result after they are called.

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
#include <boost/asio.hpp>
#include <chrono>
#include <future>
#include <string>
#include <thread>

template<typename ...Args>
auto callit(boost::asio::io_context& io_context, auto callback, Args && ...args) {
    boost::asio::post(io_context,
        [callback, ...args=std::forward<Args>(args)](){
            return callback(args...);
        }
    );
}

TEST(CallbackTestSuite, CallbackTestSuite_CallOK) {

    bool callback_called{false};
    int result{0};

    auto callback_impl = [&](){

        callback_called = true;
        result = 42;

    };

    boost::asio::io_context io_context;
    std::jthread io_thread(
        [&io_context](){
            io_context.run();
        }
    );

    callit(io_context, callback_impl);
    std::this_thread::sleep_for(std::chrono::seconds(2));

    EXPECT_TRUE(callback_called);
    EXPECT_EQ(result, 42);

}

TEST(CallbackTestSuite, CallbackTestSuite_CallOK_2) {

    bool callback_called{false};
    int result{0};

    auto callback_impl = [&](const int v1, const int v2){

        callback_called = true;
        result = v1 + v2;

    };

    boost::asio::io_context io_context;
    std::jthread io_thread(
        [&io_context](){
            io_context.run();
        }
    );

    callit(io_context, callback_impl, 1, 2);
    std::this_thread::sleep_for(std::chrono::seconds(2));

    EXPECT_TRUE(callback_called);
    EXPECT_EQ(result, 3);

}

TEST(CallbackTestSuite, CallbackTestSuite_CallNOK) {

    bool callback_called{false};
    int result{0};

    //auto callback_impl = [&](){
    //
    //    callback_called = true;
    //    result = 42;
    //
    //}

    //callit(callback_impl);
    std::this_thread::sleep_for(std::chrono::seconds(2));

    EXPECT_TRUE(callback_called);
    EXPECT_EQ(result, 42);

}


int main() {

    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();

}

/*****
    END OF FILE
**********/

