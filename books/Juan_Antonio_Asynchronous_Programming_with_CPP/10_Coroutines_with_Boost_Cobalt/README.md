
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

# Boost.Cobalt generators

They are the **only coroutine type that can yield values.**

Boost.Cobalt generators is that they are **eager by default**

Boost.Cobalt generators are asynchronous, allowing them to use co_await

std::generator is lazy and doesn’t support co_await


cobalt::generator is a struct template:

```
template<typename Yield, typename Push = void>
struct generator { ... };
```

- Yield: The generated object type
- Push: The input parameter type (defaults to void)

Boost.Cobalt generators are eager, but it is possible to make them wait (co_await) as soon as they start executing. Using following:

```
auto x = co_await boost::cobalt::this_coro::initial;
```

This makes the generator wait for the first pushed value. This behaves as a lazy generator (in
fact, it starts executing immediately because the generator is eager, but the first thing it does
is wait for an input value).

**Boost.Cobalt co_main:**

Boost.Cobalt introduces a coroutine-based entry point called co_main.

Boost.Cobalt implements the required main function internally.

Using co_main will let you implement the main function (entry point) of your program as a coroutine, thus being able to call co_await and co_return. 

**Remember from Chapter 8 that the main function cannot be a coroutine.**


# Boost.Cobalt tasks and promises

Boost.Cobalt promises are eager coroutines that return one value and Boost.Cobalt tasks are the lazy version of promises

We can call a promise repeatedly to get more than one value, but the state won’t be kept between calls (as in generators).

Basically, a promise is a coroutine that can use co_await (it can use co_return too).

Tasks are lazy and start suspended and only resume executing when the
caller calls co_await on them

# Boost.Cobalt channels

Channels provide a way for coroutines to communicate asynchronously, allowing data transfer between a producer and a consumer coroutine in a safe and efficient manner

Allows communication through message passing, promoting a share-memory-by-communicating paradigm

A channel is a mechanism through which values are asynchronously passed from one coroutine (the producer) to another (the consumer)

This communication is non-blocking

Let’s clarify this: both reading and writing operations may be blocking, depending on the buffer size if, by blocking, we mean coroutines are suspended, but on the other hand, from the point of view of threads, these operations don’t block the thread.

If the buffer size is zero, a read and a write will need to occur at the same time and act as a rendezvous (synchronous communication).

If the channel size is bigger than zero and the buffer is not full, the write operation will not suspend the coroutine. Likewise, if the buffer is not empty, the read operation will not suspend.

**Boost.Cobalt channels are strongly typed. A channel is defined for a specific type, and only that type can be sent through it.**


# Boost.Cobalt synchronization functions

Boost.Cobalt has mechanisms that allow us to wait on more than one coroutine. These mechanisms are called synchronization functions.

**1. race:** waits for one coroutine out of a set to complete, but it does so in a pseudo-random manner

**2. join:** waits for all the coroutines in a given set to complete and return their results as values

If any of the coroutines throws an exception, join will propagate the exception to the caller

**3. gather:** waits for a set of coroutines to complete, but it handles exceptions differently

Instead of throwing an exception immediately when one of the coroutines fails, gather captures each coroutine’s result individually


**4. left_race:** left_race function is like race but with deterministic behavior

It evaluates the coroutines from left to right and waits for the first coroutine to become ready

In the case of the gather function, the result for each coroutine will either be an error (absent value) or a value. join returns a tuple of values or throws an exception; gather returns a tuple of optional values that have no value in the event of an exception (the optional variables are not initialized).

The gather function returns a tuple of optional values, and we need to check whether each coroutine returned a value or not (the optional has a value or not).

# References

https://www.boost.org/doc/libs/latest/libs/cobalt/doc/html/index.html

Asynchronous Programming with C++ | Javier Reguera-Salgado & Juan Antonio Rufes

