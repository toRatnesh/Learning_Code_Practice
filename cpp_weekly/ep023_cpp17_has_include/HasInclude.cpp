/***
 *	This exmaple demonstrates the use of cpp17's __has_include
 *	__has_include ( " filename " )
 *	__has_include ( < filename > )
 *	Preprocessor constant expression that evaluates to 1 if the file name is found and 0 if not. The program is ill-formed if the argument would not be a valid argument to the #include directive.
 * ***/

#if __has_include(<iostream>)
#include <iostream>
#pragma message "Included iostream"
#endif

#if __has_include(<unistd.h>)
#include <unistd.h>
#pragma message "Included unistd"
#endif

#if __has_include(<windows.h>)
#include <windows.h>
#pragma message "Included windows"
#endif

int main() {
	return 0;
}

/***
 *	END OF FILE
 * ***/
