/**********

References:
	C++17 - The Complete Guide | Nicolai M. Josuttis
	https://en.cppreference.com/w/cpp/filesystem
	https://en.cppreference.com/w/cpp/filesystem/directory_iterator
	
20. The Filesystem Library
	With C++17 the Boost.filesystem library was finally adopted as a C++ standard library.
	
20.1 Basic Examples

20.1.1 Print Attributes of a Passed Filesystem Path
	paths by default are written quoted is an issue under Windows, because the usual directory separator backslash is then always escaped and written twice
	Writing paths quoted ensures that the written filenames can be read into a program so that you getback the original filenames
	for standard output, this is usually not acceptable
	For this reason, a portable version also running well under Windows should avoid writing paths quoted to standard output by using the member function string()

	Important Non-member functions
		copy		copies files or directories
		copy_file	copies file contents
		create_directory
		create_directories	creates new directory
		current_path		returns or sets the current working directory
		exists		checks whether path refers to existing file system object
		file_size	returns the size of a file
		remove		removes a file or empty directory
		remove_all	removes a file or directory and all its contents, recursively
		rename		moves or renames a file or directory

	File types
		is_block_file		checks whether the given path refers to block device
		is_character_file	checks whether the given path refers to a character device
		is_directory		checks whether the given path refers to a directory
		is_empty			checks whether the given path refers to an empty file or directory
		is_fifo				checks whether the given path refers to a named pipe
		is_other			checks whether the argument refers to an other file
		is_regular_file		checks whether the argument refers to a regular file
		is_socket			checks whether the argument refers to a named IPC socket
		is_symlink			checks whether the argument refers to a symbolic link
		status_known		checks whether file status is known

	std::filesystem::directory_iterator
		https://en.cppreference.com/w/cpp/filesystem/directory_iterator
	
******************/

#include <iostream>
#include <filesystem>

int main(const int argc, const char * const argv[]) {
    if(2 != argc) {
        std::clog << "Usage: " << argv[0] << " <a_file>\n";
        return 1;
    }

    std::filesystem::path l_file = argv[1];

    if(is_regular_file(l_file)) {
        std::clog << "File " << l_file.string() << " has " << file_size(l_file) << " bytes" << '\n';
    }
    else if(is_directory(l_file)) {
        std::clog << "Directory " << l_file.string() << " contents: \n";
        for(const auto & elem : std::filesystem::directory_iterator(l_file)) {
            std::clog << elem.path().string() << '\n'; // portable version
            //std::clog << elem.path() << '\n';
        }
    }
    else if(exists(l_file)) {
        std::clog << "File " << l_file.string() << " is a special file\n";
    }
    else {
        std::clog << "File " << l_file.string() << " does not exist\n";
    }

    return 0;
}

/*****
    END OF FILE
*********/


