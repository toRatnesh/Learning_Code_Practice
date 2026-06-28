/*****

References
    Asynchronous Programming with C++ | Javier Reguera-Salgado & Juan Antonio Rufes
	https://github.com/google/googletest

    Code https://godbolt.org/z/c4crzPqdf

Chapter 12 | Sanitizing and Testing Asynchronous Software

Testing asynchronous code

Mocking external resources

    If the asynchronous code also depends on external resources, 
    such as file access, network servers, timers, or other modules, 
    we might need to mock them and avoid unwanted failures due to 
    any resource issues translated into the tests.

    Instead of fully defining the mock class, we can also 
    use the gMock library and mock only the needed methods.

    Instead of overriding its methods, the MOCK_METHOD macro is used instead, 
    where the return type, the mocked method name, and its parameters are passed.

    test uses the EXPECT_CALL macro to define an expected call to the mocked method in mock class, 
    which will happen only once and invoke the function

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
#include <string>

class Session {
    public:
    virtual size_t write(std::string msg) = 0;
    virtual std::string read() = 0;
};

class MockSession : public Session {
    public:
    size_t write(const std::string msg) override {
        return msg.size();
    }
    std::string read() override {
        return std::string("Data read from network");
    }
};

TEST(MockTest, MockTestWrite) {
    MockSession msession;

    const std::string msg{"some data to send to network"};
    auto ret = msession.write(msg);
    EXPECT_EQ(ret, msg.size());

}

TEST(MockTest, MockTestRead) {
    MockSession msession;

    auto msg = msession.read();
    EXPECT_NE(0, msg.size());

}

class GMockSession : public Session {
    public:

    virtual ~GMockSession() = default;

    MOCK_METHOD(size_t, write, (const std::string msg), (override));
    MOCK_METHOD(std::string, read, (), (override));
};

TEST(GMockTest, GMockTestWrite) {
    GMockSession msession;

    const std::string msg{"some data to send to network"};
    
    EXPECT_CALL(msession, write(msg))
    .Times(1)
    .WillOnce(testing::Return(msg.size()));

    auto ret = msession.write(msg);
    EXPECT_EQ(ret, msg.size());

}

TEST(GMockTest, GMockTestRead) {
    GMockSession msession;

    EXPECT_CALL(msession, read())
    .Times(1)
    .WillOnce(testing::Return("some network data"));

    auto msg = msession.read();
    EXPECT_NE(0, msg.size());

}

int main() {

    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();

}

/*****
    END OF FILE
**********/

