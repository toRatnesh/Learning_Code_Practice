/**********

    This example demonstrates about C++23 std::basic_string::resize_and_overwrite
    For more info visit
    https://en.cppreference.com/w/cpp/string/basic_string/resize_and_overwrite
    https://www.youtube.com/watch?v=Ymm0yN_QUQA

    resize_and_overwrite
    template< class Operation >
    constexpr void resize_and_overwrite( size_type count, Operation op );

    Resizes the string to contain at most count characters, 
    using the user-provided operation op to modify the possibly indeterminate contents and set the length.

    This avoids the cost of initializing a suitably-sized std::string 
    when it is intended to be used as a char array to be populated by, e.g., a C API call.

**************/

#include <iostream>

const int LEN = 64;
std::string resize_then_overwrite() {
    std::string result(LEN, 'A');
    //result.resize(LEN);

    unsigned char cur_c = 32; 
    for(auto & c : result) {
        c = cur_c;
        ++cur_c;
    }
    return result;
}

std::string resize_and_overwrite() {
    std::string result;

    result.resize_and_overwrite(LEN, [](char * buf, std::size_t buf_size){
            unsigned char cur_c = 32; 
            for(std::size_t idx = 0; idx < buf_size; ++idx) {
                buf[idx] = cur_c;
                ++cur_c;
            }
            return buf_size;
    });
    return result;
}

int main() {
    {
        std::string res = resize_then_overwrite();
        std::cout << "resize_then_overwrite() " << res << '\n';
    }
    {
        std::string res = resize_and_overwrite();
        std::cout << "resize_and_overwrite() " << res << '\n';
    }    
    
    return 0;
}

/**********
    END OF FILE
**************/


