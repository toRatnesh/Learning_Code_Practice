/******************
  This example demonstates about 'extern template' which is used to instantiate a templte.

  Normally a template definition is instantiated when we declare a object and call any function associted with that object.
  With the help of 'extern template' we can instantiate a template declaration only or definition even when we do not call that funtion.

  For more info visit:
  C++ Insights - Episode 22: extern template | https://www.youtube.com/watch?v=cbQVxikWfmw
  Back to Basics: Compiling and Linking - Ben Saks - CppCon 2021 | 
https://www.youtube.com/watch?v=cpkDQaYttR4&list=PLHTh1InhhwT4TJaHBVWzvBOYhp27UO7mI&index=13&t=2520s

 ***********************/


template<typename T>
class test1 {
    T m;
    public:
    void set(T val) { m = val; };
    T get() { return m; }
};


template<typename T>
class test2 {
    T m;
    public:
    void set(T val) { m = val; };
    T get() { return m; }
};

extern template
class test2<int>;   // this will instantiate template declaration only

template<typename T>
class test3 {
    T m;
    public:
    void set(T val) { m = val;};
    T get() { return m; }
};

template
class test3<int>;   // this will instantiate template defintion for int

int main() {
    test1<double> t1;   // this will instantiate template declartion only
    t1.set(3.5); // this will instantiate template definition of set only, since get is not used anywhere it will not be defined

    return 0;
}


/*******
  END OF FILE
 ********/
