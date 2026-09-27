/*****

References:
    episode     https://www.youtube.com/watch?v=x2lmqGMIcok
    
    code        https://godbolt.org/z/n74rbTc4W

    This example demonstrates about lambda members in possible 
    implementaion of its closure type



**********/

#include <iostream>
#include <cassert>


int main() {

    {
        [[maybe_unused]] auto simplest_lambda1 = [](){};
        [[maybe_unused]] auto simplest_lambda2 = []{};

        static_assert(sizeof(simplest_lambda1) == 1);
        static_assert(sizeof(simplest_lambda2) == 1);
    }

    {
        //auto lambda_without_capture = [](int & ival) {
        //    ival = ival * 2;
        //    return ival;
        //};


        struct lambda_without_capture_ {

            inline constexpr int operator()(int & ival) { 
                ival = ival * 2;
                return ival;
            }

            // for conversion to funciton pointer
            using fp_ = int(*)(int &);
            inline constexpr operator fp_() const {
                return invoke_;
            }
            private:
            static inline constexpr int invoke_(int & ival) {
                return lambda_without_capture_{}(ival);
            }

        };
        lambda_without_capture_ lambda_without_capture{};

        int ival = 5;
        assert(lambda_without_capture(ival) == ival);

        static_assert(sizeof(lambda_without_capture) == 1);
    }

    {
        //auto lambda_with_capture = [mul = 3](int & ival) {
        //    ival = ival * mul;
        //    return ival;
        //};


        struct lambda_with_capture_ {
            int mul;

            constexpr int operator()(int & ival) const {
                ival = ival * mul;
                return ival;
            }
        };
        lambda_with_capture_ lambda_with_capture{3};

        int ival = 5;
        assert(lambda_with_capture(ival) == ival);

        static_assert(sizeof(lambda_with_capture) == sizeof(int));  // sum of size of capture members
    }

    {
        //auto mutable_lambda_with_capture = [max = 3](int  ival = 0) mutable {
        //    max = (ival > max) ? ival : max;
        //    return max;
        //};

        class mutable_lambda_with_capture_ {
            int max;
            public:
            mutable_lambda_with_capture_(int max_) : max{max_} { }

            inline constexpr int operator()(int  ival = 0)  {
                max = (ival > max) ? ival : max;
                return max;
            }            
        };
        mutable_lambda_with_capture_ mutable_lambda_with_capture{3};


        assert(mutable_lambda_with_capture() == 3);
        assert(mutable_lambda_with_capture(2) == 3);
        assert(mutable_lambda_with_capture(5) == 5);

        static_assert(sizeof(mutable_lambda_with_capture) == sizeof(int));  // sum of size of capture members
    }

    return 0;
}

/*****
    END OF FILE
**********/

