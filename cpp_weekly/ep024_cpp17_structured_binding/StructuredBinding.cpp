/******
 *
 * 	This example demonstrates the use of structured binding.
 * 	
 * 	Structured binding declaration (since C++17)
 * 	Binds the specified names to subobjects or elements of the initializer.
 * 	Like a reference, a structured binding is an alias to an existing object. 
 * 	Unlike a reference, the type of a structured binding does not have to be a reference type.
 *
 * *****/


#include <iostream>
#include <string>
#include <map>

struct S {
	uint32_t i = 4;
	uint32_t j = 9;
};

int main() {
	std::cout << '\n' << "=== STRUCTURE BINDING IN MAP ===" << '\n';
	std::map<std::string, std::string> l_mapValue;
	l_mapValue["name"] = "Learning Structred Binding";
	l_mapValue["addr"] = "CPP 17";

	auto res1 = l_mapValue.find("name");
	if(l_mapValue.end() != res1) {
		std::cout << res1->first << " : " << res1->second << '\n';
	}

	auto res2 = l_mapValue.find("addr");
	if(l_mapValue.end() != res2) {
		auto [key, value] = *res2;
		std::cout << key << " : " << value << '\n';
	}

	for(const auto & [key, value] : l_mapValue) {
		std::cout << key << " : " << value << '\n';
	}


	std::cout << '\n' << "=== STRUCTURE BINDING IN NESTED MAP ===" << '\n';
	std::map<std::string, std::map<uint32_t, std::string>> l_mapValue2;
	l_mapValue2["key1"].emplace(std::make_pair(1, "Learning Structred Binding 1"));
	l_mapValue2["key1"].emplace(std::make_pair(1, "Learning Structred Binding"));
	l_mapValue2["key2"].emplace(std::make_pair(2, "Learning Structred Binding 2"));
	for(const auto & [out_key, out_val] : l_mapValue2) {
		for(const auto & [in_key, in_val] : out_val) {
			std::cout   << "outer key: " << out_key
				<< " inner key: " << in_key
				<< " inner val: " << in_val << '\n';

		}  
	}

	S s = {13, 17};
	std::cout << '\n' << "=== STRUCTURE BINDING BY VALUE ===" << '\n';
	auto [i, j] = s;
	std::cout << s.i << ' ' << s.j << '\n';
	std::cout << i << ' ' << j << '\n';
	i = 16;
	std::cout << s.i << ' ' << s.j << '\n';
	std::cout << i << ' ' << j << '\n';

	std::cout << '\n' << "=== STRUCTURE BINDING BY REFERENCE ===" << '\n';
	auto & [p, q] = s;
	std::cout << s.i << ' ' << s.j << '\n';
	std::cout << p << ' ' << q << '\n';
	p = 26;
	std::cout << s.i << ' ' << s.j << '\n';
	std::cout << p << ' ' << q << '\n';

	return 0;
}


/***
 *	END OF FILE
 * ***/
