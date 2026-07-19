/*****

References

	episode https://www.youtube.com/watch?v=_ZvNJciCXeE

    code https://godbolt.org/z/ffT7q1afs

    This example demonstrates about why we should never call virtual member fucntion from inside constructor or destructor
    
    Inside constructor and destructor vptr points to vtable of the current class only

**********/

#include <iostream>
#include <string>
#include <memory>

class Base {

    public:
    virtual ~Base( ) {  
        display(); 
        std::cout << "~Base()\n";
    }
    Base() { 
        std::cout << "Base()\n"; 
        display();
    }
    virtual void display() { 
        std::cout << "Base::display " << __func__ << '\n'; 
    }
};


class Derived : public Base {

    public:
    virtual ~Derived( ) {  
        display();
        std::cout << "~Derived()\n"; 
    }
    Derived() : Base() { 
        std::cout << "Derived()\n"; 
        display();
    }

    virtual void display() override { 
        std::cout << "Derived::display " << __func__ << '\n'; 
    }

};

int main() {

    std::unique_ptr<Base> bup = std::make_unique<Derived>();
    bup->display();

    return 0;
}

/*****
    END OF FILE
**********/