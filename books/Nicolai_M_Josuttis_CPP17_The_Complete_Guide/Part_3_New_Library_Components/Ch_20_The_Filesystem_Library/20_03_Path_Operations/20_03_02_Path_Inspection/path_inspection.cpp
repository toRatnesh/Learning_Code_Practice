/****

20.3 Path Operations

	std::filesystem::path can be used as an absolute or relative path of a file that might or might not exist
	Because these operations (create, modify, update, inspect) usually do not take the filesystem into account they are cheap to call. As a consequence, they are usually member functions.
	https://en.cppreference.com/w/cpp/filesystem
	https://en.cppreference.com/w/cpp/filesystem/path

20.3.2 Path Inspection

	std::filesystem::path has various member functions for Path Inspection.
	These operations do not take the filesystem into account and are therefore member functions of a path.
	The result of these operations might depend on the operation system.

	======================================================================
	Call				Effect
	======================================================================
	p.empty()			yields whether a path is empty
	p.is_absolute()		yields whether a path is absolute
	p.is_relative()		yields whether a path is relative
	p.has_filename()	yields whether a path neither a directory nor a root name
	p.has_root_name()	yields whether a path has a root name
	p.has_root_path()	yields whether a path has a root name or a root directory
	p.filename()		yields the filename (or the empty path)
	p.root_name()		yields the root name (or the empty path)
	p.root_path()		yields the root elements (or the empty path)
	p.begin()			begin of a path iteration
	p.end()				end of a path iteration
	======================================================================

	For more member functions visit 
	https://en.cppreference.com/w/cpp/filesystem/path

	The has_...() functions check whether the corresponding functions without has_ yield an empty path.

	If a path has a filename it also always has a stem (generic-format path stripped of its extension).
	The empty path is a relative path (yielding false or an empty path for all other operations beside is_empty() and is_relative()).

	Path Iteration
		You can iterate over a path, which yields the elements of the path: the root name if any, the root directory if any, and all the filenames. 
		If the path ends with a directory separator, the last element is an empty filename.

		The iterator is a bidirectional iterator. The values the iterators refer to are of type path. 
		However, two iterators iterating over the same path might not refer to the same path object even if they refer to the same element.

		To check whether a path p ends with a directory separator you can implement:

		if (!p.empty() && (--p.end())->empty()) {
			std::cout << p << " has a trailing separator\n";
		}

*******/

#include <iostream>
#include <filesystem>
#include <array>

int main() {

    std::filesystem::path l_path = std::filesystem::current_path() / "testfile.log";
    std::clog << "Path " << l_path.string() << '\n';

    if(l_path.empty()) {
        std::clog << "Path " << l_path.string() << " is empty\n";
    }
    else {
        std::clog << "Path " << l_path.string() << " is not empty\n";
    }

    if(l_path.is_absolute()) {
        std::clog << "Path " << l_path.string() << " is absolute\n";
    }

    if(l_path.is_relative()) {
        std::clog << "Path " << l_path.string() << " is relative\n";
    }

    if(l_path.has_filename()) {
        std::clog << "Path " << l_path.string() << ", filename " << l_path.filename() << '\n';
    }

    if(l_path.has_stem()) {
        std::clog << "Path " << l_path.string() << ", stem " << l_path.stem() << '\n';
    }

    if(l_path.has_extension()) {
        std::clog << "Path " << l_path.string() << ", extension " << l_path.extension() << '\n';
    }

    if(l_path.has_root_name()) {
        std::clog << "Path " << l_path.string() << ", root name " << l_path.root_name() << '\n';
    }

    if(l_path.has_root_directory()) {
        std::clog << "Path " << l_path.string() << ", root directory " << l_path.root_directory() << '\n';
    }

    if(l_path.has_root_path()) {
        std::clog << "Path " << l_path.string() << ", root path " << l_path.root_path() << '\n';
    }

    if(l_path.has_parent_path()) {
        std::clog << "Path " << l_path.string() << ", parent path " << l_path.parent_path() << '\n';
    }

    if(l_path.has_relative_path()) {
        std::clog << "Path " << l_path.string() << ", relative path " << l_path.relative_path() << '\n';
    }

    std::clog << "=== Path Iteration ===\n";
    for(auto l_pos = l_path.begin(); l_pos != l_path.end(); ++l_pos) {
        std::clog << *l_pos << ", ";
    }
    std::clog << '\n';

    {
	    std::filesystem::path l_cur_path = std::filesystem::current_path();
	    if(! l_cur_path.empty() && (--l_cur_path.end())->empty()) {
		    std::clog << "Path " << l_cur_path.string() << " has a trailing directory separator\n";
	    } 
	    else {
		    std::clog << "Path " << l_cur_path.string() << " has no trailing directory separator\n";
	    }
    }

    {
	    std::filesystem::path l_cur_path = std::filesystem::current_path().concat("/");
	    if(! l_cur_path.empty() && (--l_cur_path.end())->empty()) {
		    std::clog << "Path " << l_cur_path.string() << " has a trailing directory separator\n";
	    } 
	    else {
		    std::clog << "Path " << l_cur_path.string() << " has no trailing directory separator\n";
	    }

    } 

    return 0;
}

/*****
    END OF FILE
********/


