/******

References:
	C++17 - The Complete Guide | Nicolai M. Josuttis
    https://en.cppreference.com/w/cpp/filesystem
    https://en.cppreference.com/w/cpp/filesystem/path

20.2 Principles and Terminology

20.2.3 Paths

	It is a name that represents the (potential) location of a file within a filesystem.
	It consists of an optional root name, an optional root directory, and a sequence of filenames separated by directory separators.
	The path can be relative (so that the file location depends on the current working directory) or absolute.

	Different formats are possible:
	• A generic format, which is portable
	• A native format, which is specific to the underlying file system

	The generic path format is as follows:
		[rootname] [rootdir] [relativepath]
		
	The filesystem library provides function to convert paths between the native and generic format.

	Examples for portable generic paths are:
	//host1/bin/hello.txt
	.
	tmp/
	/a/b//../c

	A path might be empty. This mean that there is no path defined. 
	This is not necessarily the same as ".". What it means depends on the context.

****************/

#include <iostream>
#include <filesystem>

int main() {

    
    try {
        std::filesystem::path l_empty_path;
        std::clog << "Empty file path: " << l_empty_path.string() << '\n';

        auto l_cur_path = std::filesystem::current_path();
        std::clog << "File path: " << l_cur_path.string() << '\n';
        std::clog << "root name: " <<        l_cur_path.root_name() << '\n';
        std::clog << "root directory: " <<   l_cur_path.root_directory() << '\n';
        std::clog << "root path: " <<        l_cur_path.root_path() << '\n';

        std::clog << '\n';
        std::filesystem::path l_path = std::filesystem::current_path()/"test/dir1";
        std::clog << "File path: " << l_path.string() << '\n';
        std::clog << "Generic path: " << l_path.generic_string() << '\n';
        std::clog << "Native path: " << l_path.native().c_str() << '\n';

        std::clog << "root name: " <<        l_path.root_name() << '\n';
        std::clog << "root directory: " <<   l_path.root_directory() << '\n';
        std::clog << "root path: " <<        l_path.root_path() << '\n';

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


