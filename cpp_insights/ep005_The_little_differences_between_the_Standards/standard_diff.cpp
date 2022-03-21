/********
  This example demonstrates about two differnces in standard

  1. constexpr member function is const in C++11 in later versions it's not
  2. destrcutor marked as default is constexpr in C++20

  To check differences compile this code in https://cppinsights.io/

  For more info visit:
https://www.youtube.com/watch?v=VKKNyR0RHqg
 ********/

struct Test1 {
    int m = 5;
    constexpr int fun() {   // In C++11 constexpr member function is const
        ++m;                    // this line fails to compile in C++11
        return m;
    }       
};

struct Test2 {
    ~Test2() = default;	// in C++20 default destructor is constexpr
};

struct Test3 {
    ~Test3() { };
};

int main() {
    Test1 t1{};
    return t1.fun();
}

/****
  END OF FILE
 ****/
