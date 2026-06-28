/*****

References
    Asynchronous Programming with C++ | Javier Reguera-Salgado & Juan Antonio Rufes
	https://github.com/google/googletest

    Code https://godbolt.org/z/57WxfYzcW


Chapter 12 | Sanitizing and Testing Asynchronous Software

Testing asynchronous code

Testing callbacks

    We can set a variable and a flag from inside the function and check result and flag after execution of callback

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

template<typename ...Args>
auto callit(auto callback, Args && ...args) {
    std::thread(
        [callback, ...args=std::forward<Args>(args)](){
            return callback(args...);
        }
    ).detach();
}

TEST(CallbackTestSuite, CallbackTestSuite_CallOK) {

    bool callback_called{false};
    int result{0};

    auto callback_impl = [&](){

        callback_called = true;
        result = 42;

    };

    callit(callback_impl);
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

    callit(callback_impl, 1, 2);
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

