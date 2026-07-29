/*****

References:
    episode     https://www.youtube.com/watch?v=MbqWWkP8Ras
    https://en.cppreference.com/cpp/language/final

    code https://godbolt.org/z/nrWjhhjf5

final specifier
    Specifies that a virtual function cannot be overridden in a derived class, 
    or that a class cannot be derived from.

    When applied to a member function, the identifier final appears immediately after the declarator 
    in the syntax of a member function declaration or a member function definition inside a class definition.

    When applied to a class (including struct and union), the identifier final appears at the beginning 
    of the class definition, immediately after the name of the class, and cannot appear in a class declaration.


    final may improve performance by calling the final member function of the respective because 
    they do not need to lookup into vtable for calling final member function

**********/

#include <iostream>
#include <memory>

class Base {
    
    public:

    virtual ~Base() = default;
    
    virtual void ag() const {
        std::cout << "Base::ag\n";
    }

    virtual void og() const {
        std::cout << "Base::og\n";
    }

    virtual void hag() const {
        std::cout << "Base::hag\n";
    }    

};

class Derived : public Base {
    
    public:

    virtual ~Derived() = default;
    
    virtual void ag() const final {
        std::cout << "Derived::ag\n";
    }
   
};

class MoreDerived final : public Derived {
    
    public:
    
    virtual ~MoreDerived() = default;
    
    virtual void og() const {
        std::cout << "MoreDerived::og\n";
    }
   
};

auto fun1(const Base & bobj) {
    bobj.ag();
    bobj.og();
    bobj.hag();
}

auto fun2(const Derived & dobj) {
    dobj.ag();
    dobj.og();
    dobj.hag();
}

auto fun3(const MoreDerived & mobj) {
    mobj.ag();
    mobj.og();
    mobj.hag();
}

int main()
{


    {
        std::unique_ptr<Base> bp = std::make_unique<Base>();
        bp->ag();
        bp->og();
        bp->hag();
    }
    std::cout << '\n';

    {
        std::unique_ptr<Base> bp = std::make_unique<Derived>();
        bp->ag();
        bp->og();
        bp->hag();
    }
    std::cout << '\n';

    {
        std::unique_ptr<Base> bp = std::make_unique<MoreDerived>();
        bp->ag();
        bp->og();
        bp->hag();
    }
    

    return 0;
}

/*****
    END OF FILE
**********/


