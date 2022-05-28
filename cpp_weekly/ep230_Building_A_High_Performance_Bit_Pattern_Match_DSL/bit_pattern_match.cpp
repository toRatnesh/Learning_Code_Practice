/*************

  This exmaple demonstrates about implementing a bit pattern matcher

  For more info visit:
https://www.youtube.com/watch?v=-GqMLnWuHTU&list=PLs3KjaCtOwSZ2tbuV1hx8Xz-rFZTan2J1&index=231
https://github.com/lefticus/cpp_weekly/tree/master/HighPerfBitPattern

 **************/

#include <cstdint>
#include <stdexcept>

class BitPattern {

	private:
		uint64_t expected{};
		uint64_t mask{0xFFFFFFFFFFFFFFFF};

	public:
		template <std::size_t Size>
			explicit consteval BitPattern(const char (&pattern)[Size]) {
				uint64_t cur_bit = 1;
				cur_bit = (cur_bit << (Size - 2));

				for (const char ch : pattern) {
					if (0 == ch) {
						return;
					}

					if ('1' == ch) {
						expected =
							(expected |
							 cur_bit);  // this bit should be set in expected result
					} else if ('0' == ch) {
						// do nothing
					} else if (('x' == ch) || ('X' == ch)) {
						mask = (mask & (~cur_bit));  // remove these bits from mask

						/*
						   000010      // current bit
						   111101      // bitwise complement

						   110111      // hypothetical current mask
						   &   111101      // bitwise and
						   =   110101
						*/

					} else {
						throw std::logic_error(
							"Invalid chnaracter in BitPattern input");
					}
					cur_bit = (cur_bit >> 1);
				}
			}

		constexpr friend bool operator==(const uint64_t value,
										 const BitPattern& pattern) {
			return (value & pattern.mask) == pattern.expected;
		}
};

int main() {
	static_assert(0b11010101u == BitPattern("11xxx101"));

	return 0;
}

/*********
  END OF FILE
 ********/
