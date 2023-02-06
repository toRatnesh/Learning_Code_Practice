/**********

References:
	C++17 - The Complete Guide | Nicolai M. Josuttis
    https://en.cppreference.com/w/cpp/filesystem
    https://en.cppreference.com/w/cpp/filesystem/create_directory
    https://en.cppreference.com/w/cpp/filesystem/create_symlink
    https://en.cppreference.com/w/cpp/filesystem/recursive_directory_iterator

20. The Filesystem Library
	With C++17 the Boost.filesystem library was finally adopted as a C++ standard library.
	
20.1 Basic Examples

20.1.3 Create Different Types of Files

	Creating Directories
		create_directories()	we create all missing directories of the whole passed path
		create_directory()		to create a directory only inside an existing directory
	
		If testDir already exists, create_directories() returns false.
		However, note that it is also not an error, if testDir exists but is not a directory.
		Thus, returning true does not mean that after the call there is a directory with the requested name.
		
	Creating Regular Files
		the creation of a regular file still only can be done with the existing I/O streams library

	Creating Symbolic Links
		create_directory_symlink("test", testDir.parent_path() / "slink");
		create_symlink()
        Creates a symbolic link link with its target set to target as if by POSIX symlink(): the pathname target may be invalid or non-existing
	
	Recursive Directory Iteration
		recursive_directory_iterator()		
        recursive_directory_iterator is a LegacyInputIterator that iterates over the directory_entry elements of a directory, and, recursively, over the entries of all subdirectories.
        The iteration order is unspecified, except that each directory entry is visited only once.
        By default, symlinks are not followed, but this can be enabled by specifying the directory option follow_directory_symlink at construction time.

******************/

#include <iostream>
#include <filesystem>
#include <fstream>

int main(const int argc, const char * const argv[]) {

    if(3 != argc) {
        std::clog << "Usage: " << argv[0] << " <new_dir_name> <new_file_name>\n";
        return 1;
    }

    std::filesystem::path l_dir     = argv[1];
    std::filesystem::path l_file    = l_dir/argv[2];

    try {
        
        if(false == std::filesystem::create_directories(l_dir)) {
            std::clog << "Directory " << l_dir.string() << " creation failed, It already exists\n";
        }

        std::ofstream ofs(l_file);
        if(! ofs) {
            std::clog << "Failed to open file " << l_file.string() << " for writing\n"; 
        }
        else {
            ofs << "Learning C++17 filesystem";
        }

        std::filesystem::create_directory_symlink(l_dir, l_dir.parent_path()/"dslink");

        std::clog << "Present path " << std::filesystem::current_path().string() << " have: \n";
        auto iter_opts{std::filesystem::directory_options::follow_directory_symlink};
        for(const auto & elem : std::filesystem::recursive_directory_iterator(".", iter_opts)) {
            std::clog << " " << elem.path().lexically_normal().string() << '\n';
        }

    } catch(const std::filesystem::filesystem_error & fexp) {
        std::clog << "File operation exception " << fexp.what() << '\n';
        std::clog << "  path1 " << fexp.path1() << '\n';
        std::clog << "  path2 " << fexp.path2() << '\n';
        std::clog << "  Code value " << fexp.code().value() << '\n';
        std::clog << "  Code message " << fexp.code().message() << '\n';
        std::clog << "  Code category " << fexp.code().category().name() << '\n';
    }

    return 0;
}

/*****
    END OF FILE
*********/


