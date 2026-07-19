/*****

References

	episode https://www.youtube.com/watch?v=d7CzCSrPp60

    code https://godbolt.org/z/GoxdqWsz5

    not marking move constructor as noexcept will result into move operation on container  falling back to copy 
    if move operation is marked as noexcept it will perform move operation in container because in that case it is guranteed for opeartion to succeed
    if exception is thrown in this case terminate will be called

**********/

#include <iostream>
#include <string>
#include <vector>

class Data {
    std::string     data;

    public:
    Data(const std::string & data) : data{data} { 
        std::cout << "Data constructor\n";
    }

    ~Data() {
        std::cout << "Data destructor\n";
    }

    Data(const Data & other) : data{other.data} {
        std::cout << "Data copy constructor\n";
    }

    Data & operator=(const Data & other) {
        
        std::cout << "Data copy assignment\n";

        if(&other != this) {
            data = other.data;
        }
        return *this;
        
    }


    Data(Data && other) noexcept : data{std::move(other.data)}  {
        std::cout << "Data move constructor\n";
    }

    Data & operator=(Data && other) noexcept {
        
        std::cout << "Data move assignment\n";

        if(&other != this) {
            data = std::move(other.data);
        }
        return *this;

    }

};


int main() {

    {
        std::vector<Data>   datavec;
        datavec.push_back(Data{"some large string which will not allow SSO"});

        datavec.push_back(Data{"make this throw an exception and check what happens"});
    }


    return 0;
}

/*****
    END OF FILE
**********/

