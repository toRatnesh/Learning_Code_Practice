/*************
 *	std::puts
 *	int puts( const char *str );
 *	Writes every character from the null-terminated string str and 
 *	one additional newline character '\n' to the output stream stdout, as if by repeatedly executing std::fputc.
 *
 *	The terminating null character from str is not written.
 *
 *	For more detail check:
 *	https://en.cppreference.com/w/cpp/io/c/puts
 *
 * *************/

#include <cstdio>

int main() {
	constexpr char lac[] = "This is a char array.";
	std::puts(lac);

	const char * lpc = "This is another char array using pointer notation.";
	std::puts(lpc);


	return 0;
}


/*********
 *	END OF FILE
 * *********/
