/**********

    This example demonstrates about C++ smart pointers - shared_ptr

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

void useUniquePtr(std::shared_ptr<Base> upb) {
    upb->display();
}

std::shared_ptr<Base> getUniquePtr() {
    auto up = std::make_shared<Derived_01>();
    return up;
}

int main() {

    {
        std::cout << "=== shared pointer ===\n";

        {
            std::shared_ptr<Base> upb(new Base());
            upb->display();
        }
        {
            auto upb = std::make_shared<Base>();
            upb->display();
        }
        {
            std::shared_ptr<Base> upb(new Derived_01());
            upb->display();
        }
        {
            std::shared_ptr<Base> upb = std::make_shared<Derived_02>();
            upb->display();
        }
        {
            auto up = getUniquePtr();
            useUniquePtr(up);               // copyable
            useUniquePtr(std::move(up));
        }
        {
            auto dp = std::make_shared<Derived_01>();
            dp->display();
            
            std::shared_ptr<Base> spb1(dp);
            spb1->display();
            
            std::shared_ptr<Base> spb2;
            spb2 = dp;
            spb2->display();
        }
        {
            Derived_02 * dp = new Derived_02();
            std::shared_ptr<Base> upb1(dp);
            //std::shared_ptr<Base> upb2(dp); // this will lead to double free
        }
        {
            auto dp = std::make_shared<Derived_01>();
            //std::shared_ptr<Base> upb(dp.get()); // this will lead to double free
        }

        std::cout << "=== shared pointer for array ===\n";        
        {
            std::shared_ptr<Base[]> upba(new Base[3]);
            for(int i = 0; i < 3; ++i) {
                upba[i].display();
            }
        }
        {
            auto upba = std::make_shared<Base[]>(3);
            for(int i = 0; i < 3; ++i) {
                upba[i].display();
            }
        }        
    }

    return 0;
}

/**********
    END OF FILE
******************/

