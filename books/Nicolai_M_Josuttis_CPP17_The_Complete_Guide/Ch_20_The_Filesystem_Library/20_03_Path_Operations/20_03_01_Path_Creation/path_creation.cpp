/****

20.3 Path Operations

	std::filesystem::path can be used as an absolute or relative path of a file that might or might not exist
	Because these operations (create, modify, update, inspect) usually do not take the filesystem into account they are cheap to call. As a consequence, they are usually member functions.
	https://en.cppreference.com/w/cpp/filesystem
	https://en.cppreference.com/w/cpp/filesystem/path

20.3.1 Path Creation

	======================================================================
	Call					Effect
	======================================================================
	path(string)			creates path from a string
	path(beg,end)			creates path from a range
	u8path(u8string)		creates path from a UTF-8 string
	current_path()			yields the path of the current working directory
	temp_directory_path()	yields the path for temporary files
	======================================================================

	Note that both current_path() and temp_directory_path() are more expensive operations because they are based on operating system calls. 
	By passing an argument current_path() can also be used to modify the current working directory.

*******/

#include <iostream>
#include <filesystem>
#include <array>

int main() {

    {
        std::filesystem::path l_path;
        if(l_path.empty()) {
            std::clog << "File path is empty\n";
        }
    }

    {
        std::string filename = "testfile";
        std::filesystem::path l_path{filename};
        std::clog << "Path " << l_path.string() << '\n';
    }

    {
        std::array<char, 16> filename{'t', 'e', 's', 't', 'f', 'i', 'l', 'e', '.', 'l', 'o', 'g'};
        std::filesystem::path l_path{filename.begin(), filename.end()};
        std::clog << "Path " << l_path.string() << '\n';
    }

    {
        std::clog << "Current path " << std::filesystem::current_path() << '\n';
    }

    return 0;
}

/*****
    END OF FILE
********/


