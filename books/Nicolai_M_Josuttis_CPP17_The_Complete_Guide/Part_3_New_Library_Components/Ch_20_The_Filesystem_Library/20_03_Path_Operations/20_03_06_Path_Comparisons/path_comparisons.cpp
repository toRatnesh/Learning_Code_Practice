/****

20.3 Path Operations

	std::filesystem::path can be used as an absolute or relative path of a file that might or might not exist
	Because these operations (create, modify, update, inspect) usually do not take the filesystem into account they are cheap to call. As a consequence, they are usually member functions.
	https://en.cppreference.com/w/cpp/filesystem
	https://en.cppreference.com/w/cpp/filesystem/path

20.3.6 Path Comparisons
	The operations you can use to compare two different paths:
	======================================================================
	Call Effect
	======================================================================
	p1 == p2		yields whether two paths are equal
	p1 != p2		yields whether two paths are not equal
	p1 < p2			yields whether a paths is less than another
	p1 <= p2		yields whether a path is less or equal than another
	p1 >= p2		yields whether a path is greater or equal than another
	p1 > p2			yields whether a path is greater than another
	p.compare(p2)	yields whether p2 is less, equal, or greater than p
	p.compare(sv)	yields whether p2 is less, equal, or greater than the string (view) sv converted to a path
	equivalent(p1, p2)	expensive path comparison taking the filesystem into account
	======================================================================
	
	most of the comparisons don’t take the filesystem into account, which means that they operate only lexically, which is cheap but may result in surprising return values
	If you want to take the filesystem into account so that symbolic links are correctly handled, you can use equivalent().
	A generic way to compare paths as accurate as possible (but not having the best performance) is as follows:
	bool pathsAreEqual(const std::filesystem::path& p1, const std::filesystem::path& p2) {
		return exists(p1) && exists(p2) ? equivalent(p1, p2) : p1.lexically_normal() == p2.lexically_normal();
	}
	
*******/

#include <iostream>
#include <filesystem>

// Thus, a generic way to compare paths as accurate as possible (but not having the best performance)
bool paths_are_equal(
    const std::filesystem::path& p1,
    const std::filesystem::path& p2) 
{
        return exists(p1) && exists(p2) ? 
            equivalent(p1, p2) : 
            p1.lexically_normal() == p2.lexically_normal();
}

int main() {

    std::filesystem::path l_path1 = "file1";
    std::filesystem::path l_path2 = "tmp/../file1";

    if(l_path1 == l_path2) {
        std::clog << "Path " << l_path1.string() << " and " << l_path2.string() << " are equal\n";
    }

    if(! l_path1.compare(l_path2)) {
        std::clog << "Path " << l_path1.string() << " and " << l_path2.string() << " are equal\n";
    }

    if(l_path1.lexically_normal() == l_path2.lexically_normal()) {
        std::clog << "Normalized Path for " << l_path1.string() << " and " << l_path2.string() << " are equal\n";
    }

    if(paths_are_equal(l_path1, l_path2)) {
        std::clog << "Normalized Path for " << l_path1.string() << " and " << l_path2.string() << " are equal\n";
    }

    return 0;
}

/*****
    END OF FILE
********/


