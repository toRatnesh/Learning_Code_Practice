/********
  This example demonstrates about Abbreviated Function Templates

  For more info visit:
https://en.cppreference.com/w/cpp/language/function_template
https://devblogs.microsoft.com/cppblog/abbreviated-function-templates-and-constrained-auto/
C++ Weekly episode 296 constraining auto
 *******/

constexpr auto make_it_double(auto val) {
    return (val * 2);
}

int main() {

    static_assert(4 == make_it_double(2));
    static_assert(4.8 == make_it_double(2.4));
    static_assert(6.6f == make_it_double(3.3f));

    return 0;
}

/********
  END OF FILE  
 ******/
}
}
