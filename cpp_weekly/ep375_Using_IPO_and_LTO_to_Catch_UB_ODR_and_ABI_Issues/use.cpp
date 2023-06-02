
#include <iostream>

struct Data {
    int y;
    float x;
};

void use_data(const Data & data) {
    std::cout << "data x: " << data.x << ", y: " << data.y << '\n';
    return;
}

