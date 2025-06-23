/*****

References
    episode https://www.youtube.com/watch?v=NoFQnqUZLdA
    https://en.cppreference.com/w/cpp/language/final

**********/

#include <iostream>

class Base { 
    public:
    virtual void welcome() final {
        std::puts("Inside Base::welcome()");
    }
    virtual void display() {
        std::puts("Inside Base::display()");
    }
    virtual void printIt() {
        std::puts("Inside Base::printIt()");
    }    
};

class Derived : public Base { 
    public:    
    virtual void display() override {
        std::puts("Inside Derived::display()");
    }
    virtual void printIt() override final {
        std::puts("Inside Derived::printIt()");
    }     
};

class MoreDerived : public Derived {
    public:
    virtual void display() override {
        std::puts("Inside MoreDerived::display()");
    }

    /*  CE error: virtual function 'virtual void MoreDerived::printIt()' overriding final function  
    virtual void printIt() override final {
        std::puts("Inside MoreDerived::printIt()");
    } 
    */      
};

class FinalBase final { };
// CE error: cannot derive from 'final' base 'FinalBase' in derived type 'TryDeriveFromFinalClass'
// class TryDeriveFromFinalClass : public FinalBase {};

void usingBase(Base & base) {
    // welcome method is final inside Base class, so early binding will take place
    // when called for object of Base class or classes derived from Base class
    base.welcome();
    base.display();
    base.printIt();

    std::puts("");
}

void usingDerived(Derived & derived) {
    derived.welcome();
    derived.display();

    // printIt method is final inside Derived class, so early binding will take place
    // when called for object of Derived class or classes derived from Derived class    
    derived.printIt();

    std::puts("");
}

void usingMoreDerived(Derived & more_derived) {
    more_derived.welcome();
    more_derived.display();
    more_derived.printIt();

    std::puts("");
}

int main() {

    Base        base;
    Derived     derived;
    MoreDerived more_derived;

    std::puts("=== Using function taking base class object as param ===");
    usingBase(base);
    usingBase(derived);
    usingBase(more_derived);

    std::puts("\n=== Using function taking derived class object as param ===");
    //usingDerived(base);
    usingDerived(derived);
    usingDerived(more_derived); 

    std::puts("\n=== Using function taking more derived class object as param ===");
    //usingMoreDerived(base);
    //usingMoreDerived(derived);
    usingMoreDerived(more_derived);


    return 0;
}

/*****
    END OF FILE
**********/


