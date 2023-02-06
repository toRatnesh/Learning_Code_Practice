/*******

References
    C++17 - The Complete Guide | Nicolai M. Josuttis
    https://en.cppreference.com/w/cpp/filesystem
    https://en.cppreference.com/w/cpp/filesystem/space

20.4 Filesystem Operations
	Expensive filesystem operations that take the current filesystem into account

20.4.6 Other Filesystem Operations

	============================================================
	Call				Effect
	============================================================
	equivalent(p1, p2)	yields whether p1 and p2 refer to the same file
	space(p)			yields information about the disk space available at path p
	current_path(p)		sets the path of the current working directory to p
	============================================================

	The return value of space() is the following structure:
	namespace std::filesystem {
		struct space_info {
			uintmax_t capacity;     // total size of the filesystem, in bytes
			uintmax_t free;         // free space on the filesystem, in bytes
			uintmax_t available;    // free space available to a non-privileged process (may be equal or less than free)
		};
	}

	auto [cap, _, avail] = std::filesystem::space("/");
	std::cout << std::fixed << std::precision(2) << avail/1.0e6 << " of " << cap/1.0e6 << " MB available\n\n";

******************/

#include <iostream>
#include <filesystem>
#include <fstream>
#include <iomanip>

namespace fs = std::filesystem;

void display_recursive_dir(const fs::path fp_dir) {
    std::clog << "Directory " << fp_dir.string() << " contains: \n";
    for(const auto & elem : fs::recursive_directory_iterator(fp_dir)) {
        std::clog << elem.path().string() << '\n';
    }
    std::clog << '\n';
}

int main() {
    fs::path l_work_dir   = "tmp";
    fs::path l_dir        = l_work_dir/"testdir";
    fs::path l_file       = l_dir/"testfile";

    try {

        fs::create_directories(l_dir);
        std::ofstream ofs{l_file};
        display_recursive_dir(fs::current_path());

        fs::path l_file1 = l_work_dir/"file1";
        fs::path l_file2 = l_work_dir/"file1";
        std::ofstream ofs1{l_file1};

        std::clog << R"(fs::equivalent(l_file1, l_file2)    )" << fs::equivalent(l_file1, l_file2) << '\n';
        std::clog << R"(fs::equivalent(l_file, l_file2)    )" << fs::equivalent(l_file, l_file2) << "\n\n";

        std::clog << "Current path is " << fs::current_path() << '\n';
        fs::current_path(l_work_dir);
        std::clog << "Current path is " << fs::current_path() << "\n\n";
        fs::current_path("../");
        std::clog << "Current path is " << fs::current_path() << "\n\n";

        auto [cap, _, avail] = fs::space("/");
        std::cout << std::fixed << std::setprecision(2) << avail/1.0e6 << " of " << cap/1.0e6 << " MB available\n";

        fs::remove_all(l_work_dir);
    }
    catch(const fs::filesystem_error & fexp) {
        std::clog << "File operation exception: \n" << fexp.what() << '\n';
        std::clog << "  path1: " << fexp.path1() << '\n';
        std::clog << "  path2: " << fexp.path2() << '\n';
        std::clog << "  Code value: " << fexp.code().value() << '\n';
        std::clog << "  Code message: " << fexp.code().message() << '\n';
        std::clog << "  Code category: " << fexp.code().category().name() << '\n';    
    }

    return 0;
}

/*****
    END OF FILE
********/


