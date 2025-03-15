/*****

References

    episode https://www.youtube.com/watch?v=-f5HmDR0GGY
    This episode demonstrates about execution of program in case it runs out of memory

**********/

#include <iostream>
#include <vector>

constexpr size_t vsize = 1024 * 1024 * 256;

void empty_vectors() {
    std::vector<std::vector<int>> data;
    int index = 1;
    while(true) {
        std::vector<int> elems;
        elems.reserve(vsize);
        data.push_back(std::move(elems));
        std::cout << "Iteration " << index << ", reserved " << vsize << " ints, Total bytes reserved " << (index * vsize * sizeof(int)) << std::endl;
        ++index;
    }   
}

void filled_vectors() {
    std::vector<std::vector<int>> data;
    int index = 1;
    while(true) {
        std::vector<int> elems(vsize, index);
        //elems.reserve(vsize);
        data.push_back(std::move(elems));
        std::cout << "Iteration " << index << ", reserved " << vsize << " ints, Total bytes reserved " << (index * vsize * sizeof(int)) << std::endl;
        ++index;
    }   
}

int main() {
    
    //empty_vectors();
    filled_vectors();
    
    return 0;
}

/*****
    END OF FILE
**********/


