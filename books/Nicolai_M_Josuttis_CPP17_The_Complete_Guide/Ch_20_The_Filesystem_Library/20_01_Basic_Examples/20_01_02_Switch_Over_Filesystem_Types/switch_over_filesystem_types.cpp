/**********

References:
	C++17 - The Complete Guide | Nicolai M. Josuttis
    https://en.cppreference.com/w/cpp/filesystem
    https://en.cppreference.com/w/cpp/filesystem/status
    https://en.cppreference.com/w/cpp/filesystem/file_status/type
    https://en.cppreference.com/w/cpp/filesystem/file_type

20. The Filesystem Library
	With C++17 the Boost.filesystem library was finally adopted as a C++ standard library.
	
20.1 Basic Examples

20.1.2 Switch Over Filesystem Types

    The expression status(p).type() creates a file_status, for which type() creates a file_type.
    This way we can just directly handle the different types instead of following a chain of calls like is_regular_file(), is_directory(), and so on.

    Note also that implementation-specific file_type might exist. For example, Windows provides the special file type junction. However using it is not portable.

    Important functions

    std::filesystem::file_status status( const std::filesystem::path& p );
    std::filesystem::file_status status( const std::filesystem::path& p, std::error_code& ec ) noexcept;

    std::filesystem::file_type type() const noexcept;
    void type( std::filesystem::file_type type ) noexcept;

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

******************/

#include <iostream>
#include <filesystem>

int main(const int argc, const char * const argv[]) {
    if(2 != argc) {
        std::clog << "Usage: " << argv[0] << " <a_file>\n";
        return 1;
    }

    switch(std::filesystem::path l_file = argv[1]; std::filesystem::status(l_file).type()) {

        case std::filesystem::file_type::regular: 
            {
                std::clog << "File " << l_file.string() << " has " << file_size(l_file) << " bytes" << '\n';
            }
            break;
        case std::filesystem::file_type::directory:
            {
                std::clog << "Directory " << l_file.string() << " contents: \n";
                for(const auto & elem : std::filesystem::directory_iterator(l_file)) {
                    std::clog << elem.path().string() << '\n'; // portable version
                    //std::clog << elem.path() << '\n';
                }
            }
            break;
        case std::filesystem::file_type::symlink:
            {
                std::clog << "File " << l_file.string() << " is a symbolic link file\n";
            }
            break;
        default:
            {
                std::clog << "File " << l_file.string() << " does not exist\n";
            }
    }

    return 0;
}

/*****
    END OF FILE
*********/


