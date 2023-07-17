/**********

References

    C++17 - The Complete Guide | Nicolai M. Josuttis
    https://en.cppreference.com/w/cpp/header/memory_resource

Chapter 27 Polymorphic Memory Resources (PMR)

    C++17 now provides a pretty easy-to-use approach for predefined and 
    user-defined ways of memory allocation, which can be used for standard types and user-defined types

27.1 Using Standard Memory Resources

27.1.1 Motivating Example

Allocating Memory for Containers and Strings
	When using containers or any other type which requires memory allocations, memory (re-)allocations take time and in some contexts (such as embedded systems) it might be a problem to allocate heap memory at all
	
Not Allocating Memory for Containers
	By using polymorphic allocator, we can easily improve the situation
	by passing the address of our memory resource, we ensure that the vector uses our memory resource as polymorphic allocator
	std::array<std::byte, 200000> mem_buf;
	std::pmr::monotonic_buffer_resource mem_pool{mem_buf.data(), mem_buf.size()};
	std::pmr::vector<std::string> coll{&mem_pool};
	
	If the pre-allocated memory bytes is not enough, the vector will still allocate more memory on the heap. 
	That happens, because the monotonic_memory_resource uses the default allocator, which allocates memory with new, as fallback.
	
Not Allocating Memory At All
	We can even avoid using heap memory at all by defining the element type of the std::pmr::vector to be std::pmr::string
	
	The reason is that by default a pmr vector tries to propagate its allocator to its elements. This is not successful when the elements don’t use a polymorphic allocator, as it is the case with type std::string.
	However, by using type std::pmr::string, which is a string using a polymorphic allocator, the propagation works fine.
	
Reusing Memory Pools
	Here, after allocating the initial bytes on the stack, we use this memory again and again to initializea new resource pool for the vector and its elements.
	Each time the memory gets exceeded, the pool allocates additional memory on the heap, which is deallocated when the memory pool gets destructed.

*************/

#include <iostream>
#include <memory_resource>
#include <array>
#include <vector>
#include "track_new.hpp"

int main() {
    
    {
        std::cout << "=== Allocating Memory for Containers and Elements ===\n";

        TrackNew::reset();
        std::vector<std::string> coll;
        for (int i=0; i < 1000; ++i) {
            coll.emplace_back("a long string which will require memory allocation");
        }
        TrackNew::status();
    }
    {
        std::cout << "\n=== Not Allocating Memory for Containers ===\n";
        TrackNew::reset();
        std::array<std::byte, 200000> mem_buf;
        std::pmr::monotonic_buffer_resource mem_pool{mem_buf.data(), mem_buf.size()};
        std::pmr::vector<std::string> coll{&mem_pool};
        for (int i=0; i < 1000; ++i) {
            coll.emplace_back("a long string which will require memory allocation");
        }
        TrackNew::status();
    }
    {
        std::cout << "\n=== Not Allocating Memory At All ===\n";
        TrackNew::reset();
        std::array<std::byte, 200000> mem_buf;
        std::pmr::monotonic_buffer_resource mem_pool{mem_buf.data(), mem_buf.size()};
        std::pmr::vector<std::pmr::string> coll{&mem_pool};
        for (int i=0; i < 1000; ++i) {
            coll.emplace_back("a long string which will require memory allocation");
        }
        TrackNew::status();
    }
    {
        std::cout << "\n=== Reusing Memory Pools ===\n";
        std::array<std::byte, 200000> mem_buf;
        for(int num : {1000, 500, 2000, 1000, 3000, 4000}) {
            std::cout << num << " elements: ";
            TrackNew::reset();
            std::pmr::monotonic_buffer_resource mem_pool{mem_buf.data(), mem_buf.size()};
            std::pmr::vector<std::pmr::string> coll{&mem_pool};
            for (int i=0; i < num; ++i) {
                coll.emplace_back("a long string which will require memory allocation");
            }
            TrackNew::status();
        }

    }        
    return 0;
}

/**********
    END OF FILE
*************/


