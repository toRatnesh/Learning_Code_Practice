/**************
    This example demonstrates about structure byte padding
    Byte padding is used to align memory for faster access of memory
    For more info visit:
    https://en.cppreference.com/w/c/language/object#Alignment
    episode: https://www.youtube.com/watch?v=hBUfBaD9038

**************/

#include <iostream>
/*
struct S1 {
  char a;
  int b;
  char c;
};
*/
// padding info of above structure S1, generated using https://cppinsights.io/
struct S1  /* size: 12, align: 4 */
{
  char a;                         /* offset: 0, size: 1
  char __padding[3];                            size: 3 */
  int b;                          /* offset: 4, size: 4 */
  char c;                         /* offset: 8, size: 1
  char __padding[3];                            size: 3 */
};

/*
struct S2 {
  char a;
  char c;
  int b;
};
*/
// padding info of above structure S2, generated using https://cppinsights.io/
struct S2  /* size: 8, align: 4 */
{
  char a;                         /* offset: 0, size: 1 */
  char c;                         /* offset: 1, size: 1
  char __padding[2];                            size: 2 */
  int b;                          /* offset: 4, size: 4 */
};


int main() {
  std::clog << "sizeof(S1) " << sizeof(S1) << '\n';
  std::clog << "sizeof(S2) " << sizeof(S2) << '\n';
  return 0;
}

/***************
    END OF FILE
*******************/
