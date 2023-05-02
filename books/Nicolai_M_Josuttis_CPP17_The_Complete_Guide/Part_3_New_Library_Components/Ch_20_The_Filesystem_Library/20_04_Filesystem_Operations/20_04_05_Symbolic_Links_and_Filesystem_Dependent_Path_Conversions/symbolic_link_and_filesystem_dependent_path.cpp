/*******

References
    C++17 - The Complete Guide | Nicolai M. Josuttis
    https://en.cppreference.com/w/cpp/filesystem

20.4 Filesystem Operations
	Expensive filesystem operations that take the current filesystem into account

20.4.5 Symbolic Links and Filesystem-Dependent Path Conversions

	Filesystem Path Conversions lists the operations to deal with the path of files taking the filesystem into account.
	These calls handle it differently whether the file(s) must exists, whether they normalize, and whether they follow symbolic links.
	============================================================
	Call					Effect
	============================================================
	read_symlink(symlink)	yields the file an existing symbolic link refers to
	absolute(p)				yields existing p as absolute path (not following symbolic links)
	canonical(p)			yields existing p as absolute path (following symbolic links)
	weakly_canonical(p)		yields p as absolute path (following symbolic links)
	relative(p)				yields relative (or empty) path from current directory to p
	relative(p, base)		yields relative (or empty) path from base to p
	proximate(p)			yields relative (or absolute) path from current directory to p
	proximate(p, base)		yields relative (or absolute) path from base to p
	============================================================

	Filesystem Path Conversion Attributes gives an overview of what the functions require and perform.
	============================================================
	Call				Must Exist		Normalizes		Follows Symbolic Links
	============================================================
	read_symlink()		yes				yes				once
	absolute()			no				yes				no
	canonical()			yes				yes				all
	weakly_canonical()	no				yes				all
	relative()			no				yes				all
	proximate()			no				yes				all
	============================================================

	relative_path() and lexically_relative()
	are cheap path member functions not taking the actual filesystem into account. 
	Thus, they ignore symbolic links. 

	relative() 
	takes the filesystem into account
	As long as we don’t have files yet, it acts like lexically_relative()
	But after creating the symbolic link ps (top/a/s), it follows the symbolic links and gives a different result

******************/

#include <iostream>
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

void display_recursive_dir(const fs::path fp_dir) {
    std::clog << "Directory " << fp_dir.string() << " contains: \n";
    for(const auto & elem : fs::recursive_directory_iterator(fp_dir)) {
        std::clog << elem.path().string() << '\n';
    }
    std::clog << '\n';
}

int main() {

    fs::path l_work_dir   = "tmp";
    fs::path l_dir        = l_work_dir/"testdir";

    fs::path l_file       = l_dir/"testfile";
    fs::path l_file_slink = l_work_dir/"testfile_slink";

    try {
        std::clog << "=== absolute ===\n";
        std::clog << fs::absolute(l_work_dir) << '\n';
        std::clog << fs::absolute(l_work_dir).string() << '\n';
        std::clog << fs::absolute(l_file) << '\n';
        std::clog << fs::absolute(l_file).string() << '\n';
        std::clog << fs::absolute(l_file_slink) << '\n';
        std::clog << fs::absolute(l_file_slink).string() << '\n';

        std::clog << "=== relative ===\n";
        std::clog << fs::relative(l_work_dir) << '\n';
        std::clog << fs::relative(l_work_dir).string() << '\n';
        std::clog << fs::relative(l_file) << '\n';
        std::clog << fs::relative(l_file).string() << '\n';
        std::clog << fs::relative(l_file_slink) << '\n';
        std::clog << fs::relative(l_file_slink).string() << '\n';

        std::clog << "=== proximate ===\n";
        std::clog << fs::proximate(l_work_dir) << '\n';
        std::clog << fs::proximate(l_work_dir).string() << '\n';
        std::clog << fs::proximate(l_file) << '\n';
        std::clog << fs::proximate(l_file).string() << '\n';
        std::clog << fs::proximate(l_file_slink) << '\n';
        std::clog << fs::proximate(l_file_slink).string() << '\n';

        std::clog << "=== creating directories and files ===\n";
        fs::create_directories(l_dir);
        std::ofstream ofs{l_file};
        fs::create_symlink(l_file, l_file_slink);
        display_recursive_dir(fs::current_path());

        std::clog << "=== absolute ===\n";
        std::clog << fs::absolute(l_work_dir) << '\n';
        std::clog << fs::absolute(l_work_dir).string() << '\n';
        std::clog << fs::absolute(l_file) << '\n';
        std::clog << fs::absolute(l_file).string() << '\n';
        std::clog << fs::absolute(l_file_slink) << '\n';
        std::clog << fs::absolute(l_file_slink).string() << '\n';

        std::clog << "=== relative ===\n";
        std::clog << fs::relative(l_work_dir) << '\n';
        std::clog << fs::relative(l_work_dir).string() << '\n';
        std::clog << fs::relative(l_file) << '\n';
        std::clog << fs::relative(l_file).string() << '\n';
        std::clog << fs::relative(l_file_slink) << '\n';
        std::clog << fs::relative(l_file_slink).string() << '\n';

        std::clog << "=== proximate ===\n";
        std::clog << fs::proximate(l_work_dir) << '\n';
        std::clog << fs::proximate(l_work_dir).string() << '\n';
        std::clog << fs::proximate(l_file) << '\n';
        std::clog << fs::proximate(l_file).string() << '\n';
        std::clog << fs::proximate(l_file_slink) << '\n';
        std::clog << fs::proximate(l_file_slink).string() << '\n';

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


