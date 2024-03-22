/*****

    This example demonstrates about danger of using pointer arithmetic and why to avoid them

    Alternative Use:
    std::span
    std::string_view

    For more info visit:
    episode https://www.youtube.com/watch?v=MsujPM2wDmk

**********/

#include <iostream>
#include <string>
#include <span>

struct Data {
    int             ival;
    std::string     sval;
};

void display_data(const Data & data) {
    std::cout << data.ival << ", " << data.sval << '\n';
}

void dangerous_use_of_pointer(Data * data) {

    display_data(*data);
    display_data(*(data+1));
    
    //display_data(*(data+2));  // unsafe because there is no data at that index

    return;
}

void use_of_span(std::span<Data> data) {
    // can iterate when using span
    for(const auto & elem : data) {
       display_data(elem); 
    }
    return;
}

int main() {

    Data data[2] = {{1, "sample string-1"}, 
                    {2, "sample string-2"}};

    std::cout << "Using pointer\n";
    dangerous_use_of_pointer(data);

    std::cout << "Using span\n";
    use_of_span(data);

    return 0;
}

/*****
    END OF FILE
**********/


