
/*****

    This example demonstrates about advantage of making assignment operators lvalue only 
    to stop assignment to temporary values

    For more info visit
    episode: https://www.youtube.com/watch?v=l7353tlBeaI

**********/

#include <iostream>
#include <string>

class MyData {
    std::string     data;

    public:
    MyData() = default;
    MyData(const std::string & data) : data(data) { }

    MyData& operator=(const MyData & data) & = default;
};

class S {
    MyData  data;

    public:
    MyData  at()        {   return data; }
    MyData& ref_at()    {   return data; }
};

int main() {

    { 
        S sobj;

        MyData & dref   = sobj.ref_at();
        dref            = MyData();

        sobj.ref_at()   = MyData();
    }

    { 
        S sobj;

        //MyData & dref   = sobj.at();
        //dref            = MyData();

        //sobj.at()       = MyData();
    }

    return 0;
}

/*****
    END OF FILE
**********/

