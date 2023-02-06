/****

20.3 Path Operations

	std::filesystem::path can be used as an absolute or relative path of a file that might or might not exist
	Because these operations (create, modify, update, inspect) usually do not take the filesystem into account they are cheap to call. As a consequence, they are usually member functions.
	https://en.cppreference.com/w/cpp/filesystem
	https://en.cppreference.com/w/cpp/filesystem/path

20.3.5 Path Modifications
	The operations that allow us to modify paths:
	
	======================================================================
	Call				Effect
	======================================================================
	p = p2				assign a new path
	p = sv				assign a string (view) as a new path
	p.assign(p2)		assign a new path
	p.assign(sv)		assign a string (view) as a new path
	p.assign(beg, end)	assign elements of the range from beg to end to the path
	p1 / p2				yields the path concatenating p2 as sub-path of p1
	p /=				sub appends sub as sub-path to path p
	p.append(sub)		appends sub as sub-path to path p
	p.append(beg, end)	appends elements of the range from beg to end as sub-paths to path p
	p +=				str appends the characters of str to path p
	p.concat(sub)		appends the characters of str to path p
	p.concat(beg, end)	appends elements of the range from beg to end to path p
	p.replace_filename(repl)	replace the trailing filename (if any)
	p.replace_extension(repl)	replace the trailing filename extension (if any)
	p.clear()			make the path empty
	p.swap(p2)			swap the values of two paths
	swap(p1, p2)		swap the values of two paths
	p.make_preferred()	replaces directory separators in p by native format and yields the modified p
	======================================================================

	For more member functions visit
	https://en.cppreference.com/w/cpp/filesystem/path

	+= and concat() just append new characters to a path, /, /=, and append() add a sub path separated with the current directory separator
	NOTE: appending an absolute sub-path means replacing an existing path.
	For root elements it also matters whether a new element is assigned.
	make_preferred()	converts the directory separators inside a path to the native format
	replace_extension()	replaces, adds, or removes an extension
		It doesn’t matter whether you place a leading dot in the replacement. 
		The function ensures that there is exactly one dot between the stem and the extension of the resulting filename.
		Note that filenames that are “pure extensions” (such as .git) don’t count as extensions. (Since C++17)

*******/

#include <iostream>
#include <filesystem>

int main() {

    std::filesystem::path l_path1 = "tmp/file1";
    std::filesystem::path l_path2 = "file2";

    {
        std::filesystem::path l_path1 = "tmp/file1";
        std::clog << "Path " << l_path1.string() << ',';
        l_path1 += ".git";
        std::clog << R"( path+=.git )" << l_path1.string() << '\n';
    }

    {
        std::filesystem::path l_path1 = "tmp/file1";
        std::clog << "Path " << l_path1.string() << ',';
        l_path1 /= ".git";
        std::clog << R"( path/=.git )" << l_path1.string() << '\n';
    }    
    
    {
        std::filesystem::path l_path1 = "tmp/file1";
        std::clog << "Path " << l_path1.string() << ',';
        l_path1.concat(".git");
        std::clog << R"( path.concat(.git) )" << l_path1.string() << '\n';
    }  

    {
        std::filesystem::path l_path1 = "tmp/file1";
        std::clog << "Path " << l_path1.string() << ',';
        l_path1.append(".git");
        std::clog << R"( path.append(.git) )" << l_path1.string() << '\n';
    }
    
    {
        std::clog << "=== Replace File Extension ===\n";

        std::filesystem::path file = "/tmp/dir/file.txt";
        std::clog << "File " << file.string() << ',' << R"( file.replace_extension(log) )" << file.replace_extension("log") << '\n';
        std::clog << "File " << file.string() << ',' << R"( file.replace_extension(\"\") )" << file.replace_extension("") << '\n';
        std::clog << "File " << file.string() << ',' << R"( file.replace_extension(.ini) )" << file.replace_extension(".ini") << '\n';
        std::clog << "File " << file.string() << ',' << R"( file.replace_extension() )" << file.replace_extension() << '\n';
    }

    {
        std::clog << "=== Appending File ===\n";
        auto path1 = std::filesystem::path("tmp") / "dir";
        std::clog << "Path " << path1.string() << '\n';
        auto path2 = std::filesystem::path("tmp") / "/dir";
        std::clog << "Path " << path2.string() << '\n';
    }

    return 0;
}

/*****
    END OF FILE
********/


