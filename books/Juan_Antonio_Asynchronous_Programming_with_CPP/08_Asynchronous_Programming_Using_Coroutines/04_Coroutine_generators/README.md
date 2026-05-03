# Coroutine generators

A generator is a coroutine that generates a sequence of elements by repeatedly resuming itself from the point that it was suspended.

## Fibonacci sequence generator

Write a generator and use to implement a coroutine function which returns numbers in fibonacci sequence

## C++23 std::generator

C++23 introduced the std::generator template class.

By using it, we can write coroutine-based generators without writing any of the required code, such as the promise type, the return type, and all their functions.
