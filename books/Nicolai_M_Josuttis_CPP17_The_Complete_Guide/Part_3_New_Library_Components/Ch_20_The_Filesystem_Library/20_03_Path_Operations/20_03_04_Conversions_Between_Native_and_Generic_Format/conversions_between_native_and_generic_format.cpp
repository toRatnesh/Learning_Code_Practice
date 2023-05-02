/****

20.3 Path Operations

	std::filesystem::path can be used as an absolute or relative path of a file that might or might not exist
	Because these operations (create, modify, update, inspect) usually do not take the filesystem into account they are cheap to call. As a consequence, they are usually member functions.
	https://en.cppreference.com/w/cpp/filesystem
	https://en.cppreference.com/w/cpp/filesystem/path

20.3.4 Conversions Between Native and Generic Format
	
	std::filesystem::path has member functions for conversion

	======================================================================
	Call					Effect
	======================================================================
	p.generic_string()		yields the path as a generic std::string
	p.generic_string<...>()	yields the path as a generic std::basic_string<...>
	p.native()				yields the path in the native format of type path::string_type
	p.c_str()				yields the path as a character sequence in the native string format
	p.make_preferred()		replaces directory separators in p by native format and yields the modified p
	======================================================================

	For more member functions visit
	https://en.cppreference.com/w/cpp/filesystem/path
	
	generic...()	path functions yields the path converted to the corresponding string format having the generic format
	native()	yields the path converted to the native string encoding
	c_str()		yields the path converted to the native as a null terminated character sequence. This function is not portable.
	make_preferred()	replaces any directory separator except for the root name by the native directory separator. This is the only function that modifies the path it is called for.
	
	NOTE: The native string type is not portable.

*******/

#include <iostream>
#include <filesystem>

int main() {

    std::filesystem::path l_path = "/dir1\\\dir2//dir3/\\.//file";

    std::clog << "Path " << l_path << '\n';
    std::clog << "String Path " << l_path.string() << '\n';
    std::clog << "Generic string Path " << l_path.generic_string() << '\n';
    std::clog << "Native Path " << l_path.native() << '\n';
    std::clog << "Char array Path " << l_path.c_str() << '\n';
    std::clog << "Make preferred Path " << l_path.make_preferred() << '\n';

    return 0;
}

/*****
    END OF FILE
********/


