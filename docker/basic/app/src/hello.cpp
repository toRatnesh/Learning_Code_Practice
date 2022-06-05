/***************
    This source code is to read a file which path is paased as an argument.
 
 ****************/

#include <iostream>
#include <filesystem>
#include <fstream>

#include <thread>
#include <chrono>

int main(const int argc, const char * const argv[]) {

    const std::string buffer("Learning docker");
    while(true) {
        std::clog << buffer << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(10)) ; 
    }
    return 0;
}


/*******
    END OF FILE
 *****/
