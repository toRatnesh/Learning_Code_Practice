/*****

References

std::bitset
    since C++23 All member functions of std::bitset are constexpr: 
    it is possible to create and use std::bitset objects in the evaluation of a constant expression.

std::vector<bool>
    std::vector<bool> is made space efficient (as well as whether it is optimized at all) is implementation defined.
    One potential optimization involves coalescing vector elements such that each element occupies a single bit instead of sizeof(bool) bytes.

**********/

#include <print>
#include <string>
#include <bitset>
#include <array>
#include <vector>

int main() {
    
    constexpr size_t num_of_elems = 8;

    std::println("Array of bool");
    constexpr std::array<bool, num_of_elems> barr{true};
    static_assert(sizeof(barr) == num_of_elems);
    std::println("sizeof(barr) {:>5}", sizeof(barr));
    std::println("barr.size() {:>6}", barr.size());
    std::println("");

    std::println("Vector of bool");
    std::vector<bool> bvec(num_of_elems, true);
    std::println("sizeof(bvec) {:>5}", sizeof(bvec));
    std::println("bvec.size() {:>6}", bvec.size());
    std::println("");

    std::println("Bitset");
    constexpr std::bitset<num_of_elems> bset{true};
    static_assert(bset.size() == num_of_elems);
    std::println("sizeof(bset) {:>5}", sizeof(bset));
    std::println("bset.size() {:>6}", bset.size()); // number of bits    

    return 0;
}

/*****
    END OF FILE
**********/


