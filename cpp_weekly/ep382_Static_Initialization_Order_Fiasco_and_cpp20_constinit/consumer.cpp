
#include "consumer.hpp"
#include <iostream>

constexpr Consumer::Consumer() {
    consume(provider.data());
}

void Consumer::consume(const std::string_view data) 
{
    std::cout << data << '\n';
}

Consumer consumer;

