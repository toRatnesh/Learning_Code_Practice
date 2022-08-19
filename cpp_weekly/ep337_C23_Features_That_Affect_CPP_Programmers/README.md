/******************
  This example demonstrates about C23 features that affect C++ programmers

  For more info visit:
https://www.youtube.com/watch?v=jOFrKN54M5g&list=PLs3KjaCtOwSZ2tbuV1hx8Xz-rFZTan2J1&index=340

 ********************/

/********
  1.  New preprocessor directives #embed
  This will embed the file directly into source file
 ********/
#embed </path/to/file>


/*********
  2.  constexpr

  C23 allows constexpr variable
  Although constexpr function is still not supported
 *********/

constexpr int fun() {
	// this funciton is not allowed
	return 42;
}
constexpr int val = 56;

/*********
  3.  [[attributes]]
  C23 added follwing attributes
Reference: https://en.cppreference.com/w/c/language/attributes

[[deprecated]]
[[fallthrough]]
[[maybe_unused]]
[[nodiscard]]
[[noreturn]]
 *********/

/*********
  4.  unnamed parameters in function definition
Reference: https://en.cppreference.com/w/c/language/function_definition
 *********/
void unnamed_param_fun(int ) {

}

/*********
  5.  typed enumaration
 *********/

enum Myenum : int {
	X,
	Y,
	Z
};

/*********
  6.  __has_include
 *********/
#if __has_include("somefile")
#include ("somefile");
#endif

/******
  END OF FILE
 *******/
