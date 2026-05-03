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
