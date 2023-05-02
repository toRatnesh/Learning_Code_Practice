/******

References:
	C++17 - The Complete Guide | Nicolai M. Josuttis
    https://en.cppreference.com/w/cpp/filesystem
    https://en.cppreference.com/w/cpp/filesystem/path
    https://en.cppreference.com/w/cpp/filesystem/path/lexically_normal

20.2 Principles and Terminology

20.2.4 Normalization

	A path might be or can get normalized. In a normalized path:
	• Filenames are separated only by a single preferred directory separator.
	• The filename "." is not used unless the whole path is nothing but "."
	• The filename does not contain ".." filenames unless they are at the beginning of a relative path
	• The path only ends with a directory separator if the trailing filename is a directory with a name other than "." or "..".

	----------------------------------------------------------------------
	Path				POSIX normalized			Windows normalized
	----------------------------------------------------------------------
	foo/.///bar/../		foo/						foo\
	//host/../foo.txt	//host/foo.txt				\\host\foo.txt
	./f/../.f/ 			.f/							.f\
	C:bar/../			.							C:
	C:/bar/..			C:/							C:\
	C:\bar\.. 			C:\bar\.. 					C:\
	/./../data.txt 		/data.txt 					\data.txt
	././ 				. 							.
	----------------------------------------------------------------------

	The filesystem provides function for both lexical normalization (not taking the filesystem into account) and filesystem-dependent normalization.

****************/

#include <iostream>
#include <filesystem>

void display(std::filesystem::path fp_path) {
	std::clog << "File path		: " << fp_path.string() << '\n';
        std::clog << "Normalized file path	: " << fp_path.lexically_normal().string() << '\n';
	std::clog << '\n';
} 

int main() {

    
    try {
        std::filesystem::path l_path = "foo/.///bar/../"; 
	display(l_path);

        l_path = "//host/../foo.txt";
	display(l_path);

        l_path = "./f/../.f/";
	display(l_path);

        l_path = "C:bar/../";
	display(l_path);

        l_path = "C:/bar/..";
	display(l_path);

        l_path = "C:\bar\..";
	display(l_path);

        l_path = "/./../data.txt";
	display(l_path);

        l_path = "././";
	display(l_path);

    }
    catch(const std::filesystem::filesystem_error & fexp) {
        std::clog << "File operation exception " << fexp.what() << '\n';
        std::clog << "  path1 " << fexp.path1() << '\n';
        std::clog << "  path2 " << fexp.path2() << '\n';
        std::clog << "  Code value " << fexp.code().value() << '\n';
        std::clog << "  Code message " << fexp.code().message() << '\n';
        std::clog << "  Code category " << fexp.code().category().name() << '\n';
    }

    return 0;
}

/****
    END OF FILE
******/


