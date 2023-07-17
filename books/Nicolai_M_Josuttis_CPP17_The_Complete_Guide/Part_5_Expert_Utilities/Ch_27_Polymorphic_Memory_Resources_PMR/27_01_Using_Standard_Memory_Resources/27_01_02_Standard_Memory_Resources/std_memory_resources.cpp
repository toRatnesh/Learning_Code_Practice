/**********

References

    C++17 - The Complete Guide | Nicolai M. Josuttis
    https://en.cppreference.com/w/cpp/header/memory_resource

Chapter 27 Polymorphic Memory Resources (PMR)

    C++17 now provides a pretty easy-to-use approach for predefined and 
    user-defined ways of memory allocation, which can be used for standard types and user-defined types

27.1 Using Standard Memory Resources

27.1.2 Standard Memory Resources

--------------------------------------------------------------------------- 
Memory Resource 				Behavior
---------------------------------------------------------------------------
new_delete_resource()			yields a pointer to a memory resource calling new and delete
synchronized_pool_resource		class to create memory resources with little fragmentation, thread-safe
unsynchronized_pool_resource	class to create memory resources with little fragmentation, not thread-safe
monotonic_buffer_resource		class to create memory resources that never deallocates, optionally using a passed buffer, not thread-safe
null_memory_resource()			yields a pointer to a memory resource where each allocation fails
---------------------------------------------------------------------------

new_delete_resource() and null_memory_resource() are functions that return the pointer to a global memory resource. which is defined as a singleton
The other three memory resources are classes, where you have to create objects and pass pointers to these objects to the polymorphic allocators
For this reason it is important that you ensure that the resource objects these pointers refer to exist until the last deallocation is called

std::pmr::string str{"a long string which will require memory allocation", std::pmr::new_delete_resource()};

std::pmr::synchronized_pool_resource mem_pool;
std::pmr::string str{"a long string which will require memory allocation", &mem_pool};

Default Memory Resource
    Polymorphic allocators have a default memory resource, which is used if no other memory resource is passed
    ---------------------------------------------------------------------------
    Memory Resource					Behavior
    ---------------------------------------------------------------------------
    get_default_resource()			yields a pointer to the current default memory resource
    set_default_resource(memresPtr)	sets the default memory resource (passing a pointer) and yields a pointer to the previous one
    ---------------------------------------------------------------------------

    static std::pmr::synchronized_pool_resource mem_pool;
    std::pmr::memory_resource* old_mem_pool = std::pmr::set_default_resource(&mem_pool);	// set new default memory resource
    std::pmr::set_default_resource(old);	// restore old default memory resource as default


    If required, It is a good approach to create a custom memory resource before anything else as static object in main()
    int main() {
        static std::pmr::synchronized_pool_resource mem_pool;
        ...
    }

    Alternatively, provide a global function returning your resource as static object:
    memory_resource* myResource()  {
        static std::pmr::synchronized_pool_resource mem_pool;
        return &mem_pool;
    }

*************/

#include <iostream>
#include <memory_resource>
#include <array>


std::pmr::memory_resource* getMemoryResource()  {
    static std::pmr::synchronized_pool_resource mem_pool;
    return &mem_pool;
}

int main() {
    {
        std::cout << "=== new_delete_resource() ===\n";
        std::pmr::string str{"a long string which will require memory allocation", std::pmr::new_delete_resource()};
        std::cout << "str: " << str << '\n';
    }
    {
        std::cout << "\n=== null_memory_resource() ===\n";
        try {
            std::pmr::string str{"a long string which will require memory allocation", std::pmr::null_memory_resource()};
        }
        catch(const std::exception & exp) {
            std::cout << "EXCEPTION: " << exp.what() << '\n';
        }
        //std::cout << "str: " << str << '\n';
    }
    {
        std::cout << "\n=== synchronized_pool_resource() ===\n";
        std::pmr::synchronized_pool_resource sn_mempool;
        std::pmr::string str{"a long string which will require memory allocation", &sn_mempool};
        std::cout << "str: " << str << '\n';
    }    
    {
        std::cout << "\n=== unsynchronized_pool_resource() ===\n";
        std::pmr::unsynchronized_pool_resource us_mempool;
        std::pmr::string str{"a long string which will require memory allocation", &us_mempool};
        std::cout << "str: " << str << '\n';
    }
    {
        std::cout << "\n=== monotonic_buffer_resource() ===\n";
        std::array<std::byte, 256> mem_buf;
        std::pmr::monotonic_buffer_resource mb_mempool{mem_buf.data(), mem_buf.size()};
        std::pmr::string str{"a long string which will require memory allocation", &mb_mempool};
        std::cout << "str: " << str << '\n';
    }
    {
        std::cout << "\n=== get_default_resource() ===\n";
        std::pmr::memory_resource* mem_pool = std::pmr::get_default_resource();
        std::pmr::string str{"a long string which will require memory allocation", mem_pool};
        std::cout << "str: " << str << '\n';
    }
    {
        std::cout << "\n=== set_default_resource() ===\n";
        std::pmr::unsynchronized_pool_resource us_mempool;
        std::pmr::memory_resource* mem_pool = std::pmr::set_default_resource(&us_mempool);
        std::pmr::string str1{"a long string which will require memory allocation"};
        std::cout << "str1: " << str1 << '\n';
        std::pmr::set_default_resource(mem_pool);	// restore old default memory resource as default
        std::pmr::string str2{"a long string which will require memory allocation"};
        std::cout << "str2: " << str2 << '\n';
    }
    {
        std::cout << "\n=== memory resource using global function() ===\n";
        std::pmr::string str{"a long string which will require memory allocation", getMemoryResource()};
        std::cout << "str: " << str << '\n';
    }    
    return 0;
}

/**********
    END OF FILE
*************/


