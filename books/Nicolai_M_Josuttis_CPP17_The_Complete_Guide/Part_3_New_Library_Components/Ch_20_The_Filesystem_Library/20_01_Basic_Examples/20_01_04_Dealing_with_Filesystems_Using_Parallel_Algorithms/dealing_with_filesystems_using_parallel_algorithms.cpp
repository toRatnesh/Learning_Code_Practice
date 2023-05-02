/**********

References:
	C++17 - The Complete Guide | Nicolai M. Josuttis
    https://en.cppreference.com/w/cpp/filesystem
    https://en.cppreference.com/w/cpp/filesystem/recursive_directory_iterator

20. The Filesystem Library
	With C++17 the Boost.filesystem library was finally adopted as a C++ standard library.
	
20.1 Basic Examples

20.1.4 Dealing with Filesystems Using Parallel Algorithms
	
    Recursive Directory Iteration

		recursive_directory_iterator()		
        recursive_directory_iterator is a LegacyInputIterator that iterates over the directory_entry elements of a directory, and, recursively, over the entries of all subdirectories.
        The iteration order is unspecified, except that each directory entry is visited only once.
        By default, symlinks are not followed, but this can be enabled by specifying the directory option follow_directory_symlink at construction time.

******************/

#include <iostream>
#include <filesystem>
#include <vector>
#include <numeric>
#include <execution>


int main(const int argc, const char * const argv[]) {

    if(2 != argc) {
        std::clog << "Usage: " << argv[0] << " <dir_name>\n";
        return 1;
    }

    std::filesystem::path l_dir     = argv[1];
    std::vector<std::filesystem::path> l_paths_vec;

    try {
        std::filesystem::recursive_directory_iterator l_itr{l_dir};
        std::copy(std::filesystem::begin(l_itr), std::filesystem::end(l_itr), std::back_inserter(l_paths_vec));

    } catch(const std::filesystem::filesystem_error & fexp) {
        std::clog << "File operation exception " << fexp.what() << '\n';
        std::clog << "  path1 " << fexp.path1() << '\n';
        std::clog << "  path2 " << fexp.path2() << '\n';
        std::clog << "  Code value " << fexp.code().value() << '\n';
        std::clog << "  Code message " << fexp.code().message() << '\n';
        std::clog << "  Code category " << fexp.code().category().name() << '\n';
    }

    auto l_size = std::transform_reduce(
        std::execution::par,
        l_paths_vec.cbegin(), l_paths_vec.cend(),
        std::uintmax_t {0},
        std::plus<>(),
        [](const std::filesystem::path & fp_path) {
            return std::filesystem::is_regular_file(fp_path) ? std::filesystem::file_size(fp_path) : std::uintmax_t {0};
        });

    std::clog << "Size of all " << l_paths_vec.size() << " regular files is " << l_size << '\n';

    return 0;
}

/*****
    END OF FILE
*********/


