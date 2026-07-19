/*****

References

	episode https://www.youtube.com/watch?v=rKiLxJuEjDY
    Member functions with ref-qualifier | https://en.cppreference.com/cpp/language/member_functions
    https://www.learncpp.com/cpp-tutorial/ref-qualifiers/

    code https://godbolt.org/z/761bvjaKG

    a ref-qualifier allows us to overload a member function based on whether it is being called on an lvalue or an rvalue implicit object
    Using this feature, we can create two versions of member function -- one for the case where our implicit object is an lvalue, 
    and one for the case where our implicit object is an rvalue.

**********/

#include <iostream>
#include <string>


class Data {
    std::string     data;

    public:
    Data(const std::string & data) : data{data} { 
        std::cout << "Data constructor\n";
    }

    ~Data() {
        std::cout << "Data destructor\n";
    }

    //const std::string & get() const {
    //    return data;
    //}

    const std::string & get() const & {
        return data;
    }

    std::string get() && {
        return std::move(data);
    }        
};


int main() {

    {
        Data data{"This is some large data which will be stored on heap"};
        const std::string & l_data = data.get();
        std::cout << l_data << '\n';
    }
    std::cout << '\n';

    {
        // warning: possibly dangling reference to a temporary [-Wdangling-reference]
        const std::string & l_data = Data{"This is some large data which will be stored on heap"}.get();
        std::cout << l_data << '\n';
    }

    return 0;
}

/*****
    END OF FILE
**********/

