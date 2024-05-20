
/*****

    References:
    episode : https://www.youtube.com/watch?v=AFRSr54GsL4

    This example demonstrates about issue with default parameter value in 
    virtual member function
    When compiler replaces missign argument during function call 
    it checks the type of object and replaces the default constructor from that class

**********/

#include <iostream>
#include <memory>

class Bird {
    public:
    virtual ~Bird() = default;
    virtual void fly(const bool flag = true) = 0;
};

class Ostriches : public Bird {
    public:
    virtual void fly(const bool flag) override {
        if(flag) {
            std::cout << "Ostriches can fly\n";
        } else {
            std::cout << "Ostriches can not fly\n";
        }
    }
};

class Falcon : public Bird {
    public:
    virtual void fly(const bool flag = false) override {
        if(flag) {
            std::cout << "Falcon can fly\n";
        } else {
            std::cout << "Falcon can not fly\n";
        }
    }
};

int main() {
    {
        std::unique_ptr<Bird> obird1 = std::make_unique<Ostriches>();
        obird1->fly();

        Ostriches obird2;
        //obird2.fly();       // CE
    }

    {
        std::unique_ptr<Bird> fbird1 = std::make_unique<Falcon>();
        fbird1->fly();

        Falcon fbird2;
        fbird2.fly();
    }

    return 0;
}

/*****
    END OF FILE
**********/

