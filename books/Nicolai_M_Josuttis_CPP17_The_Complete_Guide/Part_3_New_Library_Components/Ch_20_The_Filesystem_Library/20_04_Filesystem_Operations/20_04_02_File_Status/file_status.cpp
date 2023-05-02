/*******

References
    C++17 - The Complete Guide | Nicolai M. Josuttis
    https://en.cppreference.com/w/cpp/filesystem
    https://en.cppreference.com/w/cpp/filesystem/file_status

20.4 Filesystem Operations
	Expensive filesystem operations that take the current filesystem into account

20.4.2 File Status
	To avoid filesystem access, there is a special type file_status that can be used to hold and modify file type and permissions that are cached.

	============================================================
	Call 				Effect
	============================================================
	status(p)			yields the file_status of the file p (following symbolic links)
	symlink_status(p)	yields the file_status of p (not following symbolic links) p
	============================================================

	One benefit of the status operations is that you can save multiple operating system calls for the same file.

	The exists() and is_...() functions for path arguments are shortcuts for calling and checking the type() for a file status. For example,
		is_regular_file(mypath)
	is a shortcut for
		is_regular_file(status(mypath))
	which is a shortcut for
		status(mypath).type() == file_type::regular

******************/

#include <iostream>
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

int main() {

    const fs::path l_dir   = "tmp/testdir";
    const fs::path l_file  =  l_dir/"testfile";
    
    const fs::path l_dir_slink     = "tmp/testdir_slink";
    const fs::path l_file_slink    = "tmp/testfile_slink";

    try {

        fs::create_directories(l_dir);
        fs::create_directory_symlink(l_dir, l_dir_slink);

        std::ofstream ofs{l_file};
        fs::create_symlink(l_file, l_file_slink);
        
        const fs::file_status l_file_status     = fs::status(l_file);
        if(! fs::exists(l_file_status)) {
            std::clog << "File " << l_file.string() << " does not exist\n";
        }

        const fs::file_status l_dir_status      = fs::status(l_dir);
        if(! fs::exists(l_dir_status)) {
            std::clog << "Directory " << l_dir.string() << " does not exist\n";
        }

        {
            const fs::file_status l_fslink_status   = fs::status(l_file_slink); // 
            if(! fs::exists(l_fslink_status)) {
                // this is not correct way to check for symbolic link
                //fs::create_symlink(l_file, l_file_slink);   // exception: File exists
            }
        }

        const fs::file_status l_fslink_status   = fs::symlink_status(l_file_slink);
        if(! fs::exists(l_fslink_status)) {
            // this is correct way to check for symbolic link using symlink_status
            fs::create_symlink(l_file, l_file_slink);
        }

        if(is_regular_file(l_file)) {
            std::clog << "Using path: File " << l_file.string() << " is regular file\n";
        }

        if(is_regular_file(l_file_status)) {
            std::clog << "Using status: File " << l_file.string() << " is regular file\n";
        }

        if(fs::file_type::regular == l_file_status.type()) {
            std::clog << "Using file_type: File " << l_file.string() << " is regular file\n";
        }

        if(is_regular_file(l_fslink_status)) {  // this will not match
            std::clog << "Using status: File " << l_file.string() << " is regular file\n";
        }

        if(is_symlink(l_fslink_status)) {
            std::clog << "Using status: File " << l_file_slink.string() << " is symbolic link\n";
        }

        for(const auto & elem : fs::recursive_directory_iterator(fs::current_path())) {
            std::clog << elem.path().string() << '\n';
        }

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


