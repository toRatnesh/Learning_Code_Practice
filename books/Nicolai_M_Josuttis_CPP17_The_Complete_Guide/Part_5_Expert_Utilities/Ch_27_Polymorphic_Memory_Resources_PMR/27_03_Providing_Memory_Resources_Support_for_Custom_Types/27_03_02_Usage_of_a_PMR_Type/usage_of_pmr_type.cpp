/**********

References

    C++17 - The Complete Guide | Nicolai M. Josuttis
    https://en.cppreference.com/w/cpp/header/memory_resource
    https://en.cppreference.com/w/cpp/memory/polymorphic_allocator

27.3 Providing Memory Resources Support for Custom Types

27.3.2 Usage of a PMR Type

    when we push a copy of the custom type into the vector, the vector ensures that the elements all also use its polymorphic allocator.
    For this reason, the extended copy constructor of the custom type is called with the vector allocator as second argument so that the element is initialized with the custom memory resource.

*************/

#include <iostream>
#include <memory_resource>
#include <array>
#include <vector>
#include <cstddef>

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

    class Student {
        std::pmr::string        m_name;
        int                     m_id;
        public:
        using allocator_type = std::pmr::polymorphic_allocator<std::byte>;
        Student(std::pmr::string name, int id, allocator_type alloc = {}) 
            : m_name{std::move(name), alloc}, m_id{id} {
                std::cout << "Construtor - Parameterized constructor\n";
        }

        Student(const Student & stu, allocator_type alloc)
            : m_name{stu.m_name, alloc}, m_id{stu.m_id} {
                std::cout << "Construtor - Copy constructor\n";
        }

        Student(Student && stu, allocator_type alloc)
            : m_name{std::move(stu.m_name), alloc}, m_id{std::move(stu.m_id)} {
                std::cout << "Construtor - Move constructor\n";
        }

        void setName(std::pmr::string name) { m_name = std::move(name); }
        void setId(const int id)            { m_id = id; }

        std::pmr::string    getName()   const { return m_name; }
        int                 getId()     const { return m_id; }

        std::string         getNameAsString()   const { return std::string{m_name}; }
    };
}

int main() {
    nonstd::my_mem_resource                 keep_pool_track{"Keeppool: "};
    std::pmr::monotonic_buffer_resource     keep_mem_pool{2048, &keep_pool_track};

    {
        std::cout << "=== PMR vector with PMR objects ===\n";
        nonstd::Student stu1{"this is a long string which will require memory allocation", 1, &keep_mem_pool};
        nonstd::Student stu2{"this is a long string which will require memory allocation", 2, &keep_mem_pool};
        nonstd::Student stu3{"this is a long string which will require memory allocation", 3, &keep_mem_pool};
        nonstd::Student stu4{"this is a long string which will require memory allocation", 4, &keep_mem_pool};

        std::pmr::vector<nonstd::Student>   stu_coll{&keep_mem_pool};
        stu_coll.push_back(stu1);
        stu_coll.push_back(stu2);
        stu_coll.push_back(stu3);
        stu_coll.push_back(std::move(stu4));

        for(const auto & elem : stu_coll) {
            std::cout << elem.getName() << '\n';
        }
    }

    {
        std::cout << "=== PMR vector with default allocated objects ===\n";
        nonstd::Student stu1{"this is a long string which will require memory allocation", 1};
        nonstd::Student stu2{"this is a long string which will require memory allocation", 2};
        nonstd::Student stu3{"this is a long string which will require memory allocation", 3};
        nonstd::Student stu4{"this is a long string which will require memory allocation", 4};

        std::pmr::vector<nonstd::Student>   stu_coll{&keep_mem_pool};
        stu_coll.push_back(stu1);
        stu_coll.push_back(stu2);
        stu_coll.push_back(stu3);
        stu_coll.push_back(std::move(stu4));

        for(const auto & elem : stu_coll) {
            std::cout << elem.getName() << '\n';
        }
    }

    return 0;
}

/**********
    END OF FILE
*************/


