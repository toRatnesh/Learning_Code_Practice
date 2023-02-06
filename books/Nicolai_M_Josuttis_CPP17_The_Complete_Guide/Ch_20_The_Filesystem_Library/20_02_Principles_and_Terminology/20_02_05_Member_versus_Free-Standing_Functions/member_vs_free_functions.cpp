/******

References:
	C++17 - The Complete Guide | Nicolai M. Josuttis
    https://en.cppreference.com/w/cpp/filesystem
    https://en.cppreference.com/w/cpp/filesystem/path

20.2 Principles and Terminology

20.2.5 Member versus Free-Standing Functions

	Member functions are cheap. They are pure lexical operations that do not take the actual filesystem into account, so that no operating systems calls are necessary.

	Free-standing functions are expensive, because they usually take the actual filesystem into account, so that no operating systems calls are necessary.

	Due to argument dependent lookup (ADL) usually you don’t have to specify the full namespace std::filesystem, when calling free-standing filesystem functions and an argument has a filesystem specific type.
	create_directory(std::filesystem::path{"tmpdir"});	// OK
	remove(std::filesystem::path{"tmpdir"});			// OK

****************/

#include <iostream>
#include <filesystem>

void display(std::filesystem::path fp_path1, std::filesystem::path fp_path2) {
	std::clog << "First file:  " << fp_path1.string() << '\n';
	std::clog << "Second file: " << fp_path2.string() << '\n';
	std::clog << "Relative path: \n";
	std::clog << fp_path1.lexically_relative(fp_path2).string() << '\n';
	std::clog << std::filesystem::relative(fp_path1, fp_path2).string() << '\n';
	std::clog << '\n';
}

int main() {

    try {
        {
            std::filesystem::path l_path1 = "test/file";
            std::filesystem::path l_path2 = "test/file";
	    display(l_path1, l_path2);
        }
        {
            std::filesystem::path l_path1 = "test/file1";
            std::filesystem::path l_path2 = "test/file2";
	    display(l_path1, l_path2);
        }
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


