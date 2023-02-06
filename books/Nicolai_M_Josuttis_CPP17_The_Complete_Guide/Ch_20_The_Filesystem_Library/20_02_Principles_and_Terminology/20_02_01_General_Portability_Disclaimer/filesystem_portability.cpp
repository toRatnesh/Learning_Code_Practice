/******

References:
	C++17 - The Complete Guide | Nicolai M. Josuttis
    https://en.cppreference.com/w/cpp/filesystem

20.2 Principles and Terminology

20.2.1 General Portability Disclaimer

The C++ standard does not only standardize what all possible operating systems have in common for their file systems. 
In many cases, it follows POSIX standards and the C++ standard requests to follow POSIX as close as possible.
If no reasonable behavior is possible, an implementation shall report an error.

Possible examples for such errors are:

• Characters are used for filenames that are not supported
• File system elements are created that are not supported (e.g., symbolic links)
• Case sensitivity:
	"hello.txt" and "Hello.txt" and "hello.TXT" might refer to the same (Windows) or three different files (POSIX-based)
• Absolute versus relative paths:
	On some systems "/bin" is an absolute path (POSIX-based), while on others it is not (Windows)

****************/

#include <iostream>
#include <filesystem>
#include <fstream>

int main() {

    
    try {
        std::filesystem::path l_dir = "test_dir";
        if(! std::filesystem::create_directory(l_dir)) {
            std::clog << "File path " << l_dir.string() << " already exists\n"; 
        }

        // following three files are same on windows and different on POSIX
        std::ofstream file1{l_dir/"hello.txt"};
        std::ofstream file2{l_dir/"Hello.txt"};
        std::ofstream file3{l_dir/"HELLO.TXT"};

        for(auto const & l_dit : std::filesystem::directory_iterator{l_dir}) {
            std::clog << l_dit.path().lexically_normal().string() << '\n';
        }

        std::filesystem::path l_path = "/usr/bin";
        if(l_path.is_absolute()) {
            std::clog << l_path.string() << " is absolute\n";
        }
        else if(l_path.is_relative()) {
            std::clog << l_path.string() << " is relative\n";
        }

        std::filesystem::remove_all(l_dir);
    }
    catch(const std::filesystem::filesystem_error & fexp) {
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


