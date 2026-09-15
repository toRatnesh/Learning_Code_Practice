# 6. Writing Smart Pointers


# Ownership semantics


unique_ptr\<T>

- Ownership semantics: Single ownership.
- Notable special member functions: Non-copyable. The destructor is responsible for destroying the pointee

shared_ptr\<T>

- Ownership semantics: Shared ownership.
- Notable special member functions: Copying, assigning, and destroying update a shared use count. The destructor of the last co-owner is responsible for destroying both the pointee and the use count.

T*

- Ownership semantics: No ownership is defined in the type system (ownership rules have to be inscribed in user code).
- Notable special member functions: Not applicable (this is a fundamental type).




# Writing your own (naïve) unique_ptr

## Type signature

```cpp
template<class T, class Deleter = std::default_delete<T>> 
class unique_ptr;                   // (1)	(since C++11)   for scalar type

template <class T, class Deleter> 
class unique_ptr<T[], Deleter>;     // (2)	(since C++11)   for array type
```

The next step will be to choose the form of unique_ptr<T,D>. We will expect most deleters to be stateless and use empty base optimization (EBO) to our advantage by deriving from our deleter type.

## Special member functions

The code for the special member functions will be the same for both the scalar and the array forms of unique_ptr.

- copy  ✗
- move  ✓

both the general case and the array case,
operator bool() (true only if the object does not model a null pointer), 
empty() (true only if the object does model a null pointer),
operator==() and operator!=()

get() in both its const and non-const versions in order to expose the underlying pointer

## Pointer-like functions

For pointer-to-scalar, we will want to implement operator*() and operator->()  

```
The operator->() member function is a strange beast: when used on an object, it will be reinvoked on the returned object (and again on that returned object, and so on) until something returns a raw pointer, at which point the compiler will know what to do. It’s a very powerful mechanism.
```

```
C++23 introduces the “deduced this” mechanism that allows one to explicitly mark the first argument of a member function with the this keyword. Doing so and combining it with a forwarding reference (the U&& type) lets the compiler deduce the const-ness (or lack thereof) of this, in effect, expressing both the const and non-const versions in a single function.
```



# Writing your own (naïve) shared_ptr

A shared_ptr\<T> type is a difficult beast to implement and a harder beast yet to optimize.

```cpp
template< class T > 
class shared_ptr;
```

The main difficulty when writing a shared_ptr is that it’s a type with two responsibilities: it co-owns both the pointee and the usage counter, requiring some measure of care, especially with respect to exception safety.

Note that our shared counter is a pointer to an atomic integral since shared_ptr\<T> is particularly relevant in multithreaded cases where one does not know which of the threads will be the last user of the object.

- By default, we will define shared_ptr\<T> to be empty, thus conceptually equivalent to a null pointer. 

- constructor of shared_ptr\<T> that takes T* as an argument represents the act of taking ownership of the pointee. For that reason, if an exception is thrown when allocating the counter, that pointee is destroyed.

- **copy constructor** will represent sharing ownership of the pointee, making sure to consider the case where the source object models a null pointer.

- **move constructor** models the transfer of ownership. As is often the case for move operations, it’s very fast and it shows highly predictable behavior.

- **copy assignment** models the act of releasing control of the currently held resource and sharing the resource of its argument

- **move assignment** models the act of releasing control of the currently held resource and transferring control of the resource held by the argument to the assigned-to object

- **Destruction** make sure that the last owner of the pointee destroys it, to avoid immortal objects. The key point is that shared_ptr\<T> should only destroy the pointed-to T object if it was the last user of that object.


Other member functions

- operator== and operator!=
- operator*() and operator->()
- get()

## A few words on make_shared()

Why make_shared()?

make_shared\<T>(), this factory function is responsible for allocating both the T object and the counter, perfectly forwarding the arguments received by the function to the T constructor

Since the same function performs both allocations, it can fuse them in a single allocation of a memory block that contains both the T object and the counter, putting them both on the **same cache line**





# Writing a policy-based duplicating pointer

Suppose, we want single ownership semantics but, unlike std::unique_ptr\<T>, which is movable but noncopyable, we want duplication of the pointer to lead to duplication of the pointee. What can we do?

there are two expected cases:
1. copying an object of a nonpolymorphic type
2. copying an object of a polymorphic type

The customary way to duplicate an object of a polymorphic type is through subjective duplication, otherwise known as **cloning**. Expressed informally, when one holds a pointer to an object with at least one virtual member function, the only entity that can really claim to know the type of the pointee is… the pointee itself.

What dup_ptr\<T> will do, then, is to pick a duplication  policy based on the characteristics of T: **by default, if T is polymorphic, then we will duplicate through cloning; otherwise, we will duplicate through copying**. Of course, we will let the client code specify a custom duplication mechanism if needed.

three approaches to this selection of a default duplication policy: 
1. an intrusive approach based on interfaces
2. a non-intrusive approach based on traits and compile-time detection of a cloning member function using C++17 features
3. non-intrusive approach based on C++20 concepts

## Detection through interfaces

One thing we could do in user code is impose that cloneable types implement a specific interface, as in this example:

```cpp
struct cloneable {
    virtual cloneable * clone() const = 0;
    virtual ~cloneable() = default;
};
```

Such a solution is probably not standardization-worthy: it is intrusive, imposes some overhead (we are assuming that cloneable types will be polymorphic types, something that is likely but not mandatory), and so on.


```cpp
// ... type cloneable
struct Copier {
    template <class T>
    T* operator()(const T* p) const {
        return new T{*p};
    }
};

struct Cloner {
    template <class T>
    T* operator()(const T* p) const {
        return p->clone();
    }
};

template <class T, class Dup = std::conditional_t<
                       std::is_base_of_v<cloneable, T>, Cloner, Copier>>
class dup_ptr;
```

Check example

## Detection through traits

we can use type traits to detect the presence of a const-qualified clone() member function and suppose this is a reasonable claim that cloning is a better choice than copying.

```cpp
// types Cloner and Copier (see above)
template <class, class = void>
struct has_clone : std::false_type {};


// THIS SPECIALIZATION DOES NOT WORK FOR A TYPE WHICH
// DOES NOT IMPLEMENT CONST MEMBER FUNCTION
// COMPILER WILL DISCARD IT RATHER THAN TREATING IT AS A COMILATION ERROR
template <class T>
struct has_clone<T, std::void_t<decltype(std::declval<const T*>()->clone())>>
    : std::true_type {};

template <class T>
constexpr bool has_clone_v = has_clone<T>::value;

template <class T,
          class Dup = std::conditional_t<has_clone_v<T>, Cloner, Copier>>
class dup_ptr;
```

```
The advantage of this implementation over the previous one is that this one checks for the existence of a suitably written clone() member function, whereas the previous one checks for the existence of a specific base class. Implementing a function is a lighter contract than deriving from a specific base class.
```

## Detection through concepts

Through concepts, we can define a cloneable type, T, to be something for which a call to clone() is well-formed on const T* and yields something that is convertible to T*.

```cpp
template <class T>
concept cloneable = requires(const T* p) {
    { p->clone() } -> std::convertible_to<T*>;
};

template <class T, class Dup = 
    std::conditional_t<cloneable<T>, Cloner, Copier>>
class dup_ptr;
```

```
C++26 will contain two standard types named std::indirect and std::polymorphic that will cover a niche close to the one described by this dup_ptr. It was voted in on February 15 2025.
```

# Some not-so-smart yet useful smart pointers

## A non_null_ptr type

Using this type, any function that accepts a non_null_ptr\<T> argument knows that the T* pointer therein will be non-null, relieving client code from the burden of validation.

This makes non_null_ptr\<T> a beautiful type for the interface of functions that expect a non-null T*.

The two main advantages of non_null_ptr\<T> over T* in this case are that

1. The type system documents the intent better with non_null_ptr\<T> (with T*, a null pointer might be fine, but with non_null_ptr\<T>, it is clearly not)

2. The called functions can proceed without validating, the validation being (again) ingrained in the type system. Using a richer type than T* makes both caller code and called code better.

## An observer_ptr type

Operations that would apply to a raw pointer are restricted on that type. 

The canonical issue is that applying delete on T* would work but applying delete on observer_ptr\<T> would not since observer_ptr\<T> is… not a pointer.

usage of T* and of observer_ptr<T> should be mostly equivalent in user code; the only difference is in misguided uses such as applying delete or performing pointer arithmetic



# References

C++ Memory Management | Patrice Roy

https://en.cppreference.com/cpp/memory/unique_ptr
https://en.cppreference.com/cpp/memory/shared_ptr
https://en.cppreference.com/cpp/memory/weak_ptr
https://en.cppreference.com/cpp/header/memory


