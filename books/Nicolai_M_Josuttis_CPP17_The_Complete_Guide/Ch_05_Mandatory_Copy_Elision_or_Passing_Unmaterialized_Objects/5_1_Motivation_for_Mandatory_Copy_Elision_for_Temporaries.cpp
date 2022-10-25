/***********

References
	C++17 - The Complete Guide | Nicolai M. Josuttis

5. Mandatory Copy Elision or Passing Unmaterialized Objects
    In C++17, former option to eliminate copying temporary objects, when passing or returning them by value, now becomes mandatory.

5.1 Motivation for Mandatory Copy Elision for Temporaries
    When a temporary is passed to or returned from a function by value, although the copy/move constructor was usually not called, it had to exist
    Since C++17, copy elision to initialize objects from temporaries is mandatory
    However, all other optional copy elisions still are optional and require a callable copy or move constructor

*************/

#include <iostream>

class WithoutCopyAndMove {
    public:
    WithoutCopyAndMove(int) { std::puts("WithoutCopyAndMove(int)"); }

    WithoutCopyAndMove(const WithoutCopyAndMove &) = delete;
    WithoutCopyAndMove(WithoutCopyAndMove && ) = delete;
};

bool take_WithoutCopyAndMove(WithoutCopyAndMove ) { return true; }
WithoutCopyAndMove retn_temp_WithoutCopyAndMove() { return WithoutCopyAndMove(5); }
//WithoutCopyAndMove retn_WithoutCopyAndMove() { WithoutCopyAndMove obj(5); return obj; } // requires copy and move
//WithoutCopyAndMove retn_WithoutCopyAndMove(WithoutCopyAndMove parm) { return parm; } // requires copy and move


class WithCopyAndMove {
    public:
    WithCopyAndMove(int) { std::puts("WithCopyAndMove(int)"); }
    WithCopyAndMove(const WithCopyAndMove &) { std::puts("const WithCopyAndMove &"); }
    WithCopyAndMove(WithCopyAndMove && ) { std::puts("WithCopyAndMove &&"); }

    WithCopyAndMove& operator=(const WithCopyAndMove &) { std::puts("operator=(const WithCopyAndMove &)"); return *this; }
    WithCopyAndMove& operator=(WithCopyAndMove && ) { std::puts("operator=(WithCopyAndMove && )"); return *this; }
    ~WithCopyAndMove() { std::puts("~WithCopyAndMove()"); }
};

bool take_WithCopyAndMove(WithCopyAndMove ) { return true; }
WithCopyAndMove retn_temp_WithCopyAndMove() { return WithCopyAndMove(5); }
WithCopyAndMove retn_WithCopyAndMove() { WithCopyAndMove obj(5); return obj; } // requires copy and move
WithCopyAndMove retn_WithCopyAndMove(WithCopyAndMove parm) { return parm; } // requires copy and move

int main() {
    // 5.1 Motivation for Mandatory Copy Elision for Temporaries
    {
        std::puts("=== CPP-17 no need of copy and move ===");
        take_WithoutCopyAndMove(WithoutCopyAndMove(5));
        take_WithoutCopyAndMove(retn_temp_WithoutCopyAndMove());
        [[maybe_unused]] WithoutCopyAndMove obj1 = 5;
        [[maybe_unused]] WithoutCopyAndMove obj2 = retn_temp_WithoutCopyAndMove();    
    }

    {
        std::puts("=== Pre CPP-17 need copy and move ===");
        take_WithCopyAndMove(WithCopyAndMove(5));
        take_WithCopyAndMove(retn_temp_WithCopyAndMove());
        [[maybe_unused]] WithCopyAndMove obj1 = 5;
        [[maybe_unused]] WithCopyAndMove obj2 = retn_temp_WithCopyAndMove();
    }

    {
        std::puts("=== Returning named object ===");
        take_WithCopyAndMove(retn_WithCopyAndMove());
        [[maybe_unused]] WithCopyAndMove obj1 = retn_WithCopyAndMove(); 
        take_WithCopyAndMove(retn_WithCopyAndMove(retn_WithCopyAndMove()));
        [[maybe_unused]] WithCopyAndMove obj2 = retn_WithCopyAndMove(retn_WithCopyAndMove()); 
    }

    return 0;
}

/*******
    END OF FILE
******/


