/*****

References

	episode https://www.youtube.com/watch?v=1cBOZjiC6DQ
    C++ NTTP https://en.cppreference.com/cpp/language/template_parameters

    Code https://godbolt.org/z/5z95KrPb5
    
**********/

#include <iostream>

struct Data {
    int         data;
};


template<Data data, typename T>
void useit(T value) {
    std::cout << "Data: " << data.data << ", Value: " << value << '\n';
}

template<typename T, Data data>
void display(T value) {
    std::cout << "Data: " << data.data << ", Value: " << value << '\n';
}

int main() {

    {
        const std::string sval{"C++20 NTTP: Structural Types as Template Parameters"};
        useit<Data(1)>(sval);
        useit<{2}>(sval);
        //useit<(3)>(sval);   // CE error: could not convert '3' from 'int' to 'Data'
        //useit<4>(sval);     // CE error: could not convert '4' from 'int' to 'Data'
        
    }
    std::cout << '\n';

    {
        const std::string sval{"C++20 NTTP: Structural Types as Template Parameters"};
        display<std::string, Data(1)>(sval);
        display<std::string, {2}>(sval);
        //display<std::string, (3)>(sval);   // CE error: could not convert '3' from 'int' to 'Data'
        //display<std::string, 4>(sval);     // CE error: could not convert '4' from 'int' to 'Data'
    }

    return 0;
}

/*****
    END OF FILE
**********/

