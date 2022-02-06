/**************
 *
 * 	This example demonstrates the use of C++ sanitizers.
 * 	The C/C++ compilers Clang/LLVM and GCC support so-called sanitizers. 
 * 	These sanitizers are built into the application code and track the execution at runtime to report execution errors. 
 * 	There are currently four interesting sanitizers:
 *
 * 	AddressSanitizer and LeakSanitizer
 * 	ThreadSanitizer
 * 	MemorySanitizer
 *
 * 	For more details check respective GCC/Clang documentation.
 * 	https://clang.llvm.org/docs/index.html
 * 	https://gcc.gnu.org/onlinedocs/gcc/Instrumentation-Options.html
 *
 * ****************/

#include <iostream>
#include <string>

int main() {

	const char * lsa[] = {"Sample1", "Sample2", "Sample3"};
	const std::string lstr = lsa[3];

	int *pli = new int(2);
	std::cout << *pli << '\n';


	return 0;
}

/**********
 *	END OF FILE
 * **********/
