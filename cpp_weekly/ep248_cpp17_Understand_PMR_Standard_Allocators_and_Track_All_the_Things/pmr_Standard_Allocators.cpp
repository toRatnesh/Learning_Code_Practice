/************
  This example demonstrates about 
  various memory resource class and functions

  For more info visit:
https://en.cppreference.com/w/cpp/header/memory_resource
https://www.youtube.com/watch?v=Zt0q3OEeuB0&list=PLs3KjaCtOwSZ2tbuV1hx8Xz-rFZTan2J1&index=249

 ************/

#include <fmt/format.h>

#include <array>
#include <iostream>
#include <memory_resource>
#include <string>
#include <vector>
#include <map>
#include <cassert>

// thanks to Rahil Baber
// Prints if new/delete gets used.
class print_resource : public std::pmr::memory_resource {
	public:
		print_resource(std::string name, std::pmr::memory_resource * upstream)
			: m_name(std::move(name)), m_upstream(upstream) {
				assert(upstream);
			}

	private:
		std::string m_name;
		std::pmr::memory_resource* m_upstream;


		std::string format_destroyed_bytes(std::byte* p, const std::size_t size) {
			std::string result = "";
			bool in_string = false;

			auto format_char = [](bool& in_string, const char c, const char next) {
				auto format_byte = [](const char byte) {
					return fmt::format(" {:02x}", static_cast<unsigned char>(byte));
				};

				if (std::isprint(static_cast<int>(c))) {
					if (!in_string) {
						if (std::isprint(static_cast<int>(next))) {
							in_string = true;
							return fmt::format(" \"{}", c);
						} else {
							return format_byte(c);
						}
					} else {
						return std::string(1, c);
					}
				} else {
					if (in_string) {
						in_string = false;
						return '"' + format_byte(c);
					}
					return format_byte(c);
				}
			};

			std::size_t pos = 0;
			for (; pos < std::min(size - 1, static_cast<std::size_t>(32)); ++pos) {
				result += format_char(in_string, static_cast<char>(p[pos]),
									  static_cast<char>(p[pos + 1]));
			}
			result += format_char(in_string, static_cast<char>(p[pos]), 0);
			if (in_string) {
				result += '"';
			}
			if (pos < (size - 1)) {
				result += " <truncated...>";
			}
			return result;
		}

		void* do_allocate(std::size_t bytes, std::size_t alignment) override {
			fmt::print("[(alloc  ) {}] Size: {} Alignment: {} \n", m_name, bytes,
					   alignment);
			auto result = m_upstream->allocate(bytes, alignment);
			fmt::print("[(alloc  ) {}] Address: {} \n", m_name, result);
			return result;
		}

		void do_deallocate(void* p, std::size_t bytes,
						   std::size_t alignment) override {
			fmt::print(
				"[(dealloc) {}] Address: {} Dealloc Size: {} Alignment: {} Data: {} \n",
				m_name, p, bytes, alignment,
				format_destroyed_bytes(static_cast<std::byte*>(p), bytes));
			m_upstream->deallocate(p, bytes, alignment);
		}

		bool do_is_equal(
			const std::pmr::memory_resource& other) const noexcept override {
			return this == &other;
		}

};

template <typename Container, typename... Values>
auto create_container(auto* resource, Values&&... values) {
	Container result{resource};
	result.reserve(sizeof...(values));
	(result.emplace_back(std::forward<Values>(values)), ...);
	return result;
}


int main() {

	std::pmr::vector<int> lvec;  // this will use new_delete_resource by default

	print_resource default_alloc{"Rouge PMR allocation", std::pmr::null_memory_resource()};
	std::pmr::set_default_resource(&default_alloc);

	std::pmr::vector<int> lvec_nullmem;
	//lvec_nullmem.push_back(2);  // will raise bad_alloc execption becase memory resource is null_memory_resource

	print_resource new_delete_alloc("new/delete alloc", std::pmr::new_delete_resource());
	std::pmr::unsynchronized_pool_resource pool(&new_delete_alloc);

	print_resource us_pool_alloc{"us pool alloc", &pool};
	std::pmr::map<std::pmr::string, int> lmap_poolalloc(&us_pool_alloc);

	lmap_poolalloc["One"] = 1;
	lmap_poolalloc.emplace("another long string", 3);

	return 0;
}

/*****
  END OF FILE
 *****/
