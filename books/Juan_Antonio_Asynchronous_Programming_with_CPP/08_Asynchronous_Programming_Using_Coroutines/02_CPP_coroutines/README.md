# C++ coroutines
	
A coroutine is a function that can suspend itself.

Coroutines in C++ are stackless.

This means that the state we need to store to be able to suspend/resume the coroutine is stored in the heap.

## New keywords

co_yield, co_await, and co_return

If a function uses at least one of those three keywords, then the compiler knows it is a coroutine.

| Keyword   | Input/Output  | Coroutine State |
|-----------|----------------|------------|
| co_yield    | Output    | Suspended |
| co_await  | Input | Suspended |
| co_return | Output | Terminated |


##  Coroutines restrictions

- a variable number of arguments using varargs can’t be coroutines	X
- constructor or destructor cannot be a coroutine						X
- constexpr and consteval functions cannot be coroutines				X
- function returning auto cannot be a coroutine						X
- The main() function cannot be a coroutine							X
- a variadic function template can be a coroutine								✓
- a function returning auto with a trailing return type can be a coroutine	✓
- Lambdas can be coroutines													✓

