/******

References:
	C++17 - The Complete Guide | Nicolai M. Josuttis
    https://en.cppreference.com/w/cpp/filesystem
    https://en.cppreference.com/w/cpp/filesystem/filesystem_error
    https://en.cppreference.com/w/cpp/error/error_code

20.2 Principles and Terminology

20.2.6 Error Handling

	In principle you can’t ensure in ahead that the next filesystem operation will succeed.
	Thus, usually the best approach is to perform one or more filesystem operations and deal with resulting exceptions or errors.

	Note also that when reading/writing with regular files the I/O streams library by default does not throw on errors. 
	It converts any operation to a no-op instead.

	filesystem library uses a mixed approach when dealing with the filesystem:
	1. By default (without an additional error handling argument) the operations throw a filesystem_error exceptions on errors.
	2. By passing an additional out parameter, you can instead get an error code on error.

	Using filesystem_error Exceptions
	
	try {
		...
		if (!create_directory(p)) { // exception on error (unless path exists)
			std::cout << p << " already exists\n"; // path exists
		}
		...
	}
	catch (const std::filesystem::filesystem_error& e) { // derived from std::exception
		std::cout << "EXCEPTION: " << e.what() << '\n';
		std::cout << " path: " << e.path1() << '\n';
	}

	filesystem exceptions provide the usual standard exception API to yield an implementationspecific error message with what(). However, it also provides path1() if a path is involved and even path2() if a second path is involved.


	Using error_code Arguments
	
	std::error_code ec;
	if (!create_directory(p, ec)) { // set error code on error
		std::cout << "can't create directory " << p << "\n"; // any error occurred
		std::cout << "error: " << ec.message() << "\n";
	}

	However, not all filesystem operations provide this ability (because they return some value in the normal case).
	Type error_code was introduced with C++11 including a list of portable error conditions such as std::errc::read_only_filesystem. On POSIX system these map to errno values.

****************/

#include <iostream>
#include <filesystem>
#include <fstream>
#include <system_error>

int main() {

    try {
        std::filesystem::path l_dir = "/root/test";
        if(! std::filesystem::create_directory(l_dir)) {
            std::clog << "File path " << l_dir.string() << " already exists\n"; 
        }

        std::filesystem::remove_all(l_dir);
    }
    catch(const std::filesystem::filesystem_error & fexp) {
        std::clog << "File operation exception: " << fexp.what() << '\n';
        std::clog << "  path1: " << fexp.path1() << '\n';
        std::clog << "  path2: " << fexp.path2() << '\n';
        std::clog << "  Code value: " << fexp.code().value() << '\n';
        std::clog << "  Code message: " << fexp.code().message() << '\n';
        std::clog << "  Code category: " << fexp.code().category().name() << '\n';
    }

    std::filesystem::path l_dir = "/root/test";
    std::error_code l_ec;
    if(! std::filesystem::create_directory(l_dir, l_ec)) {
        std::clog << "Error, value: " << l_ec.value() << " message: " << l_ec.message() << '\n'; 
    }    

    return 0;
}

/****
    END OF FILE
******/


