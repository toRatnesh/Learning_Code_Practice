/******

References:
	C++17 - The Complete Guide | Nicolai M. Josuttis
    https://en.cppreference.com/w/cpp/filesystem
    https://en.cppreference.com/w/cpp/filesystem/file_type

20.2 Principles and Terminology

20.2.7 File Types

	Different operating systems support different file types.
	There is an enumeration type file_type, which is standardized to have the following values

	enum class file_type {
		none		= // unspecified,
		not_found	= // unspecified,
		regular		= // unspecified,
		directory	= // unspecified,
		symlink		= // unspecified,
		block		= // unspecified,
		character	= // unspecified,
		fifo		= // unspecified,
		socket		= // unspecified,
		unknown		= // unspecified,
		// implementation-defined 
	};

****************/

#include <iostream>
#include <filesystem>
#include <fstream>
#include <system_error>

int main(const int argc, const char * const argv[]) {
    if(2 != argc) {
        std::clog << "Usage: " << argv[0] << " <a_file>\n";
        return 1;
    }

    switch(std::filesystem::path l_file = argv[1]; std::filesystem::status(l_file).type()) {

        case std::filesystem::file_type::regular: 
            {
                std::clog << "File " << l_file.string() << " is a regular file"<< '\n';
            }
            break;
        case std::filesystem::file_type::directory:
            {
                std::clog << "File " << l_file.string() << " is a directory"<< '\n';
            }
            break;
        case std::filesystem::file_type::symlink:
            {
                std::clog << "File " << l_file.string() << " is a symbolic link\n";
            }
            break;
        default:
            {
                std::clog << "File " << l_file.string() << " does not exist\n";
            }
    }

    return 0;
}

/****
    END OF FILE
******/


