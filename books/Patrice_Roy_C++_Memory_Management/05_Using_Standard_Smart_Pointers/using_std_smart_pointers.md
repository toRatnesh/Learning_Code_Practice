
# 5. Using Standard Smart Pointers

# The standard smart pointers

raw pointers do not provide clear ownership information has been a recurring source of bugs in C++ over the years

**use std::unique_ptr** where there is a clearly identified last owner of a pointed-to object, regardless of whether the pointee is shared or not between pointers

**use std::shared_ptr** where the pointed-to object is shared by at least two “co-owners” and the order in which these owners will be destroyed is a priori unknown

## On the exposition of intent through function signatures

function signatures convey meaning, and it’s important to use the types that convey our intent





# Type unique_ptr

```cpp
template<class T, class Deleter = std::default_delete<T>> 
class unique_ptr;

template <class T, class Deleter>
class unique_ptr<T[], Deleter>;
```

unique_ptr\<T> object represents sole (unique) ownership of a pointed-to object



```cpp
void possible_mutation(unique_ptr<X> &);
void possible_mutation(X *);    // better choice

void consult(const unique_ptr<X> &);
void consult(const X *);        // better choice
```

## Handling objects

- copy operations  ✗
- move operations  ✓

a moved-from unique_ptr\<T> behaves like a null pointer

A unique_ptr\<T> offers most of the same operations as T*

- operator*()
- operator->()
- ==
- !=

**You cannot do pointer arithmetic on unique_ptr\<T>**

If you need to do pointer arithmetic, it’s always possible to get to the raw pointer owned by a unique_pointer<T> through its get() member function.

```
sizeof(unique_ptr<T>)==sizeof(T*)
```

## Handling arrays

unique_ptr offers a specialization to handle arrays

```cpp
template <class T, class Deleter>
class unique_ptr<T[], Deleter>;
```

you will end up having to track the size yourself, separately from the actual array, since unique_ptr does no such tracking.

alternatively you may use std::array or std::vector

```
sizeof(unique_ptr<T[]>) == sizeof(T*)
```

## Custom deleters

There are indeed many situations where applying operator delete on a pointer to destroy the pointed-to object is not an option:
- Sometimes, T::~T() is private or protected, making it inaccessible to other classes such as unique_ptr\<T>.
- Sometimes, the finalization semantics require doing something else than calling delete – for example, calling a destroy() or release() member function
- Sometimes, the expectation is to call a free function that will perform auxiliary work in addition to freeing a resource.

unique_ptr\<T> can take a custom deleter that will perform those custom resource deallocation tasks. 

A **custom deleter can be a functor or a function** that will be applied to the T* stored within unique_ptr\<T> when the destructor of that smart pointer is called

```
The D parameter in the unique_ptr<T,D> signature is expected to be stateless, as it’s not stored within the unique_ptr object but instantiated as needed, and then it’s used as a function that takes the pointer and does whatever is required to finalize the pointee.
```

use class with a private destructor, a common technique if you seek to prevent instantiation through other means than dynamic allocation (you cannot use an automatic or a static object of that type, since it cannot be implicitly destroyed)

**specialization of unique_ptr with a function pointer as a deleter leads to a slight size increase** as we will need to pass the function pointer as an argument to the constructor, since that pointer will be stored within

If the extra cost of a function pointer’s size (plus alignment) in the size of unique_ptr is unacceptable, there’s a neat trick you can play by pushing the runtime use of the deleter function into the wonderful world of the type system

```cpp
auto p =    unique_ptr<important_resource, 
                void (*)(releasable*)> {
                    new important_resource, release
            };  // ok, will use release() to delete pointee

static_assert(sizeof(p) > sizeof(void*));

auto q  =   unique_ptr<important_resource, 
                decltype([] (auto p) { release(p); })> { 
                    new important_resource 
            };

static_assert(sizeof(q) == sizeof(void*));

```

## make_unique

make_unique\<T>() – with a factory function, client code never finds itself with “floating results from calls to new”; it either has a complete unique_ptr\<T> object or not

make_unique\<T>() is a security feature, mostly useful to avoid exposing ownerless resources in client code

As a bonus, make_unique\<T>() allows us to limit how we repeat ourselves in source code. Check the following:

```cpp
unique_ptr<some_type> p0 { new some_type{ args } };
auto p1 = unique_ptr<some_type> { new some_type{ args } };
auto p2 = make_unique<some_type>(args);
```





# Types shared_ptr and weak_ptr

- shared ownership of the resource (mean co-owning the resource)

- copy  ✓
- copy constructor (shares the resource and increments the
counter)
- copy assignment (disconnects from the original resource, decrementing its counter, and
then connects to the new resource, incrementing its counter)

- move  ✓
- Moving from a std::shared_ptr\<T> transfers ownership of the resource, leaving the moved-from object into an empty state

- last co-owner of the resource is responsible for freeing it

- destructor (decrements the counter and destroys the resource if there’s no owner left)

**shared_ptr\<T> implements extrusive (non-intrusive) shared ownership semantics**

Type T could be a fundamental type and does not need to implement a particular interface for this type to work.

## Usefulness and costs

```
sizeof(shared_ptr<T>) > sizeof(unique_ptr<T>)
```

```
shared_ptr<X> p{ new X };
```

An instruction such as this one will lead to two allocations, not one – there will be one for the X object and another one (performed internally by the shared_ptr) for the counter. Since these two allocations will be done separately, one by the client code and one by the constructor itself, the two allocated objects might find themselves in distinct cache lines, potentially leading to a loss of efficiency when accessing the shared_ptr object.


## make_shared()


```
shared_ptr<X> p{ new X(args) }; // two allocations
auto q = make_shared<X>(args);  // single allocations, more cache friendly
```

make_shared\<X>(args) specifies the type X to construct along with the arguments args to forward directly to the constructor

q will perform better than p, as its two key components will be organized in a more cache-friendly manner

## What about weak_ptr?

The role of weak_ptr\<T> is to model the temporary ownership of T.

Type weak_ptr\<T> is meant to interact with shared_ptr\<T> in a way that makes the continued existence of the pointee testable from client code.

weak_ptr does not own the resource until you call lock() on it

**In practice, weak_ptr is sometimes used to break cycles when shared_ptr objects refer to each other in
some way.**




# When to use raw pointers

1. for a function, being passed a T* as an argument should mean the function is an observer, not an owner, of that T.

2. you can use a raw pointer inside a class that implements your preferred ownership semantics. \
What you don’t want to do is expose pointers to the internal nodes of your container to external code.

Use a smart pointer when the use case matches the semantics it models. Of course, when the relationship modeled by your pointers is neither unique ownership nor shared ownership, you probably do not want smart pointer types that provide these semantics, resorting instead to either nonstandard and non-owning smart pointers or, simply, raw pointers.

You often need raw pointers to use lower-level interfaces – for example, when performing system calls.

And if you have no other choice, use raw pointers.




# References

C++ Memory Management | Patrice Roy

https://en.cppreference.com/cpp/memory/unique_ptr
https://en.cppreference.com/cpp/memory/shared_ptr
https://en.cppreference.com/cpp/memory/weak_ptr
https://en.cppreference.com/cpp/header/memory


