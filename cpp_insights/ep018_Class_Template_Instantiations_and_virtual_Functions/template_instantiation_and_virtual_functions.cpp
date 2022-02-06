/*************

  This example will demonstrates about template instantiation in case of vietual functions.

  Virtual function definition are always instantiated when an obbject of template class is created irrespective of the call to that virtual function takes place or not.

  For more info visit:
  C++ Insights - Episode 18: Class Template Instantiations and virtual Functions | https://www.youtube.com/watch?v=pm_4ea7KO94


 ******************/

template<typename T>
class test {
	T m;

	public:
	void set(T val) { m = val; };
	T get() { return m; }
	virtual T get_v() {return m; }  // virtual function defintion will be instantiated when we create an object of test even when get_v() is not called on that object

};

int main() {
	test<int> t;    // this will instatiate defintion of virtual function get_v even if it's not called ***
	return 0;
}

/*******
  END OF FILE
 *******/
