/**********

    This example demonstrates about moving an array
    
    std::move() is not bad but prefer code that does not require std::move()

    if you do need to move an std::array, it's probably smart to actually std::move() it
    the array itself cannot be "moved", but it's subojects might be

    For more info visit
    episode https://www.youtube.com/watch?v=56DMwqKffi0

*************/

#include <iostream>
#include <array>
#include <string>

constexpr size_t array_size = 8;

class Data {
    std::string data;
    public:
    explicit Data() {}
    explicit Data(std::string data) : data(std::move(data)) {}
    Data(const Data & other) {
        std::cout << "Data(const Data & other)\n";
        data = other.data;
    }
    Data& operator=(const Data & other) {
        data = other.data;
        return *this;
    }

    Data (Data && other) {
        std::cout << "Data (Data && other)\n";
        if(&other != this) {
            data = other.data;
        }
    }

    Data& operator=(Data && other) {
        if(&other != this) {
            data = other.data;
        }
        return *this;
    }

};

class S {
    std::array<Data, array_size>     data;
    public:
    S(std::array<Data, array_size> data) 
        :  data(std::move(data)) {}
        //:  data(data) {}
};

int main() {

    std::array<Data, array_size> data;
    static_assert(8 == data.max_size());
    for(size_t i = 0; i < array_size; ++i) {
        data[i] = Data("sample string - " + std::to_string(i));
    }
    S   s{data};

    return 0;
}

/**********
    END OF FILE
*************/


