/***********
 *	
 *	This example demonstrates the difference between accessing a map element using [] and at().
 *
 *	For more info visit:
 *	https://en.cppreference.com/w/cpp/container/map
 *
 * **************/


#include <iostream>
#include <string>
#include <array>
#include <map>

const std::array< std::pair<std::string, std::string>, 5 > l_student_record = {{
	{"001", "Student-001"},
		{"002", "Student-002"},
		{"003", "Student-003"},
		{"004", "Student-004"},
		{"005", "Student-005"}
}}; 

int main(int argc, char *argv[]) {
	auto l_map = std::map<std::string, std::string>(l_student_record.cbegin(), l_student_record.cend());

	for(auto it = l_map.cbegin(); it != l_map.cend(); ++it) {
		// CASE - 01
		//std::cout << "Key: " << it->first << " Value: " << it->second << '\n';
		// CASE - 02	
		//std::cout << "Key: " << it->first << " Value: " << l_map.at(it->first) << '\n';
		// CASE - 03	
		std::cout << "Key: " << it->first << " Value: " << l_map[it->first] << '\n';	
	}

	return 0;
}

/**************************
 *		EOF
 * ***********************/
