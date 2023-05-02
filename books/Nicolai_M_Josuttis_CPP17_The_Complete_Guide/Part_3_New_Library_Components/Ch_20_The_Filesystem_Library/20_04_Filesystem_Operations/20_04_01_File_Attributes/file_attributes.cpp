/*******

References
    C++17 - The Complete Guide | Nicolai M. Josuttis
    https://en.cppreference.com/w/cpp/filesystem
    https://en.cppreference.com/w/cpp/filesystem/file_time_type


20.4 Filesystem Operations
	Expensive filesystem operations that take the current filesystem into account

20.4.1 File Attributes
	Operations for File Types
	============================================================
	Call			Effect
	============================================================
	exists(p)		yields whether there is a file to open
	is_symlink(p)	yields whether the file p exists and is a symbolic link
	is_regular_file(p)		yields whether the file p exists and is a regular file
	is_character_file(p)	yields whether the file p exists and is a character special file
	is_directory(p)		yields whether the file p exists and is a directory
	is_other(p)			yields whether the file exists p and is neither regular nor a directory nor a symbolic link
	is_block_file(p)	yields whether the file p exists and is a block special file
	is_fifo(p)			yields whether the file p exists and is FIFO or pipe file
	is_socket(p)		yields whether the file p exists and is a socket
	============================================================

	The function for the filesystem type match with the corresponding file_type values.
	These function (except is_symlink()) follow symbolic links. That is, for a symbolic link to a directory both is_symlink() and is_directory() yield true.
	For all checks for files that are special files (no regular file, no directory, no symbolic link) is_other() also yields true
	For implementation-specific file types there is no specific convenience function so that for them only is_other() is true (and is_symlink() if we have a symbolic link to such a file).
	To not follow symbolic links, use symlink_status() and call these functions for the returned file_status

	Check for Existence of a File

		// if not done yet, create a symbolic link to file:
		if (!exists(p)) { // OOPS: checks if the file p refers to doesn’t exist
			fs::create_symlink(file, p);
		}

		If p already exists as a symbolic link to a non-existing file, it will try to create the symbolic link at the location where already the symbolic link exists and raise a corresponding exception.

		if (!exists(symlink_status(p))) { // OK: checks if p doesn’t exist yet (as symbolic link)
			...
		}
		Here we use symlink_status(), which yields the status not following symbolic links, to check for the existence of any file at the location of p.

	Other File Attributes
		============================================================
		Call		Effect
		============================================================
		is_empty(p)		yields whether the file is empty
		file_size(p)	yields the size of a file
		hard_link_count(p) yields the number of hard links
		last_write_time(p) yields the timepoint of the last write to a file
		============================================================

		p.empty() // true if path p is empty (cheap operation)
		is_empty(p) // true if file at path p is empty (filesystem operation)

	Dealing with the Last Modification
		last_write_time(p) returns the timepoint of the last modification or write access of the file
		namespace fs {
			using file_time_type = chrono::time_point<trivialClock>;
		}
		The clock type trivialClock is an implementation specific clock type that reflects the resolution and range of file time values.
		The clock used by filesystem timepoint is not guaranteed to be the standard system_clock.
		
        A useful helper to convert any filesystem timepoint to a string
		std::string asString(const fs::file_time_type& ft) {
			using system_clock = std::chrono::system_clock;
			auto t = system_clock::to_time_t(system_clock::now() + (ft - fs::file_time_type::clock::now()));
			// convert to calendar time (including skipping trailing newline):
			std::string ts = ctime(&t);
			ts.resize(ts.size()-1);
			return ts;
		}

******************/

#include <iostream>
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

std::string filePathTimeAsString(const fs::path fp_path) {
    using system_clock = std::chrono::system_clock;
    auto ftime = fs::last_write_time(fp_path);
    auto t = system_clock::to_time_t(system_clock::now() + (ftime - fs::file_time_type::clock::now()));
    // convert to calendar time (including skipping trailing newline):
    std::string ts = ctime(&t);
    ts.resize(ts.size()-1);
    return ts;
}

int main() {

    const fs::path l_dir   = "tmp/testdir";
    const fs::path l_file  =  l_dir/"testfile";
    
    const fs::path l_dir_slink     = "tmp/testdir_slink";
    const fs::path l_file_slink    = "tmp/testfile_slink";

    try {
        create_directories(l_dir);
        create_directory_symlink(l_dir, l_dir_slink);

        std::ofstream ofs{l_file};
        fs::create_symlink(l_file, l_file_slink);

        if(! fs::exists(l_file_slink)) {
            // this is wrong way to check for sysmbolink link because fs::exists follows symbolic link
            //fs::create_symlink(l_file, l_file_slink); // this will generate exception for File exists
        }

        if(! fs::exists(symlink_status(l_file_slink))) {
            // this is correct way to check for symbolic
            fs::create_symlink(l_file, l_file_slink);
        }

        if(fs::is_empty(l_file)) {
            std::clog << "File " << l_file.string() << " is empty\n";
        }

        if(l_file.empty()) {
            std::clog << "File path " << l_file.string() << " is empty\n";
        }
        const fs::path l_empty_path;
        if(l_empty_path.empty()) {
            std::clog << "File path " << l_empty_path.string() << " is empty\n";
        }

        for(const auto & elem : fs::recursive_directory_iterator(fs::current_path())) {
            std::clog << elem.path().string() << '\n';
        }

        auto ftime = fs::last_write_time(l_file);
        auto ftime_diff = fs::file_time_type::clock::now() - ftime;
        auto ftime_duration = std::chrono::duration_cast<std::chrono::seconds>(ftime_diff).count();
        std::clog << "File " << l_file.string() << " is " << ftime_duration << " seconds old\n";

        std::clog << "File " << l_file.string() << " was last modified at " << filePathTimeAsString(l_file) << '\n';

        fs::remove_all("tmp");
    }
    catch(const fs::filesystem_error & fexp) {
        std::clog << "File operation exception: " << fexp.what() << '\n';
        std::clog << "  path1: " << fexp.path1() << '\n';
        std::clog << "  path2: " << fexp.path2() << '\n';
        std::clog << "  Code value: " << fexp.code().value() << '\n';
        std::clog << "  Code message: " << fexp.code().message() << '\n';
        std::clog << "  Code category: " << fexp.code().category().name() << '\n';    
    }

    return 0;
}

/*****
    END OF FILE
********/


