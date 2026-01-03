/*****

References

    Programming with C++20 | Andreas Fertig
    https://en.cppreference.com/w/cpp/language/constexpr.html
    https://en.cppreference.com/w/cpp/language/consteval.html
    https://en.cppreference.com/w/cpp/language/constinit.html

Chapter 12 | Doing (more) things at compiletime

12.4 Utilizing the new compile-time world: Sketching a car racing game

**********/

#include <format>
#include <iostream>
#include <cassert>
#include <cstring>

enum class CAR {
    HARRIER,
    XUV700,
    THAR,
    NONE
};

struct Car {
    virtual ~Car()  = default;
    constexpr virtual int speed() const = 0;
};

struct Harrier : Car {
    constexpr virtual int speed() const override { return 13; }
};

struct Xuv700 : Car {
    constexpr virtual int speed() const override { return 14; }
};

struct Thar : Car {
    constexpr virtual int speed() const override { return 12; }
};

constexpr Car * makeCar(const CAR car) {
    
    switch(car) {
        using enum CAR;
        case HARRIER: { return new Harrier{}; }
        case XUV700: { return new Xuv700{}; }
        case THAR: { return new Thar{}; }
        default: { return nullptr; }
    }

    return nullptr;
} 

constexpr CAR getFastestCar() {
    int max_speed = 0;
    CAR res{};

    for(int i_car = static_cast<int>(CAR::HARRIER); 
        i_car != static_cast<int>(CAR::NONE); 
        ++i_car) 
    {
        Car * car = makeCar(static_cast<CAR>(i_car));
        if(max_speed < car->speed()) {
            max_speed = car->speed();
            res = static_cast<CAR>(i_car);
        }

        delete car; car = nullptr;
    }

    return res;
}


int main() {

    constexpr auto fcar = getFastestCar();
    static_assert(fcar == CAR::XUV700);

    return 0; 
}

/*****
    END OF FILE
**********/


