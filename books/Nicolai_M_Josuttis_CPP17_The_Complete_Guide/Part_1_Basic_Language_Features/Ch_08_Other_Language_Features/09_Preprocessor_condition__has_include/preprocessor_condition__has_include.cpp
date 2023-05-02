/************
References:
	C++17 - The Complete Guide | Nicolai M. Josuttis
    https://en.cppreference.com/w/cpp/preprocessor/include
    https://gcc.gnu.org/onlinedocs/cpp/_005f_005fhas_005finclude.html

9. Preprocessor condition __has_include
    It checks whether a header or source file is available for inclusion
    evaluates to a nonzero(true) value if the header/source file can be included and to zero(false) otherwise

*************/

#if __has_include(<iostream>)
#include <iostream>
#endif

#if __has_include(<does_not_exist.h>)
    #include <does_not_exist.h>
#elif __has_include(<sys/utsname.h>)
    #include <sys/utsname.h>
#else
#endif

int main() {

	std::clog << "Learning __has_include()\n";

	struct utsname l_utsname;
	uname(&l_utsname);
	std::clog << "OS: " << l_utsname.sysname << ", release: " << l_utsname.release << ", version: " << l_utsname.version << '\n';


	return 0;
}

/***************
  END OF FILE
 *****************/
