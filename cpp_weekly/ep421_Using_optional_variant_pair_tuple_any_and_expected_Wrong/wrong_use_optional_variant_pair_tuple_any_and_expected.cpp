/*****

    This example demonstrates about wrong use of optional, variant, pair, tuple, any, and expected
    Wrong use will not benefit from RVO

    For more info visit
    episode: https://www.youtube.com/watch?v=0yJk5yfdih0

**********/

#include <print>
#include <source_location>

void log(const std::source_location & slocation 
            = std::source_location::current()) noexcept {

    std::println("{}", slocation.function_name());
}

class Lifetime {
    public:
    ~Lifetime()     noexcept  { log(); }

    Lifetime()      noexcept  { log(); }
    explicit Lifetime(int )  noexcept  { log(); }

    Lifetime(const Lifetime & ) noexcept  { log(); }
    Lifetime(Lifetime && )      noexcept  { log(); }

    Lifetime& operator=(const Lifetime & ) noexcept  { 
        log(); 
        return *this;
    }
    Lifetime& operator=(Lifetime && )      noexcept  { 
        log(); 
        return *this;
    }
};

std::optional<Lifetime> get_optional_val() {

    //return {5};       // explicit constructor will result in CE

    // /*      RVO
    return std::optional<Lifetime>{std::in_place_t{}, 5};
    // */

    /*      RVO
    return std::optional<Lifetime>{4};
    */

    /*      RVO
    std::optional<Lifetime> retval;
    retval.emplace(3);
    return retval;
    */

    
    /*  No RVO
    std::optional<Lifetime> retval;
    retval = Lifetime{2};
    return retval;
    */

    
    /*  NO RVO
    return Lifetime{1};
    */
    
    
}

std::pair<Lifetime, Lifetime> get_pair_val() {



    //      RVO
    return std::pair<Lifetime, Lifetime>{1, 2};

    /*      RVO
    std::pair<Lifetime, Lifetime> retval{1, 2};
    return retval;
    */


    /*  NO RVO
    std::pair<Lifetime, Lifetime> retval;
    retval.first    = Lifetime{1};
    retval.second   = Lifetime{2};
    return retval;    
    */


    /*  NO RVO
    return std::make_pair(Lifetime(1), Lifetime(2));
    */

    /*  NO RVO
    return {Lifetime(1), Lifetime(2)};
    */
}

int main() {
    std::println("=== for optional ===");
    get_optional_val();
    std::println("=== for pair ===");
    get_pair_val();    
    return 0;
}

/*****
    END OF FILE
**********/


