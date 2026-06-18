
10 Coroutines with Boost.Cobalt
=================================


Boost.Cobalt is fully compatible with Boost.Asio, allowing you to seamlessly combine both libraries in your projects

# Introducing the Boost.Cobalt library

writing coroutines is not an easy task due to two main reasons:
• Writing coroutines in C++ requires a certain amount of code to make the coroutine work but is not related to the functionality we want to implement.

• The development of plain C++20 coroutines requires a good knowledge of the low-level aspects of how coroutines are implemented in C++,

The goal of Boost.Cobalt is to allow us to write simple single-threaded asynchronous code using coroutines – applications that can do multiple things simultaneously in a single thread.

## Eager and lazy coroutines

**• Eager coroutines:**	begins execution as soon as it is called

The coroutine logic starts running immediately, and it progresses through its sequence until it hits a suspension point (such as co_await or co_yield)

Eager coroutines are beneficial when you want the coroutine to initiate its work immediately upon being created, such as starting asynchronous network operations or preparing data

**• Lazy coroutines:**	defers its execution until is explicitly awaited or used

The coroutine object can be created without any of its body running until the caller decides to interact with it (usually by awaiting it with co_await)

Lazy coroutines are useful when you want to set up a coroutine but delay its execution until a certain condition is met or when you need to coordinate its execution with other tasks

## Boost.Cobalt coroutine types

- Promise:  eager coroutine

It is used to implement asynchronous operations that return a single value (calling co_return)

- Task: lazy version of the promise

It will not begin execution until is explicitly awaited

When awaited, the task starts execution, allowing for delayed processing of asynchronous operations

- Generator:  eager coroutine

In Boost.Cobalt, a generator is the **only type of coroutine that can yield values**

Its functionality is like std::generator in C++23 but it allows waiting with co_await (std::generator doesn’t)

- Detached: eager coroutine

It can use co_await but not co_return values

It cannot be resumed and usually is not awaited

# References

https://www.boost.org/doc/libs/latest/libs/cobalt/doc/html/index.html

Asynchronous Programming with C++ | Javier Reguera-Salgado & Juan Antonio Rufes

