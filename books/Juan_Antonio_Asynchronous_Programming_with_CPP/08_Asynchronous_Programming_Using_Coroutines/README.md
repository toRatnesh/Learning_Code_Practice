Coroutines are a mechanism that allows us, among other things, to perform multiple tasks in a single thread.
	
# Coroutines
		
A coroutine is a function that can suspend itself.

Coroutines suspend themselves while waiting for an input value (while they are suspended, they don’t execute)

or after yielding a value such as the result of a computation. 

Once the input value is available or the caller requests another value, the coroutine resumes execution.
	
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


# Implementing basic coroutines

## The simplest coroutine

The simplest coroutine that just returns

The promise type:

    The promise type is required by the compiler.

    We need to always have this type defined (it can be either a class or a struct), *it must be named promise_type*, and it must implement some functions specified in the C++ reference.

    The promise type must be defined inside the type returned by the coroutine

    It has nothing to do with std::promise

## A yielding coroutine

A coroutine that can send data back to the caller.

A communication channel from the coroutine to the caller is established through the coroutine’s promise type and handle, which manages the state of the coroutine.

Coroutine frame:

    When a coroutine is called, it creates a coroutine frame, which contains all the state information needed to suspend and resume its execution.

Promise type:

    Each coroutine has an associated promise type, which is responsible for managing the coroutine’s interaction with the caller functions.
    
    The promise is where the coroutine’s return value is stored, and it provides functions to control the coroutine’s behavior.

Coroutine handle:

    The coroutine handle is a type that gives access to the coroutine frame (the coroutine’s internal state) and allows the caller to resume or destroy the coroutine.

    The handle is what the caller can use to resume the coroutine after it has been suspended.

    The handle can also be used to check whether the coroutine is done or to clean up its resources.

Suspend and resume mechanism:

    When a coroutine yields a value (co_yield) or awaits an asynchronous operation (co_await), it suspends its execution, saving its state in the coroutine frame.


When the compiler reads the co_yield expression, it will generate a call to the yield_value
function defined in the promise type.

The handle type:

    a way to refer to a suspended or executing coroutine

    Its type is std::coroutine_handle and it’s a member variable of the return type.

## A waiting coroutine

The coroutine “waits,” we mean it is suspended (that is, not executing) until the data is received.

When the coroutine calls co_await, the compiler will generate code to call a function in the promise object called await_transform, which has a parameter of the same type as the data the coroutine is waiting for.

await_transform is a function that transforms any object (in our example, std::string) into an awaitable object. std::string is not awaitable, hence the previous compiler error.

await_transform must return an awaiter object

The promise_type function await_transform is required by the compiler.
We cannot use a different identifier for this function.

The parameter type must be the same as the object the coroutine is waiting for.
The awaiter struct can be named with any name.

- await_ready: This is called to check whether the coroutine is suspended. If that is the
case, it returns false.

- await_resume: This resumes the coroutine and generates the result of the co_await expression.

- await_suspend: In our simple awaiter, this returns void, meaning the control is passed
to the caller and the coroutine is suspended.

It’s also possible for await_suspend to return a Boolean.

Returning true in this case is like returning void.

Returning false means the coroutine is resumed.

# Coroutine generators

A generator is a coroutine that generates a sequence of elements by repeatedly resuming itself from the point that it was suspended.

## Fibonacci sequence generator

Write a generator and use to implement a coroutine function which returns numbers in fibonacci sequence

## C++23 std::generator

C++23 introduced the std::generator template class.

By using it, we can write coroutine-based generators without writing any of the required code, such as the promise type, the return type, and all their functions.

# Simple coroutine string parser

Write an example code which returns a number corresponding to a string of digits which terminates with '#'

## The parsing algorithm

Implement above string parser using a simple example

## The parsing coroutine

Implement above string parser using a coroutine

# Coroutines and exceptions
			
if the exception is thrown before the coroutine is executed, the code creating the coroutine must handle the exception,

if the exception is thrown when the coroutine is executed, then unhandled_exception() is called.

There are different strategies to handle such exceptions.

- Rethrow the exception so we can handle it outside the promise type (that is, in our code).
- Terminate the program (for example, calling std::terminate).
- Leave the function empty. In this case, the coroutine will crash and it will very likely crash the program too.

# References

Asynchronous Programming with C++ | Juan Antonio Rufes

https://en.cppreference.com/cpp/coroutine
https://en.cppreference.com/cpp/language/coroutines
https://en.cppreference.com/cpp/coroutine/generator

https://github.com/toRatnesh/Learning_Code_Practice/tree/main/booksAndreas_Fertig-Programming_with_CPP20/ch02_Coroutines_Suspending_functions
	
