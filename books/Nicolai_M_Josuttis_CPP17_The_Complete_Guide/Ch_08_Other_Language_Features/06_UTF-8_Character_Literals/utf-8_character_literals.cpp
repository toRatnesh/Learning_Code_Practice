/************
References:
	C++17 - The Complete Guide | Nicolai M. Josuttis

6.  UTF-8 Character Literals
    Since C++17, C++ supports the prefix u8 for UTF-8 character literals
    u8 can only be used for single characters and characters that have a single byte (code unit) in UTF-8.

    both character and string literals now accept the following prefixes:
        • u8 for single-byte US-ASCII and UTF-8 encoding.
        • u for two-byte UTF-16 encoding.
        • U for four-byte UTF-32 encoding.
        • l for wide characters without specific encoding, which might have two or four bytes.

*************/

#include <iostream>
#include <iomanip>
#include <vector>

int main() {
    {
        char u8c = u8'A';
        std::clog << R"(u8'A' - )" << u8c << '\n';
    }
    
    {
        //char smiley = u8'😀';     // error: character constant too long for its type
        //char smiley = u'😀';      // error: character constant too long for its type
        //char smiley = U'😀';      // warning: overflow in conversion from 'char32_t' to 'char' changes value from '128512' to ''\000''
        char32_t smiley = U'😀';
        std::clog << R"(U'😀' - )" << static_cast<wchar_t>(smiley) << '\n';
    }

    return 0;
}

/***************
    END OF FILE
*****************/
