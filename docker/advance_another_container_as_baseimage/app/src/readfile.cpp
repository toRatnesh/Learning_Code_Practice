/***************
    This source code is to read a file which path is paased as an argument.
 
 ****************/

#include <iostream>
#include <filesystem>
#include <fstream>
#include <sstream>

#include <thread>
#include <chrono>

bool readFile(const std::filesystem::path filepath) {

    if(filepath.empty()) {
        std::clog << "file path is empty\n";
        return false;
    }

    std::ifstream ifs(filepath);
    auto fsize =  std::filesystem::file_size(filepath);
    std::string buffer(fsize, 0);
    //std::clog << "file size is " << fsize << '\n';

    while(ifs.read(buffer.data(), buffer.size())) {
        std::clog << buffer;
    }
    std::clog << '\n';

    return true;
}

int main(const int argc, const char * const argv[]) {

    if(2 != argc) {
        std::clog << "Usage: bin <filepath_to_read>\n";
        return 1;
    }

    const std::filesystem::path filepath(argv[1]);
    readFile(filepath);

    while(true) {
        std::this_thread::sleep_for(std::chrono::seconds(3600)) ;  
    }

    return 0;
}


/*******
    END OF FILE
 *****/
