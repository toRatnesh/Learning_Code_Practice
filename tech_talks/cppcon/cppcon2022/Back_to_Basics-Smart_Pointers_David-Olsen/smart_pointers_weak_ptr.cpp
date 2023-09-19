/**********

    This example demonstrates about C++ smart pointers - weak_ptr

    For more info visit
    Back to Basics: C++ Smart Pointers - David Olsen - CppCon 2022 
    https://www.youtube.com/watch?v=YokY6HzLkXs

******************/

#include <iostream>
#include <memory>

class Base {
    public:
    virtual ~Base() { std::cout << "~B()\n"; }
    Base() { std::cout << "B()\n"; }

    virtual void display()  {
        std::cout << "Base\n";
    }
};

class Derived_01 : public Base {
    public:
    virtual ~Derived_01() { std::cout << "~Derived_01()\n"; }
    Derived_01() { std::cout << "Derived_01()\n"; }
        
    virtual void display()  {
        std::cout << "Derived_01\n";
    }
};

class Derived_02 : public Base {
    public:
    virtual ~Derived_02() { std::cout << "~Derived_02()\n"; }
    Derived_02() { std::cout << "Derived_02()\n"; }
          
    virtual void display()  {
        std::cout << "Derived_02\n";
    }
};

void usePointer(std::shared_ptr<Base> upb) {
    upb->display();
}

std::shared_ptr<Base> getPointer() {
    auto up = std::make_shared<Derived_01>();
    return up;
}

int main() {

    {
        std::weak_ptr<Base> wp;
        {
            auto sp = std::make_shared<Derived_01>();
            wp = sp;
            std::cout << "Inside scope\n";
            std::cout << "wp.use_count() " << wp.use_count() << '\n';
            std::cout << "wp.expired() " << std::boolalpha << wp.expired() << '\n';
            auto sp2 = wp.lock();
            std::cout << "shared pointer using wp.lock() ";
            if(sp2) { std::cout << "working\n"; sp2->display(); } else { std::cout << "not working\n"; }   
        }
            std::cout << "Outside scope\n";
            std::cout << "wp.use_count() " << wp.use_count() << '\n';
            std::cout << "wp.expired() " << std::boolalpha << wp.expired() << '\n';
            auto sp2 = wp.lock();
            std::cout << "shared pointer using wp.lock() ";
            if(sp2) { std::cout << "working\n"; sp2->display(); } else { std::cout << "not working\n"; }            
    }

    return 0;
}

/**********
    END OF FILE
******************/

