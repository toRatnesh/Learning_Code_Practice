/**********
  This example is about corrections about mistakes in previous episodes
  related to PMR

  Important Updates and errata
 * In this episode (and several others about PMR) I conflate the terms
 "memory_resource" and "allocator." Generally speaking, if I say "allocator," I
 mean "memory_resource".
 * It's important to note that the primary problem with the "initializer_list"
 usage is the fact that initializer_lists are `const` and can *never* be moved
 from. Where and how the data was allocated is a secondary matter.
 * print_alloc should really be named "printing_resource"

 We made some mistakes along  the way that most people missed. Some important
 updates here for how to make sure you are using your allocator aware types
 correctly.

 For more info visit:
 {NOTE: code is coped from compiler explorer link available in video description and added content for my understanding}
https://www.youtube.com/watch?v=6BLlIj2QoT8&list=PLs3KjaCtOwSZ2tbuV1hx8Xz-rFZTan2J1&index=247

 *********/

#include <array>
#include <iostream>
#include <memory_resource>
#include <string>
#include <vector>

// Prints if new/delete gets used.
class print_alloc : public std::pmr::memory_resource {
	private:
		void* do_allocate(std::size_t bytes, std::size_t alignment) override {
			std::clog << "Allocating " << bytes << '\n';
			return std::pmr::new_delete_resource()->allocate(bytes, alignment);
		}

		void do_deallocate(void* p, std::size_t bytes,
						   std::size_t alignment) override {
			std::clog << "Deallocating " << bytes << ": '";

			for (std::size_t i = 0; i < bytes; ++i) {
				std::clog << *(static_cast<char*>(p) + i);
			}
			std::clog << "'\n";
			return std::pmr::new_delete_resource()->deallocate(p, bytes, alignment);
		}

		bool do_is_equal(
			const std::pmr::memory_resource& other) const noexcept override {
			return std::pmr::new_delete_resource()->is_equal(other);
		}
};

template <typename Container, typename... Values>
auto create_container(auto* resource, Values&&... values) {
	Container result{resource};
	result.reserve(sizeof...(values));
	(result.emplace_back(std::forward<Values>(values)), ...);
	return result;
};

int main() {
	// remember initializer lists are broken.
	print_alloc mem;
	std::pmr::set_default_resource(&mem);

	std::array<std::uint8_t, 1024> buffer{};
	std::pmr::monotonic_buffer_resource mem_resource(buffer.data(),
													 buffer.size());

	std::clog << "initializing vector for int\n";
	{ 
		std::pmr::vector<int> lv{1, 2, 3, 4}; 
	}
	std::clog << "initializing vector for std::pmr::string\n";
	{
		std::pmr::vector<std::pmr::string> lvs{{"Learning", "PMR"}, &mem_resource};
	}

	/***********
Que:    At run time memmory is allocated and deallocted for new added 'Correcting previous mistakes'
We are using pms::vector with pmr::string, still why memory is allocated and deallocated, Why?

Ans:    initializer_list are broken
For example initializer list will be generated using arr like this

	// Generated code for initializer_list using https://cppinsights.io/
	const std::basic_string<char, std::char_traits<char>, std::pmr::polymorphic_allocator<char> > __list0[3]{
	std::basic_string<char, std::char_traits<char>, std::pmr::polymorphic_allocator<char> >("Learning", std::pmr::polymorphic_allocator<char>()),
	std::basic_string<char, std::char_traits<char>, std::pmr::polymorphic_allocator<char> >("PMR", std::pmr::polymorphic_allocator<char>()),
	std::basic_string<char, std::char_traits<char>, std::pmr::polymorphic_allocator<char> >("Correcting previous mistakes",
	std::pmr::polymorphic_allocator<char>())};

	std::initializer_list<std::pmr::string> li = std::initializer_list<std::basic_string<char, std::char_traits<char>, std::pmr::polymorphic_allocator<char> > >{__list0, 0};

	 ************/
	std::clog << "initializing vector for std::pmr::string\n";
	{
		std::pmr::vector<std::pmr::string> lvs{{"Learning", "PMR", "Correcting previous mistakes"}, &mem_resource};
		lvs.push_back("push_back will also allocate and deallocate because it copies data");
		lvs.emplace_back("emplace_back will not allocate and deallocate");  // but emplace_back will constantly realloc
		// remedy for problem with constant realloc is to create our container 
	}


	auto vec = create_container<std::pmr::vector<std::pmr::string>>(
		&mem_resource, "Hello", "World", "Hello Long String",
		"Another Long String");


	return 0;
}

/******
  END OF FILE
 ******/
