/*******

References
    C++17 - The Complete Guide | Nicolai M. Josuttis
    https://en.cppreference.com/w/cpp/filesystem
    https://en.cppreference.com/w/cpp/filesystem/perms
    https://en.cppreference.com/w/cpp/filesystem/perm_options

20.4 Filesystem Operations
	Expensive filesystem operations that take the current filesystem into account

20.4.3 Permissions
	The model to deal with file permissions is adopted from the UNIX/POSIX world.
	There are bits to signal read, write, and/or execute/search access for owners of the file.
	Permission Bits lists the values of the bitmask scoped enumeration type perms

	============================================================
	Enum			Octal		POSIX Meaning
	============================================================
	none			0			No permissions set
	owner_read		0400		S_IRUSR Read permission for the owner
	owner_write 	0200		S_IWUSR Write permission for the owner
	owner_exec 		0100		S_IXUSR Execute/search permission for the owner
	owner_all 		0700		S_IRWXU All permissions for the owner
	group_read 		040			S_IRGRP Read permission for the group
	group_write 	020			S_IWGRP Write permission for the group
	group_exec 		010			S_IXGRP Execute/search permission for the group
	group_all 		070			S_IRWXG All permission for the group
	others_read 	04			S_IROTH Read permission for all others
	others_write 	02			S_IWOTH Write permission for all others
	others_exec 	01			S_IXOTH Execute/search permission for all others
	others_all 		07			S_IRWXO All permissions for all others
	all 			0777		All permissions for all
	set_uid 		04000		S_ISUID Set user-ID on execution
	set_gid 		02000		S_ISGID Set group-ID on execution
	sticky_bit 		01000		S_ISVTX Operating system dependent
	mask 			07777		Mask for all possible bits
	unknown 		0xFFFF		Permissions not known
	============================================================

    Permission options
    enum class perm_options {
        replace     = // unspecified,
        add         = // unspecified,
        remove      = // unspecified,
        nofollow    = // unspecified,
    };

	You can ask for the current permissions and as a result check the bits of the returned perms object.
	To combine flags, you have to use the bit operators. 
	you have to put the & expressions in parentheses before comparing the outcome with a specific value.
	For example:
	// if writable:
	if ((fileStatus.permissions() & (fs::perms::owner_write | fs::perms::group_write | fs::perms::others_write)) != fs::perms::none) {
		...
	}

	shorter (but maybe less readable) way to initialize a bitmask would be to directly use the corresponding octal value and relaxed enum initialization:
	// if writable:
	if ((fileStatus.permissions() & fs::perms{0222}) != fs::perms::none) {
		...
	}

******************/

#include <iostream>
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

std::string filePermissionAsString(const fs::path fp_path) {
    using perms = std::filesystem::perms;
    auto pm = fs::status(fp_path).permissions();
    std::string perms_str;
    perms_str.resize(9);
    perms_str[0] = (pm & perms::owner_read)     != perms::none ? 'r' : '-';
    perms_str[1] = (pm & perms::owner_write)    != perms::none ? 'w' : '-';
    perms_str[2] = (pm & perms::owner_exec)     != perms::none ? 'x' : '-';
    perms_str[3] = (pm & perms::group_read)     != perms::none ? 'r' : '-';
    perms_str[4] = (pm & perms::group_write)    != perms::none ? 'w' : '-';
    perms_str[5] = (pm & perms::group_exec)     != perms::none ? 'x' : '-';
    perms_str[6] = (pm & perms::others_read)    != perms::none ? 'r' : '-';
    perms_str[7] = (pm & perms::others_write)   != perms::none ? 'w' : '-';
    perms_str[8] = (pm & perms::others_exec)    != perms::none ? 'x' : '-';
    return perms_str;
}

int main() {

    const fs::path l_work_dir   = "tmp";
    const fs::path l_file       =  l_work_dir/"testfile";
    const fs::path l_file_slink         = l_work_dir/"testfile_slink";

    try {

        fs::create_directories(l_work_dir);
        std::ofstream ofs{l_file};
        fs::create_symlink(l_file, l_file_slink);

        for(const auto & elem : fs::recursive_directory_iterator(fs::current_path())) {
            std::clog << elem.path().string() << '\n';
        }
        std::clog << "File " << l_file.string() << " permission is " << filePermissionAsString(l_file) << '\n';

        auto l_file_status = fs::status(l_file);
        if((l_file_status.permissions() & (fs::perms::owner_write | fs::perms::group_write | fs::perms::others_write) ) != fs::perms::none) {
            std::clog << "File " << l_file.string() << " has write permission\n";
        }
        if((l_file_status.permissions() & (fs::perms{0222})) != fs::perms::none) {
            std::clog << "File " << l_file.string() << " has write permission\n";
        }

        if((l_file_status.permissions() & (fs::perms::owner_all | fs::perms::group_all | fs::perms::others_all) ) != fs::perms::none) {
            std::clog << "File " << l_file.string() << " has all permission\n";
        }
        if((l_file_status.permissions() & fs::perms{0777}) != fs::perms::none) {
            std::clog << "File " << l_file.string() << " has all permission\n";
        }

        fs::remove_all(l_work_dir);
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


