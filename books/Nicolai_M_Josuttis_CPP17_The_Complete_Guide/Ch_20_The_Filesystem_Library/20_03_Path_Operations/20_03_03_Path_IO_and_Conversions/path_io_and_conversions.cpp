/****

20.3 Path Operations

	std::filesystem::path can be used as an absolute or relative path of a file that might or might not exist
	Because these operations (create, modify, update, inspect) usually do not take the filesystem into account they are cheap to call. As a consequence, they are usually member functions.
	https://en.cppreference.com/w/cpp/filesystem
	https://en.cppreference.com/w/cpp/filesystem/path

20.3.3 Path I/O and Conversions

	std::filesystem::path has member functions to read or write and to yield a converted path.
	If you have to deal with paths where symbolic links matter, you might want to use the filesystem-dependent path conversions.

	======================================================================
	Call			Effect
	======================================================================
	strm << p		write the value of a path as quoted string
	strm >> p		reads the value of a path as quoted string
	p.string()		yields the path as a std::string
	p.string<...>()	yields the path as a std::basic_string<...>
	p.lexically_normal()		yields p as normalized path
	p.lexically_relative(p2)	yields the path from p2 to p (empty path if none)
	p.lexically_proximate(p2)	yields the path from p2 to p (p if none)
	======================================================================

	For more member functions visit
	https://en.cppreference.com/w/cpp/filesystem/path

	The lexically_...() functions return a new path, while the other conversion functions yield a corresponding string type.

	Path I/O
		I/O operators write and read paths as quoted strings. You have to convert them to a string to write them without quotes.
		NOTE: reading filenames supports both forms (quoted with a leading " and non-quoted).
		std::filesystem::path tmp;
		std::cin >> tmp;			//	reads quoted and non-quoted paths correctly

	Normalization
		A path can be normalized by following this algorithm:
			If the path is empty, stop.
			Replace each directory-separator (which may consist of multiple slashes) with a single path::preferred_separator.
			Replace each slash character in the root-name with path::preferred_separator.
			Remove each dot and any immediately following directory-separator.
			Remove each non-dot-dot filename immediately followed by a directory-separator and a dot-dot, along with any immediately following directory-separator.
			If there is root-directory, remove all dot-dots and any directory-separators immediately following them.
			If the last filename is dot-dot, remove any trailing directory-separator.
			If the path is empty, add a dot (normal form of ./ is .)

		Nevertheless, it is a good approach to use lexically_normal() to remove the leading dot when iterating over the current directory.

	Relative Path

		Both lexically_relative() and lexically_proximate() can be called to compute the relative path between two paths.
		The only difference is the behavior if there is no path, In that case:
		p.lexically_relative(p2)	yields the empty path if there is no relative path from p2 to p
		p.lexically_proximate(p2)	yields p if there is no relative path from p2 to p
		
		As both operations operate lexically, the actual filesystem (with possible symbolic links) and the current_path() are not taken into account. 
		If both paths are equal, the relative path is ".".
		
	Conversions to Strings
		With u8string() you can use the path as UTF-8 string,

		std::vector<std::string> utf8paths; // std::u8string with C++20
		for (const auto& entry : fs::directory_iterator(p)) {
			utf8paths.push_back(entry.path().u8string());
		}

		NOTE: you should not use a function c_str(), which is also provided, because it converts to the native string format, which might be a wchar_t so that you, for example, have to use std::wcout instead of std::cout to write it to a stream.

*******/

#include <iostream>
#include <filesystem>
#include <array>

int main() {
    
    std::filesystem::path l_path{"/tmp/dir/../filename.log"};
    std::clog << "Path " << l_path.string() << '\n';
    std::clog << "Normalized path " << l_path.lexically_normal().string() << '\n';

    {
        std::filesystem::path path1 = "a/b";
        std::filesystem::path path2 = "a/b";
        std::clog << "Path-1 " << path1.string() << '\n';
        std::clog << "Path-2 " << path2.string() << '\n';
        std::clog << R"(path1.lexically_relative(path2)  )" << path1.lexically_relative(path2) << '\n';
    }

    {
        std::filesystem::path path1 = "/a/b";
        std::filesystem::path path2 = "a/b";
        std::clog << "Path-1 " << path1.string() << '\n';
        std::clog << "Path-2 " << path2.string() << '\n';
        std::clog << R"(path1.lexically_relative(path2)  )" << path1.lexically_relative(path2) << '\n';
    }

    {
        std::filesystem::path path1 = "a/b/c";
        std::filesystem::path path2 = "a/b";
        std::clog << "Path-1 " << path1.string() << '\n';
        std::clog << "Path-2 " << path2.string() << '\n';
        std::clog << R"(path1.lexically_relative(path2)  )" << path1.lexically_relative(path2) << '\n';
    }

    return 0;
}

/*****
    END OF FILE
********/


