/*****

References

    episode https://www.youtube.com/watch?v=E5aEt4917mM
    https://en.cppreference.com/w/cpp/utility/initializer_list.html

    This example demonstrates about how presence of a constructor which
    takes initializer_list as parameter can be cause confusion and unexpected
result

**********/

#include <print>
#include <string>
#include <vector>

int main() {
    {
        std::println("=== vector ===");

        {
            std::vector lv(3, 4);
            std::println("vector {}", lv);
        }

        {
            std::vector lv{3, 4};
            std::println("vector {}", lv);
        }
    }

    {
        std::println("=== Data ===");

        struct Data {
            int a;
            int b;
            std::vector<int> data;
        };

        {
            Data lv(3, 4);
            std::println("Data: {} {} {}", lv.a, lv.b, lv.data);
        }

        {
            Data lv{3, 4};
            std::println("Data: {} {} {}", lv.a, lv.b, lv.data);
        }
    }

    {
        std::println("=== Data with initializer_constructor ===");

        struct Data {
            Data(int a, int b) : a{a}, b{b} { }
            Data(std::initializer_list<int> data) : data{data} { }

            int a;
            int b;
            std::vector<int> data;
        };

        {
            Data lv(3, 4);
            std::println("Data: {} {} {}", lv.a, lv.b, lv.data);
        }

        {
            Data lv{3, 4};
            std::println("Data: {} {} {}", lv.a, lv.b, lv.data);
        }


    }

    return 0;
}

/*****
    END OF FILE
**********/
