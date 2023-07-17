/**********

References

    C++17 - The Complete Guide | Nicolai M. Josuttis
    https://en.cppreference.com/w/cpp/header/memory_resource

27.2 Defining Custom Memory Resources

	To provide custom memory resources
	• derive from std::pmr::memory_resource
	• implement the private members
		– do_allocate()		to allocate memory
		– do_deallocate()	to deallocate memory
		– do_is_equal()		to define when two allocators are interchangeable (i.e., whether and when 
								one polymorphic memory resource object can deallocate memory allocated by another)

	As usual for smart memory resources, we support to pass another memory resource (usually called upstream) to wrap it or use it as fallback
	

27.2.1 Equality of Memory Resources

	bool do_is_equal(const std::pmr::memory_resource& other) const noexcept override {
		// same object?:
		if (this == &other) return true;
		// same type and prefix and equal upstream?:
		auto op = dynamic_cast<const Tracker*>(&other);
		return op != nullptr && op->prefix == prefix && upstream->is_equal(other);
	}

	moves are only performed as moves, if the source and destination are have interchangeable allocators.
	For polymorphic allocated types this is the case, when the move constructor is used (the new object copied the allocator).
	
	But if a non-interchangeable allocator is required (as with the tracker having a different prefix here) or if a different allocator type is used (as by moving to a std::string, which uses the default allocator), the memory gets copied
	
	Thus, interchangeability affects the performance of moves.	
	So, it is worthwhile to make memory resources interchangeable, because less moves convert to copies.
	But you should not make them more interchangeable than their purpose needs.

*************/

#include <iostream>
#include <memory_resource>
#include <array>

namespace nonstd {

    class my_mem_resource : public std::pmr::memory_resource {     
        public:
            explicit my_mem_resource(std::pmr::memory_resource * ups = std::pmr::get_default_resource())
                : m_ups{ups} { }
            explicit my_mem_resource(std::string prefix, std::pmr::memory_resource * ups = std::pmr::get_default_resource()) 
                : m_prefix{std::move(prefix)}, m_ups{ups} { }
                
        private:
            std::string                     m_prefix;
            std::pmr::memory_resource   *   m_ups;      // wrapper for fallback 
            void* do_allocate(  std::size_t bytes, 
                                std::size_t alignment ) override {
                std::cout << m_prefix << " allocate " << bytes << " bytes\n";
                return m_ups->allocate(bytes, alignment);
            }

            void do_deallocate( void* p,
                                std::size_t bytes,
                                std::size_t alignment ) override {
                std::cout << m_prefix << " deallocate " << bytes << " bytes\n";
                return m_ups->deallocate(p, bytes, alignment);
            }

            bool do_is_equal(const std::pmr::memory_resource& other) const noexcept override {
                if(this == &other)  return true;    // same object
                // same type and prefix and equal upstream
                auto op = dynamic_cast<const my_mem_resource *>(&other);
                return (nullptr != op) && ((op->m_prefix) == m_prefix) && (m_ups->is_equal(other)); 
            }
    };

}

int main() {
    {
        std::cout << "=== Defining Custom Memory Resources ===\n";
        nonstd::my_mem_resource     keep_pool_track{"Keeppool: "};

        //  only the keeppool allocations become (rather expensive) system calls
        //  even when the syncpool has deallocated all its memory, the keeppool doesn’t deallocate any

        std::pmr::monotonic_buffer_resource     keep_pool{65536, &keep_pool_track};
        {
            nonstd::my_mem_resource     sync_pool_track{"   Syncpool: ", &keep_pool};
            std::pmr::synchronized_pool_resource    sync_pool{&sync_pool_track};

            for(int num : {200, 100, 500, 200, 700}) {
                static int i = 0;
                std::pmr::vector<std::pmr::string>  coll{&sync_pool};
                coll.reserve(100);
                for(int j = 0; j < num; ++j) {
                    coll.emplace_back("a long string which will require memory allocation");
                }

                std::cout << "  --- iteration : " << ++i << " done for " << num << " elements\n";
            }

            std::cout << "*** Leaving scope of Syncpool\n";
        }
        std::cout << "*** Leaving scope of Keeppool\n";
    }

    {
        std::cout << "\n=== Equality of Memory Resources ===\n";
        {
        nonstd::my_mem_resource mem_res_01{"mem_res-01"};
        nonstd::my_mem_resource mem_res_02{"mem_res-02"};

        std::pmr::string    str1{"a long string which will require memory allocation", &mem_res_01};    // allocate with mem_res-01
        std::pmr::string    str2{std::move(str1), &mem_res_01};     // moves becoz same resource type
        
        std::pmr::string    str3{std::move(str2), &mem_res_02};     // copies becoz diff resource type 
        std::pmr::string    str4{std::move(str3)};                  // moves becoz allocator copied
        std::string         str5{std::move(str4)};                  // copies becoz different allocator
        }
        {
        nonstd::my_mem_resource mem_res_01;
        nonstd::my_mem_resource mem_res_02;

        std::pmr::string    str1{"a long string which will require memory allocation", &mem_res_01};    // allocate with mem_res-01
        std::pmr::string    str2{std::move(str1), &mem_res_01};     // moves becoz same resource type
        
        std::pmr::string    str3{std::move(str2), &mem_res_02};     // moves becoz diff resource type 
        std::pmr::string    str4{std::move(str3)};                  // moves becoz allocator copied
        std::string         str5{std::move(str4)};                  // copies becoz different allocator
        }
    }

    return 0;
}

/**********
    END OF FILE
*************/


