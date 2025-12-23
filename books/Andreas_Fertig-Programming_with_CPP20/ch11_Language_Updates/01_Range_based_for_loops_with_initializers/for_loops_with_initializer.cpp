/*****

References

    Programming with C++20 | Andreas Fertig
    https://en.cppreference.com/w/cpp/language/range-for.html

Chapter 11 | Language Updates

11.1 Range based for loops with initializers

11.1.1 Using a counter variable in a range based for loop
    since C++20 In range-based for-loops, we can declare a variable in the head
    for-loops now are a bit closer to regular for-loops, as regular for-loops allow to declare varible

11.1.2 A workaround for temporaries
    follwing example demonstrates how we can declare varible for temporaries increasing there lifetime

**********/

#include <format>
#include <iostream>
#include <vector>
#include <source_location>

struct Data {

    const std::vector<int> data{51, 52, 53, 54, 55};

    ~Data() {
        std::cout << std::format("~Data()\n");
    }

    auto & get() {
        return data;
    }

};

int main() { 

    {
        std::cout << std::format("=== {} ===\n", "11.1.1 Using a counter variable in a range based for loop");

        {
            std::cout << std::format("{}\n", "using regular for-loop");
            const std::vector lvec{1, 2, 3, 4, 5};
            
            for(size_t i = 0; i < lvec.size(); ++i) {

                std::cout << std::format("index: {} value: {}\n", i, lvec[i]);
            }
        }

        {
            std::cout << std::format("{}\n", "using range based for-loop");
            const std::vector lvec{1, 2, 3, 4, 5};

            // relationship between i and for-loop is obfuscated

            size_t i{0};
            for(const auto & val : lvec) {

                std::cout << std::format("index: {} value: {}\n", i++, val);
            }
        }

        {
            std::cout << std::format("{}\n", "using range based for-loop with initialization");
            const std::vector lvec{1, 2, 3, 4, 5};

            // relationship between i and for-loop is clear
            for(size_t i{0}; const auto & val : lvec) {

                std::cout << std::format("index: {} value: {}\n", i++, val);
            }
        }

    }

    {
        std::cout << std::format("=== {} ===\n", "11.1.2 A workaround for temporaries");

        std::cout << std::format("using reference to temporary\n");
        for(auto & val : Data().get()) {

            std::cout << std::format("value: {}\n", val);   // RUN time error
        }

        std::cout << std::format("using const reference to temporary\n");
        for(const auto & val : Data().get()) {

            std::cout << std::format("value: {}\n", val);   // RUN time error
        }  

        std::cout << std::format("declrae a rvalue for temporary and use it\n");
        for(auto && data = Data(); auto & val : data.get()) {

            std::cout << std::format("value: {}\n", val);   // RUN time error
        }  
                      
    }

    

    return 0; 
}

/*****
    END OF FILE
**********/
