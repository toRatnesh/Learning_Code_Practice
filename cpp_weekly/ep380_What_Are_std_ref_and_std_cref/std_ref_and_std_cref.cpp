/**********

    This example demonstrates about std::ref and std::cref
    For more info visit
    https://en.cppreference.com/w/cpp/utility/functional/ref
    episode https://www.youtube.com/watch?v=YxSg_Gzm-VQ

    std::ref and std::cref are used to create 
    std::reference_wrapper<T>
    and 
    std::reference_wrapper<const T> 
    respectively

**************/

#include <iostream>
#include <functional>
#include <algorithm>
#include <array>

int fun(int & parm, const int & c_parm) {
    parm = parm + (c_parm * 2);
    return parm;
}

struct Data {
    // reference wrapper is better than normal reference because 
    // it enables some special opertions like move
    std::reference_wrapper<int>         m_iref_wrap;
    int                             &   m_iref;

};

int main() {
    int res    = 0;
    int data  = 2;

    {
        // bind is taking copy of each parameter
        std::cout << "=== Bind without std::ref() ===\n";
        auto get_double = std::bind(fun, res, data);

        std::cout << "get_double()  " << get_double() << '\n';
        std::cout << "res   " << res << '\n';
        std::cout << "get_double()  " << get_double() << '\n';
        std::cout << "res   " << res << '\n';
    }
    
    {
        // using std::ref and std::cref to pass as reference to bind
        std::cout << "\n=== Bind with std::ref() ===\n";
        auto get_double = std::bind(fun, std::ref(res), std::cref(data));

        std::cout << "get_double()  " << get_double() << '\n';
        std::cout << "res   " << res << '\n';
        std::cout << "get_double()  " << get_double() << '\n';
        std::cout << "res   " << res << '\n';
    }

    {
        std::cout << "\n=== move and assignment of reference_wrapper and normal reference ===\n";
        int val = 7;
        Data data{val, val};
        std::cout << "data.m_iref_wrap: " << data.m_iref_wrap << ", data.m_iref: " << data.m_iref << '\n';

        // CE error: cannot bind non-const lvalue reference of type 'int&' to an rvalue of type 'std::remove_reference<int&>::type' {aka 'int'}
        //Data data2{std::move(data.m_iref_wrap), std::move(data.m_iref)};

        Data data3{std::move(data.m_iref_wrap), data.m_iref};
        std::cout << "data3.m_iref_wrap: " << data3.m_iref_wrap << ", data3.m_iref: " << data3.m_iref << '\n';
        {
        int val2= 9;
        Data data4{val2, val2};
        std::cout << "data4.m_iref_wrap: " << data4.m_iref_wrap << ", data4.m_iref: " << data4.m_iref << '\n';
        data4.m_iref_wrap = data3.m_iref_wrap;
        data4.m_iref = data3.m_iref;
        std::cout << "data4.m_iref_wrap: " << data4.m_iref_wrap << ", data4.m_iref: " << data4.m_iref << '\n';
        }

        {
        int val2= 9;
        Data data4{val2, val2};
        std::cout << "data4.m_iref_wrap: " << data4.m_iref_wrap << ", data4.m_iref: " << data4.m_iref << '\n';            
        data4.m_iref_wrap = std::move(data3.m_iref_wrap);
        data4.m_iref = std::move(data3.m_iref);
        std::cout << "data4.m_iref_wrap: " << data4.m_iref_wrap << ", data4.m_iref: " << data4.m_iref << '\n';
        }
    }

    {
        std::cout << "=== using std::ref in algorithms ===\n";
        auto accumulator = [sum = 0](int value) mutable {
            sum += value;
            return sum;
        };

        std::array  larr{1, 2, 3, 4, 5, 6, 7, 8, 9};

        {
            // algorithms takes copy of callable 
            std::cout << "without std::ref: ";
            std::for_each(larr.begin(), larr.end(), accumulator);
            std::cout << accumulator(0) << '\n';
        }
        
        {
            std::cout << "with std::ref: ";
            std::for_each(larr.begin(), larr.end(), std::ref(accumulator));
            std::cout << accumulator(0) << '\n';
        }
    }

    return 0;
}

/**********
    END OF FILE
**************/




