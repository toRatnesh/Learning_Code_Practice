/**************
    This example demonstrates about 
    Using constructors from a base class in a derived class
    (Inheriting constructors)

    For more info visit:
    https://en.cppreference.com/w/cpp/language/using_declaration
**************/

#include <iostream>

struct Base {
    int bval = 7;

    virtual ~Base() { std::clog << "~Base()\n"; }
    Base() { std::clog << "Base()\n"; }
    Base(int val) : bval(val) { std::clog << "Base(int)\n"; }

    virtual void display() { std::clog << "base val: " << bval << '\n'; }
};

struct Derived : public Base {
    int dval = 8;

    virtual void display() override {
        std::clog << "base val: " << bval << " derived val: " << dval << '\n';
    }
};

struct Derived2 : public Base {
    int dval = 9;
    using Base::Base;  // inheriting the Base class constructor

    virtual void display() override {
        std::clog << "base val: " << bval << " derived val: " << dval << '\n';
    }
};

int main() {
    {
        Derived d;
        d.display();
    }
    {
        // Derived d(5); // this fails to call parameterized constructor of base class
    }

    {
        Derived2 d;
        d.display();
    }
    {
        Derived2 d(5);
        d.display();
    }

    return 0;
}

/*******
    END OF FILE
******/
