/*****

References
    episode https://www.youtube.com/watch?v=W4G2xJX9Gnw
    https://en.cppreference.com/w/cpp/language/lambda


**********/

#include <iostream>
#include <string>
#include <memory>
#include <array>

template<typename T, typename U>
void using_lambda(T * plambda, U arg) {
    auto res = (*plambda)(arg);
    std::puts(std::to_string(res).c_str());
}

int main() {

    std::puts("=== Lambda without capture on heap ===");

    {
        auto lambda = [] (int multiplier) { 
            std::puts("Lambda without capture"); 
            return 5 * multiplier;
        };
        auto res = lambda(5);
        std::puts(std::to_string(res).c_str());

        using_lambda(&lambda, 3);
    }

    {
        auto lambda = [] (int multiplier) { 
            std::puts("Lambda without capture on heap using new"); 
            return 5 * multiplier;
        };
        auto plambda = new decltype(lambda){std::move(lambda)};
        auto res = (*plambda)(5);
        std::puts(std::to_string(res).c_str());

        using_lambda(plambda, 3);

        if(nullptr != plambda) {
            delete plambda;
            plambda = nullptr;
        }
    }

    {   
        auto plambda =  new auto([] (int multiplier) {    
            std::puts("Lambda with capture on heap using new auto()"); 
            return 5 * multiplier;
        });
        
        auto res = (*plambda)(5);
        std::puts(std::to_string(res).c_str());

        using_lambda(plambda, 3);
        if(nullptr != plambda) {
            delete plambda;
            plambda = nullptr;
        }        
    }

    {
        auto lambda = [] (int multiplier) { 
            std::puts("Lambda without capture on heap using make_unique"); 
            return 5 * multiplier;
        };
        auto plambda = std::make_unique<decltype(lambda)>(std::move(lambda));
        auto res = (*plambda)(5);
        std::puts(std::to_string(res).c_str());

        using_lambda(plambda.get(), 3);
    }

    #if (202002L == __cplusplus)
    {   std::puts("--- Lambda on heap, using c++20 lambda in unevaluated context ");
        auto plambda = new decltype([] (int multiplier) { 
            std::puts("Lambda without capture on heap using new"); 
            return 5 * multiplier;
        });
        auto res = (*plambda)(5);
        std::puts(std::to_string(res).c_str());

        using_lambda(plambda, 3);

        if(nullptr != plambda) {
            delete plambda;
            plambda = nullptr;
        }
    }

    {
        auto plambda = std::make_unique<decltype([] (int multiplier) { 
            std::puts("Lambda without capture on heap using make_unique"); 
            return 5 * multiplier;
        })>();
        auto res = (*plambda)(5);
        std::puts(std::to_string(res).c_str());

        using_lambda(plambda.get(), 3);                
    }
    #endif



    
    std::puts("\n === Lambda with capture on heap ===");

    {
        auto lambda = [arr = std::array<int, 1024>{1, 2, 3, 4}] (int multiplier) { 
            std::puts("Lambda with capture"); 
            return 5 * multiplier * arr[2];
        };
        auto res = lambda(5);
        std::puts(std::to_string(res).c_str());

        using_lambda(&lambda, 3);
    }

    {
        auto lambda = [arr = std::array<int, 1024>{1, 2, 3, 4}] (int multiplier) { 
            std::puts("Lambda with capture on heap using new"); 
            return 5 * multiplier * arr[2];
        };
        auto plambda = new decltype(lambda){std::move(lambda)};
        auto res = (*plambda)(5);
        std::puts(std::to_string(res).c_str());

        using_lambda(plambda, 3);

        if(nullptr != plambda) {
            delete plambda;
            plambda = nullptr;
        }
    }

    {   
        auto plambda =  new auto([arr = std::array<int, 1024>{1, 2, 3, 4}] (int multiplier) {    
            std::puts("Lambda with capture on heap using new auto()"); 
            return 5 * multiplier * arr[2];
        });
        
        auto res = (*plambda)(5);
        std::puts(std::to_string(res).c_str());

        using_lambda(plambda, 3);
        if(nullptr != plambda) {
            delete plambda;
            plambda = nullptr;
        }        
    }

    {
        auto lambda = [arr = std::array<int, 1024>{1, 2, 3, 4}] (int multiplier) { 
            std::puts("Lambda with capture on heap using make_unique"); 
            return 5 * multiplier * arr[2];
        };
        auto plambda = std::make_unique<decltype(lambda)>(std::move(lambda));
        auto res = (*plambda)(5);
        std::puts(std::to_string(res).c_str());

        using_lambda(plambda.get(), 3);
    }

    #if (202002L == __cplusplus)
    // NOTE: SINCE C++20 ONLY LAMBDA WITHOUT CAPTURE CAN BE USED IN UNEVALUATED CONTEXT
    std::puts("--- Lambda with capture on heap, using c++20 lambda in unevaluated context ");
    {   
        // error: no matching constructor for initialization of [the lambda expression] (aka '(lambda at <source>:71:37)'
        /*
        auto plambda = new decltype([arr = std::array<int, 1024>{1, 2, 3, 4}] (int multiplier) {    
            std::puts("Lambda with capture on heap using make_unique"); 
            return 5 * multiplier * arr[2];
        }){};
        */
    }

    {   /* error: no matching constructor for initialization of '(lambda at <source>:80:50)'
        auto plambda = std::make_unique<decltype([arr = std::array<int, 1024>{1, 2, 3, 4}] (int multiplier) {    
            std::puts("Lambda with capture on heap using make_unique"); 
            return 5 * multiplier * arr[2];
        })>();
        */
               
    }

    #endif

    return 0;
}

/*****
    END OF FILE
**********/


