/**************
  This exmple demonstrates about compile time map implementation and its performace comparison to std::map

  For more info visit:
https://www.youtube.com/watch?v=INn3xa4pMfg&list=PLs3KjaCtOwSZ2tbuV1hx8Xz-rFZTan2J1&index=234
 *************/


#include <array>
#include <utility>
#include <algorithm>
#include <map>
#include <iostream>

namespace nonstd {

	template<typename Key, typename Value, std::size_t Size>
		class map {

			private:
				std::array<std::pair<Key, Value>, Size> data;

			public:

				constexpr map(const auto & data) : data(data) { }

				[[nodiscard]] constexpr Value at(const Key & key) const {
					const auto itr = std::find_if(data.cbegin(), data.cend(),
												  [&key](const auto & val ) { return val.first == key;} );

					if(data.cend() != itr) {
						return itr->second;
					}
					else {
						throw std::range_error("Key not found");
					}
				}
		};

}


using namespace  std::literals::string_view_literals;
static constexpr std::array<std::pair<std::string_view, uint32_t>, 5> students({
	{"student-1"sv, 1},
		{"student-2"sv, 2},
		{"student-3"sv, 3},
		{"student-4"sv, 4},
		{"student-5"sv, 5}
});

int main() {
	const auto data = std::map<std::string_view, uint32_t>(students.cbegin(), students.cend());
	std::clog << data.at("student-3") << '\n';

	const auto data2 = nonstd::map<std::string_view, uint32_t, students.size()>(students);
	std::clog << data2.at("student-3") << '\n';

	static constexpr auto data3 = nonstd::map<std::string_view, uint32_t, students.size()>(students);
	std::clog << data3.at("student-3") << '\n';

	return 0;
}

/********
  END OF FILE
 ********/
