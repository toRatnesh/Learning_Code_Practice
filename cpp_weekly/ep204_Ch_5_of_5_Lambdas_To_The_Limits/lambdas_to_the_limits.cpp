/*********************
  This exmaple demonstrates about the concept of lamda and its usage

// Chapter 5: Lambdas To The Limits

126: Lambdas With Destructors https://www.youtube.com/watch?v=9L9uSHrJA08
162: Recursive Lambdas https://www.youtube.com/watch?v=M_Mrk1xHMoo
89: Overusing Lambdas https://www.youtube.com/watch?v=OmKMNQFx_8Y
177: `std::bind_front` with Lambdas https://www.youtube.com/watch?v=fLeHy7s1WIo

1: List the C++ features that lambdas take advantage of
Ans:
struct/classes
value / reference semantics
constexpr 
inline 
mutable 
auto 
constrating auto
const member funnctin
template
template funcitons
concept
function pointer
callable
return type deductions 
trailing retutn type
operator overloading


2: What is the type of a lambda?
unknown (lambda can not be named)   // c++ weekly episode 249

3: Do lambda objects follow normal lifetime rules?
yes
captures are destroyed when lamda goes out of scope

4: How do lambdas help us write efficient code?
lambdas generate eficient code considering RVO technique

5: How is it possible to overuse lambdas?
lambad inside  templates (because each instantialtion of template will generate identical code for the lambda causing code bloat)

 ***********************/

/******
  END OF FILE
 *****/
