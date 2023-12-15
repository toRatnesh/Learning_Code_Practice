/*****

Reference
    CppCon 2022 - Lightning Talks: -std=c++20 -- Will This C++ Code Compile? - Tulio Leao
    https://www.youtube.com/watch?v=87_Ld6CMHAw

Code which will not compile in C++20
1.  using reserved keyword from C++20
    https://en.cppreference.com/w/cpp/keyword

    Solution:   Rename the identifier

2.  Incompatibility between string and filesystem path converted to u8string
    https://en.cppreference.com/w/cpp/filesystem/path

    Solution:   Either change use of u8string() or change string varible to u8string

3.  Redundant/unallowed template-id on constructors and destructors
    Do not use template parameter for constructors and destructors

    Solution:   Remove redundant <T> on the constructor and destructor definition

4.  Aggregate initializaton of struct with deleted default constructor
    no user-declared or inherited constructors
    https://en.cppreference.com/w/cpp/language/aggregate_initialization

    Solution:   Implement your own constrcutor

5.  Removed std::allocator member functions
    https://en.cppreference.com/w/cpp/memory/allocator

    Solution:   Use std::allocator_traits
                std::construct_at, std::destroy_at  (incompatible)

6. change in std::accumulate handling of binary operations
    it moves the first parameter

    Solution:   Use const &, remove reference, stop using std::accumulate

**********/

#include <iostream>
#include <filesystem>
#include <vector>
#include <numeric>

// 3. Redundant/unallowed template-id on constructors and destructors

template<typename T>
class S {
    public:
    ~S<T>() { }
    S<T>()  { }
};

// 4. Aggregate initializaton of struct with deleted default constructor
struct S {
    S() = default;
    int a;
    int b;
};


int main() {

    std::cout << "=== 1. using reserved keyword from C++20 ===\n";
    int requires    = 5;
    int concept     = 6;


    std::cout << "\n=== 2. Incompatibility between string and filesystem path converted to u8string ===\n";
    std::filesystem::path       fpath{"/usr/user-name/dir"};
    std::string     spath = fpath.u8string();


    std::cout << "\n=== 3. Redundant/unallowed template-id on constructors and destructors ===\n";


    std::cout << "\n=== 4. Aggregate initializaton of struct with deleted default constructor ===\n";
    S s = {1, 2};


    std::cout << "\n=== 5. Removed std::allocator member functions ===\n";
    std::allocator<int> ialloc;
    int * pival;
    ialloc.construct(pival, 5);
    std::cout << "*pival " << *pival << '\n';
    ialloc.destroy(pival);

    // since C++20 use allocator_traits
    using alloc_trait = std::allocator_traits<decltype(ialloc)>;
    pival = alloc_trait::allocate(ialloc, 1);   // allocate for 1 int

    alloc_trait::construct(ialloc, pival, 13);
    std::cout << "*pival " << *pival << '\n';
    alloc_trait::deallocate(ialloc, pival, 1);


    std::cout << "\n=== 6. change in std::accumulate handling of binary operations ===\n";
    std::vector     avec{1, 2, 3, 4, 5};

    auto ret = std::accumulate(avec.begin(), avec.end(), 0, 
                    [](auto & a, auto & b){ return a+b;} 
                    //[](auto a, auto b){ return a+b;} 
                    );
    std::cout << "ret " << ret << '\n';    


    return 0;
}

/*****
    END OF FILE
**********/



