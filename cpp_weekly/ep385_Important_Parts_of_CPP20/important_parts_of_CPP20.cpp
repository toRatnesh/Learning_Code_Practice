/*******

    This example demonstrates about important features of C++20

    1. Designated initializer
    2. 3-way comparison or spaceship operator
    3. Modules
    4. Coroutines
    5. Concepts or auto concepts
    6. Format lib
    7. Source location
    8. Calendar updates to chrono
    9. Ranges
    10. More Constexpr
    11. Span
    12. Multiple thread features

****************/

#include <iostream>

#include <format>
#include <source_location>
#include <string>
#include <chrono>
#include <array>
#include <ranges>
#include <numeric>
#include <span>
#include <thread>

int main() {

    {
        std::cout << std::format("=== 1. Designated initializer ===\n");

        struct S {
            int             ival;
            double          dval;
            std::string     sval;
        };

        S s1{.ival = 5, .dval = 6.7, .sval = "sample string"};
        std::cout << std::format("ival {}, dval {}, sval {}\n", s1.ival, s1.dval, s1.sval);
        
        S s2{.ival = 5, .dval = 6.7};
        std::cout << std::format("ival {}, dval {}, sval {}\n", s2.ival, s2.dval, s2.sval);
        
        //S s3{.ival = 5, .sval = "sample string", .dval = 6.7}; // CE: designator order for field 'main()::S::dval' does not match declaration order in 'main()::S'
        
        S s4{.ival = 5, .sval = "sample string"};
        std::cout << std::format("ival {}, dval {}, sval {}\n", s4.ival, s4.dval, s4.sval);
    }


    {
        std::cout << std::format("\n=== 2. 3-way comparison or spaceship operator ===\n");       

        struct S {
            int             ival;
            double          dval;
            std::string     sval;
            constexpr auto operator<=>(const S & ) const = default;
        };

        {
            S s1{2, 3.5, "sample string"};
            S s2{2, 3.5, "sample string"};
            std::cout << std::format("ival {}, dval {}, sval {}\n", s1.ival, s1.dval, s1.sval);
            std::cout << std::format("ival {}, dval {}, sval {}\n", s2.ival, s2.dval, s2.sval);
            std::cout << std::format("Comparison result of s1 < s2 {}\n", s1<s2);
        }
        {
            S s1{2, 3.5, "sample string"};
            S s2{3, 3.5, "sample string"};
            std::cout << std::format("ival {}, dval {}, sval {}\n", s1.ival, s1.dval, s1.sval);
            std::cout << std::format("ival {}, dval {}, sval {}\n", s2.ival, s2.dval, s2.sval);            
            std::cout << std::format("Comparison result of s1 < s2 {}\n", s1<s2);
        }
        {
            S s1{2, 3.5, "sample string"};
            S s2{2, 3.6, "sample string"};
            std::cout << std::format("ival {}, dval {}, sval {}\n", s1.ival, s1.dval, s1.sval);
            std::cout << std::format("ival {}, dval {}, sval {}\n", s2.ival, s2.dval, s2.sval);            
            std::cout << std::format("Comparison result of s1 < s2 {}\n", s1<s2);
        }
        {
            S s1{2, 3.5, "sample string"};
            S s2{2, 3.5, "Sample string"};
            std::cout << std::format("ival {}, dval {}, sval {}\n", s1.ival, s1.dval, s1.sval);
            std::cout << std::format("ival {}, dval {}, sval {}\n", s2.ival, s2.dval, s2.sval);            
            std::cout << std::format("Comparison result of s1 < s2 {}\n", s1<s2);
        }
    }

    {
        std::cout << std::format("\n=== 3. Modules ===\n");
        std::cout << std::format("Not supported by any compiler yet\n");
    }

    {
        std::cout << std::format("\n=== 4. Coroutines ===\n");
        std::cout << std::format("No std lib support check https://github.com/lewissbaker/cppcoro\n");
    }

    {
        std::cout << std::format("\n=== 5. Concepts or auto concepts ===\n");
        auto l = [](std::integral auto lhs, std::integral auto rhs){ return lhs+rhs; };
        std::cout << std::format("Result of l(3, 5) {}\n", l(3,5));
    }

    {
        std::cout << std::format("\n=== 6. Format lib ===\n");
        std::cout << std::format("Python Style support for fomratting in {} version {}\n", "C++", 20);
    }

    {
        std::cout << std::format("\n=== 7. Source location ===\n");
        std::cout << std::format("File \"{}\" funciton \"{}\" line {}\n", 
            std::source_location::current().file_name(),
            std::source_location::current().function_name(),
            std::source_location::current().line());
    }

    {
        std::cout << std::format("\n=== 8. Calendar updates to chrono ===\n");
        std::cout << std::format("Day {}\n", std::chrono::day(1));
    }

    {
        std::cout << std::format("\n=== 9. Ranges ===\n");
        std::vector vec{1,2,3,4,5,6,7,8,9};
        for(const auto & elem : vec|std::ranges::views::drop(2)) {
            std::cout << std::format("{}, ", elem);
        }
        std::cout << '\n';
    }

    {
        std::cout << std::format("\n=== 10. More Constexpr ===\n");
        std::cout << std::format("C++ has implemented more library features and container methods as constexpr\n");
        
        constexpr std::array arr{1,2,3,4,5,6,7,8,9};
        constexpr auto res = std::accumulate(arr.cbegin(), arr.cend(), 0);
        static_assert(45 == res);
    }

    {
        std::cout << std::format("\n=== 11. Span ===\n");
        std::array  larr{1,2,3,4,5,6,7,8,9};
        std::span   sp(larr);

        for(auto const & elem : sp) {
            std::cout << elem << ',';
        }
        std::cout << '\n';

        for(auto const & elem : sp|std::ranges::views::drop(4)) {
            std::cout << elem << ',';
        }
        std::cout << '\n';        
    }

    {
        std::cout << std::format("\n=== 12. Multiple thread features ===\n");
        /*
        1. jthread      https://en.cppreference.com/w/cpp/thread/jthread
        2. atomic_ref   https://en.cppreference.com/w/cpp/atomic/atomic_ref
        3. latch        https://en.cppreference.com/w/cpp/thread/latch
        4. barrier      https://en.cppreference.com/w/cpp/thread/barrier
        5. Semaphores   https://en.cppreference.com/w/cpp/thread#Semaphores
        */
        auto routine = [](){ std::cout << "This is a thread routine\n"; };
        std::jthread thr(routine);
    }

    return 0;
}

/*******
    END OF FILE
****************/



