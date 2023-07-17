/**********

References

    C++17 - The Complete Guide | Nicolai M. Josuttis
    https://en.cppreference.com/w/cpp/header/memory_resource

Chapter 27 Polymorphic Memory Resources (PMR)

    C++17 now provides a pretty easy-to-use approach for predefined and 
    user-defined ways of memory allocation, which can be used for standard types and user-defined types

27.1 Using Standard Memory Resources

27.1.3 Standard Memory Resources in Detail

new_delete_resource()
	default memory resource
	It handles allocations like they are handled when using the default allocator:
		• Each allocation calls new
		• Each deallocation calls delete

	NOTE: a polymorphic allocator with this memory resource is not interchangeable with the default allocator, because they simply have different types. For this reason 
	std::string s{"my string with some value"};
	std::pmr::string ps{std::move(s), std::pmr::new_delete_resource()}; // copies
	
	will not move (pass the allocated memory for s to ps). Instead, the memory of s will be copied to new memory of ps allocated with new.

synchronized_pool_resource() and unsynchronized_pool_resource()
	try to locate all memory close to each other
	Thus, they force little fragmentation of memory
	If memory of pool is only handled by a single thread (or that (de)allocations are synchronized), you should prefer unsynchronized_pool_resource
	
	Both classes still use an underlying memory resource to actually perform the allocations and deallocations.
	They only act as a wrapper ensuring that these allocations are better clustered
	std::pmr::synchronized_pool_resource myPool;
	is the same as
	std::pmr::synchronized_pool_resource myPool{std::pmr::get_default_resource()};
	
	One major application of these pools is to ensure that elements in a node based container are located next to each other.
	This may also increase the performance of the containers significantly
	This depends on the implementation of the memory resource
	
monotonic_buffer_resource()
	also provides the ability to place all memory in big chunks of memory
	it has two other abilities:
		• You can pass a buffer to be used as memory. This, especially, can be memory allocated on the stack.
		• The memory resource never deallocates until the resource as a whole gets deallocated.

	std::array<std::byte, 200000> buf;
	std::pmr::monotonic_buffer_resource pool{buf.data(), buf.size()};
	
	it also tries to avoid fragmentation.
	it is super fast because deallocation is a no-op and you skip the need to track deallocated memory for further use
	Whenever there is a request to allocate memory it just return the next free piece of memory until all memory is exhausted
	
	Note that objects are still destructed. Only their memory is not freed
	You should prefer this resource, if you either have no deletes or if you have enough memory to waste (not reusing memory that was previously used by another object).
	
	In addition, you can define which memory resource it uses to perform the allocations. This allows us to chain memory resources to provide more sophisticated memory resources.
	std::pmr::monotonic_buffer_resource keepAllocatedPool{10000};
	std::pmr::synchronized_pool_resource pool{&keepAllocatedPool};

null_memory_resource()
	each allocation throws a bad_alloc exception
	application is to ensure that a memory pool using memory allocated on the stack not suddenly allocates memory on the heap, if it needs more

*************/

#include <iostream>
#include <memory_resource>
#include <array>
#include <map>
#include <vector>

int main() {
    {
        std::cout << "=== new_delete_resource() ===\n";
        std::string str("sample string");
        std::pmr::string new_str{std::move(str), std::pmr::new_delete_resource()}; // no move because diffrence in allocator

        std::cout << "str: " << str << '\n';
        std::cout << "new_str: " << new_str << '\n';
    }
    {
        std::cout << "\n=== (un)synchronized_pool_resource() ===\n";
        {
            std::cout << "--- std::map ---\n";
            std::map<int, std::string>  l_map;
            for(int i = 0; i < 10; ++i) {
                std::string str{"a long string which will require memory allocation" + std::to_string(i)};
                l_map.emplace(i, str);
            }

            std::cout << "diff: ";
            for(const auto & elem : l_map) {
                static long long    last_addr   = 0;
                long long           curr_addr   = reinterpret_cast<long long>(&elem);
                std::cout << (curr_addr - last_addr) << ' ';
                last_addr = curr_addr;
            }
            std::cout << '\n';

        }
        {
            std::cout << "--- std::pmr::map with std::pmr::synchronized_pool_resource ---\n";
            std::pmr::synchronized_pool_resource    mem_pool;
            std::pmr::map<int, std::pmr::string>    l_map{&mem_pool};
            for(int i = 0; i < 10; ++i) {
                std::string str{"a long string which will require memory allocation" + std::to_string(i)};
                l_map.emplace(i, str);
            }

            std::cout << "diff: ";
            for(const auto & elem : l_map) {
                static long long    last_addr   = 0;
                long long           curr_addr   = reinterpret_cast<long long>(&elem);
                std::cout << (curr_addr - last_addr) << ' ';
                last_addr = curr_addr;
            }
            std::cout << '\n';
        }        
    }    
    {
        std::cout << "\n=== monotonic_buffer_resource() ===\n";
        {
            std::cout << "--- std::map ---\n";
            std::map<int, std::string>  l_map;
            for(int i = 0; i < 10; ++i) {
                std::string str{"a long string which will require memory allocation" + std::to_string(i)};
                l_map.emplace(i, str);
            }

            std::cout << "diff: ";
            for(const auto & elem : l_map) {
                static long long    last_addr   = 0;
                long long           curr_addr   = reinterpret_cast<long long>(&elem);
                std::cout << (curr_addr - last_addr) << ' ';
                last_addr = curr_addr;
            }
            std::cout << '\n';
        }
        {
            std::cout << "--- std::pmr::map with std::pmr::monotonic_buffer_resource ---\n";
            std::array<std::byte, 4096>   mem_buf;
            std::pmr::monotonic_buffer_resource    mem_pool{mem_buf.data(), mem_buf.size()};
            std::pmr::map<int, std::pmr::string>    l_map{&mem_pool};
            for(int i = 0; i < 10; ++i) {
                std::string str{"a long string which will require memory allocation" + std::to_string(i)};
                l_map.emplace(i, str);
            }

            std::cout << "diff: ";
            for(const auto & elem : l_map) {
                static long long    last_addr   = 0;
                long long           curr_addr   = reinterpret_cast<long long>(&elem);
                std::cout << (curr_addr - last_addr) << ' ';
                last_addr = curr_addr;
            }
            std::cout << '\n';
        } 
        {
            std::cout << "--- std::pmr::map with chain of memory resource std::pmr::monotonic_buffer_resource and std::pmr::synchronized_pool_resource ---\n";
            std::array<std::byte, 4096>   mem_buf;
            std::pmr::monotonic_buffer_resource     mbr_mem_pool{mem_buf.data(), mem_buf.size()};
            std::pmr::synchronized_pool_resource    syn_mem_pool{&mbr_mem_pool};
            std::pmr::map<int, std::pmr::string>    l_map{&syn_mem_pool};
            for(int i = 0; i < 10; ++i) {
                std::string str{"a long string which will require memory allocation" + std::to_string(i)};
                l_map.emplace(i, str);
            }

            std::cout << "diff: ";
            for(const auto & elem : l_map) {
                static long long    last_addr   = 0;
                long long           curr_addr   = reinterpret_cast<long long>(&elem);
                std::cout << (curr_addr - last_addr) << ' ';
                last_addr = curr_addr;
            }
            std::cout << '\n';
        }                
    }
    {
        std::cout << "\n=== null_memory_resource() ===\n";
        std::array<std::byte, 1024>             mem_buf;
        std::pmr::monotonic_buffer_resource     mem_pool{mem_buf.data(), mem_buf.size(), 
                                                    std::pmr::null_memory_resource()};
        std::pmr::map<int, std::pmr::string>    l_map{&mem_pool};
        for(int i = 0; i < 10; ++i) {
            try {
                std::string str{"a long string which will require memory allocation" + std::to_string(i)};
                l_map.emplace(i, str);
            } catch (const std::exception & exp) {
                std::cout << "EXCEPTION: " << exp.what() << '\n';
            }
        }

        std::cout << "diff: ";
        for(const auto & elem : l_map) {
            static long long    last_addr   = 0;
            long long           curr_addr   = reinterpret_cast<long long>(&elem);
            std::cout << (curr_addr - last_addr) << ' ';
            last_addr = curr_addr;
        }
        std::cout << '\n';
    }
    return 0;
}

/**********
    END OF FILE
*************/


