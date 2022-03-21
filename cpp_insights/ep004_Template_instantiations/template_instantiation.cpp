/**********
  This example demonstrates about template instantiation

  For more info visit:
https://en.cppreference.com/w/cpp/language/templates

C++ Insights - Episode 22: extern template | https://www.youtube.com/watch?v=cbQVxikWfmw
Back to Basics: Compiling and Linking - Ben Saks - CppCon 2021 |
https://www.youtube.com/watch?v=cpkDQaYttR4&list=PLHTh1InhhwT4TJaHBVWzvBOYhp27UO7mI&index=13&t=2520s

 *******/


template<typename T> 
void fun(T t) { }

struct St {};

int main() {
    fun(St());  // this will instatiate definition of fun for struct St type
    return 0;
}

/*****
  END OF FILE
 ******/
