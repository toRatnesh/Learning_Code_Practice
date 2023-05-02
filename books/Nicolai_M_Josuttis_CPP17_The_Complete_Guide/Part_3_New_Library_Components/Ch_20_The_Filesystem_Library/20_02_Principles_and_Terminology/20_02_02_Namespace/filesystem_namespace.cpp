/******

References:
	C++17 - The Complete Guide | Nicolai M. Josuttis
    https://en.cppreference.com/w/cpp/filesystem

20.2 Principles and Terminology

20.2.2 Namespace

The filesystem library has its own sub-namespace filesystem inside std.
It is a pretty common convention to introduce the shortcut fs for it:
	namespace fs = std::filesystem;

Note that not qualifying filesystem calls sometimes results in unintended behavior.

****************/

#include <iostream>
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

int main() {

    try {
	fs::path l_dir = "test_dir";
        if(! fs::create_directory(l_dir)) {
            std::clog << "File path " << l_dir.string() << " already exists\n"; 
        }

        // following three files are same on windows and different on POSIX
        std::ofstream file1{l_dir/"hello.txt"};
        std::ofstream file2{l_dir/"Hello.txt"};
        std::ofstream file3{l_dir/"HELLO.TXT"};

        for(auto const & l_dit : fs::directory_iterator{l_dir}) {
            std::clog << l_dit.path().lexically_normal().string() << '\n';
        }

        fs::path l_path = "/usr/bin";
        if(l_path.is_absolute()) {
            std::clog << l_path.string() << " is absolute\n";
        }
        else if(l_path.is_relative()) {
            std::clog << l_path.string() << " is relative\n";
        }

        fs::remove_all(l_dir);
    }
    catch(const fs::filesystem_error & fexp) {
        std::clog << "File operation exception " << fexp.what() << '\n';
        std::clog << "  path1 " << fexp.path1() << '\n';
        std::clog << "  path2 " << fexp.path2() << '\n';
        std::clog << "  Code value " << fexp.code().value() << '\n';
        std::clog << "  Code message " << fexp.code().message() << '\n';
        std::clog << "  Code category " << fexp.code().category().name() << '\n';
    }

    return 0;
}

/****
    END OF FILE
******/


