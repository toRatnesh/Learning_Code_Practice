/*******

References
    C++17 - The Complete Guide | Nicolai M. Josuttis
    https://en.cppreference.com/w/cpp/filesystem
    https://en.cppreference.com/w/cpp/filesystem/file_time_type


20.4 Filesystem Operations
	Expensive filesystem operations that take the current filesystem into account

20.4.4 Filesystem Modifications
	Create and Delete Files
	============================================================
	Call Effect
	============================================================
	create_directory(p)				create a directory
	create_directory(p, attrPath)	create a directory with attributes of attrPath
	create_directories(p)			create a directory and all directories above that don’t exists yet
	create_hard_link(old, new)		create another filesystem entry to for the existing file from
	create_symlink(to, new)			create a symbolic link from new to to
	create_directory_symlink(to, new) create a symbolic link from new to the directory to
	copy(from, to)					copy a file of any type
	copy(from, to, options)			copy a file of any type with options
	copy_file(from, to)				copy a file (but not directory or symbolic link)
	copy_file(from, to, options)	copy a file with options
	copy_symlink(from, to)			copy a symbolic link (to refers to where from refers)
	remove(p)						remove a file or empty directory
	remove_all(p)					remove p and recursively all files in its subtree (if any)
	============================================================

	There is no function to create a regular file. This is covered by the I/O Stream standard library.

	After create_directory() or create_directories() returning false you don’t know whether there is already the requested directory or something else. Thus, finding a directory that is already there is not an error. However, finding a file there that is not a directory is also not an error. 

	if you want correct error messages or have to ensure for other reasons that there really is a directory you have to do something like the following:
	if (!create_directory(myPath) && !is_directory(myPath)) {
	std::cerr << "OOPS, \"" << myPath.string() << "\" is already something else\n";
		... // handle this error
	}


	The copy...() functions don’t work with special file types. By default they:
	Report an error if existing files are overwritten
	Don’t operate recursively
	Follow symbolic links

	In both cases remove() and remove_all() symbolic links are removed rather than any file they refer to.

	The bitmask scoped enumeration type copy_options
	============================================================
	copy_options		Effect
	============================================================
	none				Default (value 0)
	skip_existing		Skip overwriting existing files
	overwrite_existing	Overwrite existing files
	update_existing		Overwrite existing files if the new files are newer
	recursive			Recursively copy sub-directories and their contents
	copy_symlinks		Copy symbolic links as symbolic links
	skip_symlinks		Ignore symbolic links
	directories_only	Copy directories only
	create_hard_links	Create additional hard links instead of copies of files
	create_symlinks		Create symbolic links instead of copies of files (the source path must be an absolute path unless the destination path is in the current directory)
	============================================================


	Modify Existing Files
	============================================================
	Call Effect
	============================================================
	rename(old, new)			rename and/or move a file
	last_write_time(p, newtime)	change the timepoint of the last write access
	permissions(p, prms)		replace the permissions of a file by prms
	permissions(p, prms, mode)	modify the permissions of a file according to mode
	resize_file(p, newSize)		change the size of a regular file
	============================================================

	rename()	for symbolic links the link is renamed, not where it refers to
	rename()	needs the full new path including filename to move it to a different directory

	last_write_time() uses the timepoint format as described in Dealing with the Last Modification
	last_write_time(p, std::filesystem::file_time_type::clock::now());

	permissions() uses the permission API format as described in Permissions (20.4.3)
	To switch portably between these two modes, you have to enable or disable all three write flags together (removing one after the other does not work):
	// portable value to enable/disable write access:
	auto allWrite = std::filesystem::perms::owner_write
		| std::filesystem::perms::group_write
		| std::filesystem::perms::others_write;

	// portably remove write access:
	permissions(file, allWrite, std::filesystem::perm_options::remove);

	A shorter way to initialize allWrite (using relaxed enum initialization) would be as follows:
		std::filesystem::perms allWrite{0222};

	resize_file() can be used to reduce or extend the size of a regular file
	resize_file(file, 0);

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

void display_recursive_dir(const fs::path fp_dir) {
    std::clog << "Directory " << fp_dir.string() << " contains: \n";
    for(const auto & elem : fs::recursive_directory_iterator(".")) {
        std::clog << elem.path().string() << '\n';
    }
    std::clog << '\n';
}

int main() {

    fs::path l_work_dir   = "tmp";
    fs::path l_dir        = l_work_dir/"testdir";

    fs::path l_file       = l_dir/"testfile";
    fs::path l_file_slink = l_dir/"testfile_slink";

    try {

        fs::create_directories(l_dir);
        std::ofstream ofs{l_file};
        fs::create_symlink(l_file, l_file_slink);
        display_recursive_dir(fs::current_path());

        fs::copy_file(l_file, l_dir/"testfile_copy");
        display_recursive_dir(fs::current_path());

        const fs::path l_new_dir   = l_work_dir/"testdir_copy";
        fs::copy(l_dir, l_new_dir);
        display_recursive_dir(fs::current_path());
        //fs::remove_all(l_new_dir);

        auto ftime = fs::last_write_time(l_file);
        auto ftime_diff = fs::file_time_type::clock::now() - ftime;
        auto ftime_duration = std::chrono::duration_cast<std::chrono::seconds>(ftime_diff).count();
        std::clog << "File " << l_file.string() << " is " << ftime_duration << " seconds old\n";

        std::clog << "File " << l_file.string() << " was last modified at " << filePathTimeAsString(l_file) << '\n';

        fs::remove_all(l_work_dir);
    }
    catch(const fs::filesystem_error & fexp) {
        std::clog << "File operation exception: \n" << fexp.what() << '\n';
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


