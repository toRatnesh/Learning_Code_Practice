/*******

References
    C++17 - The Complete Guide | Nicolai M. Josuttis
    https://en.cppreference.com/w/cpp/filesystem
    https://en.cppreference.com/w/cpp/filesystem/directory_entry

20.5 Iterating Over Directories

    Most convenient way to do it is to use a range-based for loop

    for (const auto& e : std::filesystem::directory_iterator(dir)) {
        std::cout << e.path() << '\n';
    }

    or iterate recursively over all files in a filesystem (sub)tree:

    for (const auto& e : std::filesystem::recursive_directory_iterator(dir)) {
        std::cout << e.path() << '\n';
        std::cout << e.path().lexically_normal().string() << '\n';	// portable
    }

Directory Iterators are Ranges
	both directory_iterator and recursive_directory_iterator are classes for which global overloads of begin() and end() are provided
	std::filesystem::directory_iterator di{p};
	for (auto pos = begin(di); pos != end(di); ++pos) {
		std::cout << pos->path() << '\n';
	}

Directory Iterator Options
	When iterating over directories you can pass values of type directory_options

	===========================================================
	directory_options			Effect
	===========================================================
	none						Default (value 0)
	follow_directory_symlink	Follow symbolic links (rather than skipping them)
	skip_permission_denied		Skip directories where permission is denied
	===========================================================


20.5.1 Directory Entries
    The elements directory iterators iterate over are of type std::filesystem::directory_entry.

    for (const std::filesystem::directory_entry& e : std::filesystem::directory_iterator(p)) {
        std::cout << e.path() << '\n';
    }

    The iterators are input iterators. The reason is that iterating over a directory might result into different results as at any time directory entries might change. This has to be taken into account when using directory iterators in parallel algorithms.

    For member functions of directory_entry visit
    https://en.cppreference.com/w/cpp/filesystem/directory_entry

    assign() and replace_filename() call the corresponding modifying path operations but do not modify the files in the underlying filesystem.

Directory Entry Caching

	Implementations are encouraged to cache such additional file attributes to avoid additional filesystem access when using the entries. However, implementations are not required to cache the data.

	Whether cached or not, in a mult-user or multi-process operating system all these iterations might yield data about files that is no longer valid.

	you can request to refresh the data a directory entry holds:
	for (const auto& e : std::filesystem::directory_iterator{"."}) {
		... // data data becomes old
		e.refresh(); // refresh cache data for the file
		if (e.exists()) {
			auto t = e.last_write_time();
			...
		}
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

void display_dir(const fs::path fp_dir) {
    std::clog << "Directory " << fp_dir.string() << " contains: \n";
    for(const auto & elem : fs::directory_iterator(fp_dir)) {
        std::clog << elem.path().string() << '\n';
    }
    std::clog << "--- Lexically Normal Path ---\n";
    for(const auto & elem : fs::directory_iterator(fp_dir)) {
        std::clog << elem.path().lexically_normal().string() << '\n';
    }
    std::clog << '\n';
}

void display_recursive_dir(const fs::path fp_dir) {
    std::clog << "Directory " << fp_dir.string() << " recursively contains: \n";
    for(const auto & elem : fs::recursive_directory_iterator(fp_dir)) {
        std::clog << elem.path().string() << '\n';
    }
    std::clog << "--- Lexically Normal Path ---\n";
    for(const auto & elem : fs::recursive_directory_iterator(fp_dir)) {
        std::clog << elem.path().lexically_normal().string() << '\n';
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
        display_dir(fs::current_path());

        // Directory Iterators are Ranges
        std::filesystem::directory_iterator di{fs::current_path()};
        for (auto pos = begin(di); pos != end(di); ++pos) {
            std::clog << pos->path() << '\n';
        }
        std::clog << '\n';

        //Directory Iterator Options
        for (fs::directory_iterator pos{fs::current_path(), fs::directory_options::skip_permission_denied};
                pos != fs::directory_iterator{}; ++pos) {
            std::clog << pos->path() << '\n';
        }
        std::clog << '\n';

        // 20.5.1 Directory Entries
            // Directory Entry Caching
        for(auto elem : fs::recursive_directory_iterator(fs::current_path())) {
            elem.refresh();     // refresh cache data for the file
            if(elem.exists()) {
                
                auto ftime_diff = fs::file_time_type::clock::now() - elem.last_write_time();
                auto ftime_duration = std::chrono::duration_cast<std::chrono::seconds>(ftime_diff).count();
                std::clog << "File " << elem.path().string() << " is " << ftime_duration << " seconds old\n";

                if(elem.is_regular_file()) {
                    elem.replace_filename("new_file_name");
                }
                else {
                    elem.assign("new_name");
                }
            }
        }
        std::clog << '\n';        
        display_recursive_dir(fs::current_path());

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


