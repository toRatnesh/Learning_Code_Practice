/*****
    Data types used by Impl
**********/

#ifndef DATA_HPP
#define DATA_HPP

#include <iostream>

class St {
    int     val;
    public:
    
    ~St()   { std::cout << "~St()\n"; }
    St()   { std::cout << "St()\n"; }
    explicit St(const int ival) : val(ival) { std::cout << "St(const int ival)\n"; }
    
    St(const St & other) : val(other.val) { 
        std::cout << "St(const St & other)\n"; 
    }
    St & operator=(const St & other) { 
        std::cout << "operator=(const St & other)\n"; 

        if(this != &other) {
            val = other.val;
        }
        return *this;
    }

    St(St && other) : val(std::move(other.val)) { 
        std::cout << "St(St && other)\n"; 
    }
    St & operator=(St && other) { 
        std::cout << "operator=(St && other)\n"; 

        if(this != &other) {
            val = std::move(other.val);
        }
        return *this;
    }    

};


#endif

/*****
    END OF FILE
**********/

