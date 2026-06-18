
10 Coroutines with Boost.Cobalt
=================================


Boost.Cobalt is fully compatible with Boost.Asio, allowing you to seamlessly combine both libraries in your projects

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


# References

https://www.boost.org/doc/libs/latest/libs/cobalt/doc/html/index.html

Asynchronous Programming with C++ | Javier Reguera-Salgado & Juan Antonio Rufes

