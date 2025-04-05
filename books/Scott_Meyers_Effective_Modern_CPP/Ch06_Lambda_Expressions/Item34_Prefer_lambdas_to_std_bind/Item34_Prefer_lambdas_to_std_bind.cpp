/*********

References
    Effective Modern C++ | Scott Meyers

Item 34: Prefer lambdas to std::bind
    Lambdas are more readable, more expressive, and may be more efficient than using std::bind.
    In C++11 only, std::bind may be useful for implementing move capture or for binding objects with templatized function call operators.
    In C++14, there are no reasonable use cases for std::bind.

**********/

#include <iostream>
#include <memory>
#include <functional>

struct St{
    int m;
    void display() { std::clog << "value is " << m << '\n'; }
};

struct St_template{
    int m;
    template<typename T>
    void operator()(const T & parm) const {
        std::clog << "template value is "<< parm << "\n";
    }
};

void cpp11_need_of_bind() {
    std::clog << "=== Lambda and bind in CPP-11 : Need of bind in CPP-11\n";
    auto up = std::unique_ptr<St>(new St{5});
    // there is no way to capture up pointer using move inside lambda
    auto lambda = [](std::unique_ptr<St> && up){ up->display(); };
    lambda(std::move(up));

    // we may move it inside bind
    auto bind_1 = std::bind([](const std::unique_ptr<St> & st_up){ st_up->display(); }, std::move(up));
    bind_1(); // we are not passing pointer as argument when calling bind object

    St_template st{7};
    // CPP-11 lambda offers no way to call templated operator()
    //auto lambda_2 = [st](const St_template & parm){ st(parm); };

    auto bind_2 = std::bind(st, std::placeholders::_1);
    bind_2(7);
    bind_2(6.9);
    bind_2("sample string");

    return ;
}

void cpp14_no_need_of_bind() {
    std::clog << "=== Lambda and bind in CPP-14 : No need of bind in CPP-14 \n";
    auto up = std::unique_ptr<St>(new St{5});
    auto lambda = [up = std::move(up)](){ up->display();};
    lambda();

    // no need of bind in CPP-14
    //auto bind_1 = std::bind([](const std::unique_ptr<St> & st_up){ st_up->display(); }, std::move(up));
    //bind_1();

    St_template st{7};
    auto lambda_2 = [st](const auto & parm){ st(parm); };
    lambda_2(7);
    lambda_2(6.9);
    lambda_2("sample string");

    /*  no need of bind in CPP-14
    auto bind_2 = std::bind(st, std::placeholders::_1);
    bind_2(7);
    bind_2(6.9);
    bind_2("sample string");
    */

    return ;
}

int main() {
    cpp11_need_of_bind();
    cpp14_no_need_of_bind();
    return 0;
}

/***********
    END OF FILE
*************/


