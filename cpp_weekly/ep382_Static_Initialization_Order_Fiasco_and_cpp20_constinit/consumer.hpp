
#ifndef CONSUMER_HPP
#define CONSUMER_HPP

#include "provider.hpp"

class Consumer {

    public:
    constexpr Consumer();
    void consume(const std::string_view data);
};

extern Consumer consumer;

#endif
