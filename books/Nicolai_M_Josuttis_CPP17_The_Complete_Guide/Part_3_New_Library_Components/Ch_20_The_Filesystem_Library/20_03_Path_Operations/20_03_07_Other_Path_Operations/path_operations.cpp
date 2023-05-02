/****

20.3 Path Operations

	std::filesystem::path can be used as an absolute or relative path of a file that might or might not exist
	Because these operations (create, modify, update, inspect) usually do not take the filesystem into account they are cheap to call. As a consequence, they are usually member functions.
	https://en.cppreference.com/w/cpp/filesystem
	https://en.cppreference.com/w/cpp/filesystem/path

20.3.7 Other Path Operations

	======================================================================
	Call			Effect
	======================================================================
	p.hash_value()	yields the hash value for a path
	======================================================================

	Only equal paths have the same hash_value.
	For this reason, you might want to normalize paths before you put them in a hash table.

*******/

#include <iostream>
#include <filesystem>

int main() {

    std::filesystem::path l_path1 = "file1";
    std::filesystem::path l_path2 = "tmp/../file1";

    std::clog << "Path " << l_path1.string() << " hash value " << std::filesystem::hash_value(l_path1) << '\n';
    std::clog << "Path " << l_path2.string() << " hash value " << std::filesystem::hash_value(l_path2) << '\n';

    std::clog << "Normalized path " << l_path1.lexically_normal().string() << " hash value " << std::filesystem::hash_value(l_path1.lexically_normal()) << '\n';
    std::clog << "Normalized path " << l_path2.lexically_normal().string() << " hash value " << std::filesystem::hash_value(l_path2.lexically_normal()) << '\n';

    return 0;
}

/*****
    END OF FILE
********/


