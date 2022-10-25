/***********
  This example demonstrates about decltype(auto) and how it differs from auto

  decltype(auto)
  Deduces exact type of an expression
  It is useful in generic code
  Useful for perfect return value

  For more info visit:
https://www.youtube.com/watch?v=E5L66fkNlpE

 *************/

#include <type_traits>

const int & get() {
	static int val = 5;
	return val;
}

auto get_retType_as_auto() { return get(); } // This will return int
decltype(auto) get_retType_as_decltype_auto() { return get(); }

decltype(auto) simple_return() { int i = 5; return i; }
decltype(auto) return_like_expression() { 
	int i = 5; 
	return (i); // NEVER TRAET RETURN AS A FUNCTION CALL, warning: reference to local variable 'i' returned
}  

int main() {
	{
		auto v1 = get();
		static_assert(std::is_same<decltype(v1), int>::value, "Deduced type is not int");
		auto v2 = get_retType_as_auto();
		static_assert(std::is_same<decltype(v2), int>::value, "Deduced type is not int");
		auto v3 = get_retType_as_decltype_auto();
		static_assert(std::is_same<decltype(v3), int>::value, "Deduced type is not int");
	}

	{
		const auto v1 = get();
		static_assert(std::is_same<decltype(v1), const int>::value, "Deduced type is not const int");
		const auto v2 = get_retType_as_auto();
		static_assert(std::is_same<decltype(v2), const int>::value, "Deduced type is not const int");
		const auto v3 = get_retType_as_decltype_auto();
		static_assert(std::is_same<decltype(v3), const int>::value, "Deduced type is not const int");
	}    

	{
		const auto & v1 = get();
		static_assert(std::is_same<decltype(v1), const int &>::value, "Deduced type is not const int &");
		const auto & v2 = get_retType_as_auto();
		static_assert(std::is_same<decltype(v2), const int &>::value, "Deduced type is not const int &");
		const auto & v3 = get_retType_as_decltype_auto();
		static_assert(std::is_same<decltype(v3), const int &>::value, "Deduced type is not const int &");
	}

	{
		decltype(auto) v1 = get();
		static_assert(std::is_same<decltype(v1), const int &>::value, "Deduced type is not const int &");
		decltype(auto) v2 = get_retType_as_auto();
		//static_assert(std::is_same<decltype(v4), const int &>::value, "Deduced type is not const int &");
		// Now return value is int instead of const int &
		static_assert(std::is_same<decltype(v2), int>::value, "Deduced type is not int");
		decltype(auto) v3 = get_retType_as_decltype_auto();
		static_assert(std::is_same<decltype(v3), const int &>::value, "Deduced type is not const int &");
	}

	{
		auto v1 = simple_return();
		static_assert(std::is_same<decltype(v1), int>::value, "Deduced type is not int");
		auto v2 = return_like_expression();
		static_assert(std::is_same<decltype(v2), int>::value, "Deduced type is not int");

		decltype(auto) v3 = simple_return();
		static_assert(std::is_same<decltype(v3), int>::value, "Deduced type is not int");
		decltype(auto) v4 = return_like_expression();
		static_assert(std::is_same<decltype(v4), int &>::value, "Deduced type is not int &");
	}

	return 0;
}

/********
  END OF FILE
 ********/


