/*****

References

	episode https://www.youtube.com/watch?v=gDKKZb4qASE
    https://cppreference.com/cpp/language/function#Defaulted_functions

    code https://godbolt.org/z/56fGv3rr4

    = default default initialize data members
    When defining an object with uniform initialization {}

**********/

#include <iostream>

class Data {
    int m_data;
    //int m_data{};             // m_data is default initialized

    public:
    //Data() { }                // m_data is uninitialzed
    //Data() : m_data{} { }     // m_data is default initialized
    Data() = default;           // m_data is default initialized

    int data() const { return m_data; }
};

int main() {

    //{
    //    Data data;  // warning: 'data' may be used uninitialized
    //    return data.data();    
    //}

    {
        Data data{};
        return data.data();    
    }

    return 0;
}

/*****
    END OF FILE
**********/

