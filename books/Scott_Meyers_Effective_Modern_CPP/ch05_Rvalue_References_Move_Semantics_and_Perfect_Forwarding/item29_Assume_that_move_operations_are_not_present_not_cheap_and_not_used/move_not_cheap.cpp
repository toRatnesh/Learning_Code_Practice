/*****

References

    Effective Modern C++ | Scott Meyers
	https://en.cppreference.com/w/cpp/language/reference
	https://en.cppreference.com/w/cpp/language/reference

Item 29: Assume that move operations are not present, not cheap, and not used

	Move doesn’t just allow compilers to replace expensive copy operations with comparatively cheap moves, 
	it actually requires that they do so, when the proper conditions are fulfilled

	Several scenarios in which C++11’s move semantics do you no good:

	•	No move operations: The object to be moved from fails to offer move operations. 
		The move request therefore becomes a copy request.
	•	Move not faster: The object to be moved from has move operations 
		that are no faster than its copy operations.
	•	Move not usable: The context in which the moving would take place requires 
		a move operation that emits no exceptions, but that operation isn’t declared noexcept.
		
	Source object is lvalue: With very few exceptions (see e.g., Item 25) 
	only rvalues may be used as the source of a move operation.


Summary
	•	Assume that move operations are not present, not cheap, and not used.
	•	In code with known types or support for move semantics, there is no need for assumptions.

**********/

#include <iostream>
#include <vector>
#include <array>

class OnlyMoveWithoutNoexcept {

    public:
    ~OnlyMoveWithoutNoexcept() { std::puts("~OnlyMoveWithoutNoexcept()"); }
    OnlyMoveWithoutNoexcept() { std::puts("OnlyMoveWithoutNoexcept()"); }
    OnlyMoveWithoutNoexcept(OnlyMoveWithoutNoexcept && ) { 
        std::puts("OnlyMoveWithoutNoexcept(OnlyMoveWithoutNoexcept && ))");
    }
    OnlyMoveWithoutNoexcept& operator=(OnlyMoveWithoutNoexcept && ) {
        std::puts("operator=(OnlyMoveWithoutNoexcept && )");
        return *this;
    }      

    OnlyMoveWithoutNoexcept(const OnlyMoveWithoutNoexcept & )               = delete;
    OnlyMoveWithoutNoexcept& operator=(const OnlyMoveWithoutNoexcept & )    = delete;
};

class OnlyMoveWithNoexcept {

    public:
    ~OnlyMoveWithNoexcept() { std::puts("~OnlyMoveWithNoexcept()"); }
    OnlyMoveWithNoexcept() { std::puts("OnlyMoveWithNoexcept()"); }
    OnlyMoveWithNoexcept(OnlyMoveWithNoexcept && ) noexcept { 
        std::puts("OnlyMoveWithNoexcept(OnlyMoveWithNoexcept && ))");
    }
    OnlyMoveWithNoexcept& operator=(OnlyMoveWithNoexcept && ) noexcept {
        std::puts("operator=(OnlyMoveWithNoexcept && )");
        return *this;
    }

    OnlyMoveWithNoexcept(const OnlyMoveWithNoexcept & )             = delete;
    OnlyMoveWithNoexcept& operator=(const OnlyMoveWithNoexcept & )  = delete;
};


class OnlyCopyWithoutNoexcept {

    public:
    ~OnlyCopyWithoutNoexcept() { std::puts("~OnlyCopyWithoutNoexcept()"); }
    OnlyCopyWithoutNoexcept() { std::puts("OnlyCopyWithoutNoexcept()"); }
    OnlyCopyWithoutNoexcept(const OnlyCopyWithoutNoexcept & ) { 
        std::puts("OnlyCopyWithoutNoexcept(const OnlyCopyWithoutNoexcept & )");
    }
    OnlyCopyWithoutNoexcept& operator=(const OnlyCopyWithoutNoexcept & ) {
        std::puts("operator=(const OnlyCopyWithoutNoexcept & )");
        return *this;
    }  
    OnlyCopyWithoutNoexcept(OnlyCopyWithoutNoexcept && )            = delete;
    OnlyCopyWithoutNoexcept& operator=(OnlyCopyWithoutNoexcept && ) = delete;
};

class OnlyCopyWithNoexcept {

    public:
    ~OnlyCopyWithNoexcept() { std::puts("~OnlyCopyWithNoexcept()"); }
    OnlyCopyWithNoexcept() { std::puts("OnlyCopyWithNoexcept()"); }
    OnlyCopyWithNoexcept(const OnlyCopyWithNoexcept & ) noexcept { 
        std::puts("OnlyCopyWithNoexcept(const OnlyCopyWithNoexcept & )");
    }
    OnlyCopyWithNoexcept& operator=(const OnlyCopyWithNoexcept & ) noexcept {
        std::puts("operator=(const OnlyCopyWithNoexcept & )");
        return *this;
    }  
    OnlyCopyWithNoexcept(OnlyCopyWithNoexcept && )            = delete;
    OnlyCopyWithNoexcept& operator=(OnlyCopyWithNoexcept && ) = delete;
};

int main() {

    {
        constexpr std::size_t	ARR_SIZE{3};
        {   std::puts("=== Moving array of type which move is not noexcept ===");
            std::array<OnlyMoveWithoutNoexcept, ARR_SIZE>   larr{};
            std::array<OnlyMoveWithoutNoexcept, ARR_SIZE>   larr2{std::move(larr)};
        }

        {   std::puts("\n=== Moving array of type which move is noexcept ===");
            std::array<OnlyMoveWithNoexcept, ARR_SIZE>   larr{};
            std::array<OnlyMoveWithNoexcept, ARR_SIZE>   larr2{std::move(larr)};
        }


        {   std::puts("\n=== Moving array of type which only supports copy which is not noexcept ===");
            std::array<OnlyCopyWithoutNoexcept, ARR_SIZE>   larr{};
            std::array<OnlyCopyWithoutNoexcept, ARR_SIZE>   larr2{std::move(larr)};
        }

        {   std::puts("\n=== Moving array of type which only supports copy which is noexcept ===");
            std::array<OnlyCopyWithNoexcept, ARR_SIZE>   larr{};
            std::array<OnlyCopyWithNoexcept, ARR_SIZE>   larr2{std::move(larr)};
        }
    } 

    {
        constexpr std::size_t	ARR_SIZE{3};

        {   std::puts("=== Moving vector of type which move is not noexcept ===");
            std::vector<OnlyMoveWithoutNoexcept>   lvec(ARR_SIZE);
            std::vector<OnlyMoveWithoutNoexcept>   lvec2{std::move(lvec)};
        }

        {   std::puts("\n=== Moving vector of type which move is noexcept ===");
            std::vector<OnlyMoveWithNoexcept>   lvec(ARR_SIZE);
            std::vector<OnlyMoveWithNoexcept>   lvec2{std::move(lvec)};
        }


        {   std::puts("\n=== Moving vector of type which only supports copy which is not noexcept ===");
            std::vector<OnlyCopyWithoutNoexcept>   lvec(ARR_SIZE);
            std::vector<OnlyCopyWithoutNoexcept>   lvec2{std::move(lvec)};
        }

        {   std::puts("\n=== Moving vector of type which only supports copy which is noexcept ===");
            std::vector<OnlyCopyWithNoexcept>   lvec(ARR_SIZE);
            std::vector<OnlyCopyWithNoexcept>   lvec2{std::move(lvec)};
        }

    }
    return 0;
}

/*****
    END OF FILE
**********/


