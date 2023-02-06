/*******

References
    C++17 - The Complete Guide | Nicolai M. Josuttis
	https://en.cppreference.com/w/cpp/string/basic_string_view

19 String Views

std::string_view objects refer to external character sequences without owning them.
The object can be considered as a reference to a character sequence.
It is also potentially dangerous, because similar to raw pointers it is up to the programmer to ensure that the referred character sequences is still valid

19.4 String View Types and Operations
the types and operations of string views

19.4.1 Concrete String View Types
	specializations of class basic_string_view<>
	namespace std {
		using string_view		= basic_string_view<char>;
		using u16string_view	= basic_string_view<char16_t>;
		using u32string_view	= basic_string_view<char32_t>;
		using wstring_view		= basic_string_view<wchar_t>;
	}

	usage and the problems are the same because all string view classes have the same interface.

19.4.2 String View Operations
	Except for remove_prefix() and remove_suffix(), all operations of string views are also provided for std::strings.
	For operations visit https://en.cppreference.com/w/cpp/string/basic_string_view
	
	Construction
		String views created with the default constructor have nullptr as data()
		When initializing a string view by a null terminated byte stream, the resulting size is the number of characters without '\0' and using the index of the terminating null character is not valid
			std::string_view sv{"hello"};
			std::string_view sv{"hello", 6}; // NOTE: 6 to include '\0'
		To create a string view from a std::string an implicit conversion operator is provided in class std::string. Also having the null terminator right after the last character, which is usually guaranteed for a string, is not guaranteed to exist for the string view
		The literal operator is defined for the suffix sv
			using namespace std::literals;
			auto s = "hello"sv;
			
	Hashing
		The C++ standard library guarantees that hash values for strings and strings views are equal.
		
	Modifying a String View
		can assign a new value or swap the values of two string views
		can skip leading or trailing character
		no support for operator+
		there is no implicit conversion to a string, because this is an expensive operation because it might allocate memory

19.4.3 String View Support by Other Types
	Strings can use or be combined with string views wherever useful
	There is also in implicit conversion from a string to a string view
	You can initialize, extend or compare filesystem paths with string views.
	There is no support for string views in the regex component of the C++ standard library

******************/

#include <iostream>
#include <string>
#include <string_view>
#include <iomanip>
#include <filesystem>

std::string_view get_sview() {
    std::string str = "implicit conversio from string to string_view allowed";
    return str;
}

std::string get_str() {
    [[maybe_unused]] std::string_view sview = "implicit conversion from string_view to string not allowed because its a expensive operation";
    //return sview;   // error: could not convert 'sview' from 'std::string_view' to 'std::string' 
    return static_cast<std::string>(sview);
}


int main() {

    // 19.4.1 Concrete String View Types
    std::clog << "=== 19.4.1 Concrete String View Types ===\n";
    {
        std::string_view sview{"😊"};
        std::clog << sview << '\n';
        std::clog << "sview.size()  " << sview.size() << '\n';
    }
    {
        std::u16string_view u16sview{u"😊"};
        //std::clog << u16sview << '\n';          // CE no match for operator << ...
        std::clog << "u16sview.size()   " << u16sview.size() << '\n';
    }
    {
        std::u32string_view u32sview{U"😊"};
        //std::clog << u32sview << '\n';            // CE no match for operator << ...
        std::clog << "u32sview.size() " << u32sview.size() << '\n';
    }
    {
        std::wstring_view wsview(L"😊");
        //std::clog << wsview << '\n';            // CE no match for operator << ...
        std::clog << "wsview.size()   " << wsview.size() << '\n';
    }
    

    // 19.4.2 String View Operations
    std::clog << "\n=== 19.4.2 String View Operations ===\n";
    {
        // Construction
        std::string default_sview;
        auto p = default_sview.data();
        if(nullptr == p) {
            std::clog << "default_sview.data() is nullptr\n"; 
        }

        std::string_view asview{"string view using byte stream"}; // does not include '\0'
        std::clog << "asview: " << asview << ", asview.size() " << asview.size() << '\n';
        try {
            std::clog << "asview.data() " << asview.data() << " (theoratically this is undefined behavior)" << '\n'; // undefined behavior
            std::clog << "asview[asview.size()] " << asview[asview.size()] << " (theoratically this is undefined behavior)" << '\n'; // undefined behavior
            std::clog << "asview.at(asview.size()) " << asview.at(asview.size()) << '\n'; // raises exception
        }
        catch(const std::out_of_range & range_exp) {
            std::clog << "EXCEPTION - Range exception for string_view: " << range_exp.what() << '\n';

        }
        std::clog << '\n';

        std::string_view asview_with_null{"string view with null byte", 27}; // does not include '\0'
        std::clog << "asview_with_null: " << asview_with_null << ", asview.size() " << asview_with_null.size() << '\n';
        try {
            std::clog << "asview_with_null.data() " << asview_with_null.data() << '\n'; 
            std::clog << "asview_with_null[asview_with_null.size()] " << asview_with_null[asview_with_null.size() - 1] << '\n'; // OK prints '\0'
            std::clog << "asview_with_null.at(asview_with_null.size()) " << asview_with_null.at(asview_with_null.size() - 1) << '\n';  // OK prints '\0'
        }
        catch(const std::out_of_range & range_exp) {
            std::clog << "EXCEPTION - Range exception for string_view: " << range_exp.what() << '\n';

        }
        std::clog << '\n';

        std::string astr{"C++"};
        std::string_view str_to_sview{astr};
        std::clog << "astr: " << astr << ", astr.size() " << astr.size() << '\n';
        std::clog << "str_to_sview: " << str_to_sview << ", str_to_sview.size() " << str_to_sview.size() << '\n'; 
        try {
            std::clog << "astr.at(astr.size()) " << astr.at(astr.size()) << '\n';
        }
        catch(const std::out_of_range & range_exp) {
            std::clog << "EXCEPTION - Range exception for string_view: " << range_exp.what() << '\n';

        }
        std::clog << '\n';

        // hashing
        auto hash_str = std::hash<std::string>{}(astr);
        auto hash_str_view = std::hash<std::string_view>{}(str_to_sview);
        std::clog << "Hash value of str " << hash_str << '\n';
        std::clog << "Hash value of str view " << hash_str_view << '\n';
        if(hash_str == hash_str_view) {
            std::clog << "hash value of string and its corresponding view is same\n";
        }
        std::clog << '\n';

        // Modifying a String View
        std::string_view mod_sview{"this string view will be modified"};
        std::string_view another_sview{"this is a different string view"};
        std::clog << "mod_sview: " << mod_sview << '\n';
        mod_sview.remove_prefix(5);
        mod_sview.remove_suffix(17);
        std::clog << "mod_sview after remove_prefix and remove_suffix: " << mod_sview << '\n';
        mod_sview.swap(another_sview);
        std::clog << "mod_sview after swap with another string_view: " << mod_sview << '\n';

        //auto res_view = mod_sview + another_sview; // CE error: no match for 'operator+' (operand types are 'std::string_view' and 'std::string_view')
    }

    std::clog << "\n=== 19.4.3 String View Support by Other Types ===\n";
    {
        using namespace std::literals;
        auto sview = R"(this is a string view literal)"sv; // raw string view
        std::clog << "std::quoted(sview): " << std::quoted(sview) << '\n';

        std::string_view sv_path1{"tmp/file1"};
        std::string_view sv_path2{"tmp/file1"};

        std::filesystem::path path1{sv_path1};
        if(path1.empty()) {
            std::clog << "Path " << sv_path1 << " is empty\n";
        }

        if(path1.compare(sv_path2)) {
            std::clog << "path1 and path2 are same\n";
        }
        else {
            std::clog << "path1 and path2 are different\n";
        }

    }

    return 0;
}

/*****
    END OF FILE
********/


