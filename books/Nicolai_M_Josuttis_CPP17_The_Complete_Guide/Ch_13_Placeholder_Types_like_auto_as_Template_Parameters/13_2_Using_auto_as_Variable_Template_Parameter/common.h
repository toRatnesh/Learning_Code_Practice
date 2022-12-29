#ifndef COMMON_H
#define COMMON_H

#include <array>

// auto as Variable Template Parameter
template<typename T, auto N>
std::array<T, N> garr;

void printArray();


// declare a constant variable of an arbitrary type
template<auto val>
constexpr auto gval = val;

inline char gcarr[] = "global char array";

#endif


