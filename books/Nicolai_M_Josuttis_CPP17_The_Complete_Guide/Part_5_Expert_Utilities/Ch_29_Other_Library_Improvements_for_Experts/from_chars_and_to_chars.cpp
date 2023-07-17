/**********

References

    C++17 - The Complete Guide | Nicolai M. Josuttis
    https://en.cppreference.com/w/cpp/utility/from_chars
    https://en.cppreference.com/w/cpp/utility/to_chars

29 Other Library Improvements for Experts

29.1 Low-Level Conversions between Character Sequences and Numeric Values

	C++17 introduced new elementary string conversion functions with the following abilities:
	• No runtime parsing of format strings
	• No dynamic memory allocation inherently required by the interface
	• No consideration of locales
	• No indirection through function pointers required
	• Prevention of buffer overruns
	• When parsing a string, errors are distinguishable from valid numbers
	• When parsing a string, whitespace or decorations are not silently ignored

	In addition for floating-point numbers, this feature will provide a round-trip guarantee that values converted to a character sequence and converted back result in the original value.

	29.1.1 Example Usage
	
		Two overloaded functions are provided:
		• std::from_chars() converts a given character sequence to a numeric value.
		• std::to_chars() converts numeric values to a given character sequence.
		
	from_chars()
		std::from_chars() converts a given character sequence to a numeric value
		The result value is the following structure:
		
		struct from_chars_result {
			const char*		ptr;
			std::errc		ec;
		};
		
		There is no implicit conversion to bool for std::errc
		
		Return value
		On success, ptr points at the first character not matching the pattern, or has the value equal to last if all characters match and ec is value-initialized.

		If there is no pattern match, ptr equals first and ec equals std::errc::invalid_argument. value is unmodified.

		If the pattern was matched, but the parsed value is not in the range representable by the type of value, ec equals std::errc::result_out_of_range and ptr points at the first character not matching the pattern. value is unmodified.
		
		
	to_chars()
		std::to_chars() converts numeric values to a given character sequence
		The result value is the following structure:
		struct to_chars_result {
			char* ptr;
			std::errc ec;
		};
	
		There is no implicit conversion to bool for std::errc
		
		Return value
		On success, ec equals value-initialized std::errc and ptr is the one-past-the-end pointer of the characters written. Note that the string is not NUL-terminated.

		On error, std::errc::value_too_large in ec, a copy of the value last in ptr, and leaves the contents of the range [first, last) in unspecified state.

		Add a trailing null character
		*res.ptr = '\0';
		
	29.1.2 Floating-Point Round-Trip Support
	
		If no precision is given, to_chars() and from_chars() guarantee round-trip support for floatingpoint values.
		This means that a value converted to a character sequence and read back has exactly its original value.
		
		As a consequence, floating-point value have to be written as a sequence of characters with the finest granularity with the highest precision.
		
		Again note that the granularity (and therefore the necessary size of the character sequence) depends on the platform. 
		The round-trip support shall work for all floating-point numbers including NAN and INFINITY.
		However, note that the assertion in d2str2d() will fail for NAN because it never compares to anything, including itself.

*************/

#include <iostream>
#include <string>
#include <iomanip>
#include <charconv>
#include <array>
#include <vector>
#include <cassert>


// to check round trip

void d2str2d(double value) {
	std::cout << "in: " << value << '\n';
	
	std::array<char, 128> str;
	// convert to character sequence:
	{
		auto [ptr, ec] = std::to_chars(str.data(), str.data() + str.size(), value);
		*ptr = '\0'; // add trailing null character
		std::cout << "str: " << std::quoted(str.data()) << '\n';
		assert(ec == std::errc{});
	}
	
	// read back from character sequence:
	double value2;
	{
		auto [ptr, ec] = std::from_chars(str.data(), str.data() + str.size(), value2);
		std::cout << "out: " << value2 << '\n';
		assert(ec == std::errc{});	
	}
	assert(value == value2); // should never fail
	
	return ;
}

auto show_to_chars = [](auto ... format_args) {
    std::array<char, 10> str;
 
    if (auto [ptr, ec] = std::to_chars(str.data(), str.data() + str.size(), format_args...);
        ec == std::errc{})
        std::cout << std::string_view(str.data(), ptr - str.data()) << '\n';
    else
        std::cout << std::make_error_code(ec).message() << '\n';
};

int main() {

    std::cout << "=== conversion to int ===\n";
    std::vector nvec{'1', '2', '3'};
    for(std::string_view str : {"123", "123sample", "sample123", "sample123string", " 123", "123 ", "sample"}) {
        std::cout << "String: " << std::quoted(str) << ",   ";
        int result{};
        auto [ptr, ec] = std::from_chars(str.data(), str.data() + str.size(), result);
        //auto [ptr, ec] = std::from_chars(nvec.data(), nvec.data() + nvec.size(), result);
 
        if (ec == std::errc{})
            std::cout << "Result: " << result << ", ptr -> " << std::quoted(ptr) << '\n';
        else if (ec == std::errc::invalid_argument)
            std::cout << "That isn't a number.\n";
        else if (ec == std::errc::result_out_of_range)
            std::cout << "This number is larger than an int.\n";
    }

    std::cout << "=== conversion to double ===\n";
    for(std::string_view str : {"12.34", "12.34sample", "sample12.34", "sample12.34string", " 12.34", "12.3 ", "sample"}) {
        std::cout << "String: " << std::quoted(str) << ",   ";
        double result{};
        auto [ptr, ec] = std::from_chars(str.data(), str.data() + str.size(), result);
 
        if (ec == std::errc{})
            std::cout << "Result: " << result << ", ptr -> " << std::quoted(ptr) << '\n';
        else if (ec == std::errc::invalid_argument)
            std::cout << "That isn't a number.\n";
        else if (ec == std::errc::result_out_of_range)
            std::cout << "This number is larger than an int.\n";
    }

    {
        std::cout << "=== conversion from number to char sequence ===\n";
        show_to_chars(42);
        show_to_chars(+3.14159F);
        show_to_chars(-3.14159, std::chars_format::fixed);
        show_to_chars(-3.14159, std::chars_format::scientific, 3);
        show_to_chars(3.1415926535, std::chars_format::fixed, 10);
    }


    {
        std::cout << "=== Round-Trip check ===\n";
        d2str2d(2.3567);
        d2str2d(2.35674732974);
    }

    return 0;
}

/**********
    END OF FILE
*************/


