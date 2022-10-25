#ifndef COMMON_HPP
#define COMMON_HPP

#include <string>
#include <iostream>

inline int common_gval = 10;
int common();

class CommonSt {
    inline static std::string msg = "this is a inline member varibale";

    public:
        void display() {
            std::clog << msg << '\n';
        }
};

inline CommonSt commonobj;


// you have to ensure that types are complete before you can initialize them
struct SomeType {
    int mval = 5;
    SomeType(int val) : mval(val) { }
    
    static SomeType someval; // // can only be declared here

};
inline SomeType SomeType::someval{17};


// For static data members, constexpr implies inline
struct Data {
    static constexpr int data = 10; // this is same as inline static constexpr int data = 10;
    // C++11/C++14: declaration
    // since C++17: definition
};


#endif