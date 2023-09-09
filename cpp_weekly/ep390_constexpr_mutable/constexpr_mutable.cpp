/*****

This example demonstartes about use constexpr and mutable together

References
    episode https://www.youtube.com/watch?v=67DenIV45xY

**********/

#include <iostream>
#include <string>

class LambdaLike {
    int     m_value;

    public:
    constexpr int operator()(const int multiplier) const {
        return m_value * multiplier;
    }

    constexpr LambdaLike(int value) : m_value(value) { }
};

class LambdaLikeMutable {
    mutable int     m_value;

    public:
    /*constexpr*/ consteval int operator()(const int multiplier) const {
        return (++m_value) * multiplier;
    }

    /*constexpr*/ consteval LambdaLikeMutable(int value) : m_value(value) { }
};

int main() {

    {
        constexpr auto lambda = [value = 10](const int multiplier) /*constexpr*/ consteval { return value * multiplier; };
        static_assert(50 == lambda(5));

        constexpr LambdaLike lambda_like{10};
        static_assert(50 == lambda_like(5));
    }

    {
        /*****
        can not use constexpr with mutabel lambda becasue 
        using mutable will make operator()() as non-const which 
        can not be called using a const or constexpr object        
        **********/
        [[maybe_unused]] constexpr auto lambda = [value = 10](const int multiplier) constexpr mutable { return (++value) * multiplier; };
        //static_assert(50 == lambda(5));

        constexpr LambdaLikeMutable lambda_like_mutable{10};
        // CE error: mutable 'LambdaLikeMutable::m_value' is not usable in a constant expression
        //static_assert(50 == lambda_like_mutable(5));        
    }

    return 0;
}

/*****
    END OF FILE
**********/


