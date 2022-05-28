/**********
  This example demonstrates about how small integer operations result in unexpected result
  because these operatinos with small integer type are broken 
  and oerations are performed by converting small int type (like uint8_t and uint16_t) to int type

  For more info visit:
https://www.youtube.com/watch?v=R6_PFqOSa_c&list=PLs3KjaCtOwSZ2tbuV1hx8Xz-rFZTan2J1&index=312
 **********/


#include <iostream>
#include <cstdint>
#include <typeinfo>
#include <type_traits>
#include <bitset>

auto print_uint8_t_asInt(uint8_t val) {
	return static_cast<unsigned int>(val);
} 

int main () {
	uint8_t val1 = 0;
	uint8_t val2 = 1;

	uint16_t val3 = 0;
	uint16_t val4 = 1;

	std::clog << "(val1 - val2): " << (val1 - val2) << '\n';
	std::clog << "(val3 - val4): " << (val3 - val4) << '\n';

	std::clog << "static_cast<uint8_t>(val1 - val2): " << print_uint8_t_asInt(static_cast<uint8_t>(val1 - val2)) << '\n';
	std::clog << "static_cast<uint16_t>(val3 - val4): " << static_cast<uint16_t>(val3 - val4) << '\n';

	uint8_t res11 = val1 - val2;
	uint16_t res31 = val3 - val4;
	std::clog << "Assigning (val1 - val2) to uint8_t, result is :" << print_uint8_t_asInt(res11) << '\n';
	std::clog << "Assigning (val3 - val4) to uint16_t, result is :" << res31 << '\n';

	auto res12 = val1 - val2; 
	auto res32 = val3 - val4; 
	std::clog << "Assigning (val1 - val2) to auto, result is :" << res12 << '\n';
	std::clog << "Assigning (val3 - val4) to auto, result is :" << res32 << '\n';

	std::clog << "Type of (val1 - val2) when result is stored in auto type: " << typeid(res12).name() << '\n';
	std::clog << "Type of (val3 - val4) when result is stored in auto type: " << typeid(res32).name() << '\n';
	static_assert(std::is_same_v<decltype(res12), int>);
	static_assert(std::is_same_v<decltype(res32), int>);


	/*********
	  Singned Integer Arithmetic
	  1100 0000 >> 1
	  1110 0000

	  Unsiged Integer Arithmetic
	  1100 0000 >> 1
	  0110 0000
	 **********/

	uint8_t shift_res = (val1 - val2) >> 2; // signed ineteger arithmetic
	std::clog << "(val1 - val2) >> 2 : " << print_uint8_t_asInt(shift_res) << '\n';
	std::clog << std::bitset<8>(shift_res).to_string() << '\n';

	uint8_t shift_res2 = static_cast<uint8_t>(val1 - val2) >> 2; // unsigned integer arithmetic
	std::clog << "static_cast<uint8_t>(val1 - val2) : " << print_uint8_t_asInt(shift_res2) << '\n';
	std::clog << std::bitset<8>(shift_res2).to_string() << '\n';

	return 0;
}

/*****
  END OF FILE
 ****/
