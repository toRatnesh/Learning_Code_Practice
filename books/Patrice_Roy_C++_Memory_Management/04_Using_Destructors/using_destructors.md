
# 4. Using Destructors


# On destructors: a short recap

- When an object reaches the end of its lifetime, a special member function called the destructor is called. For some class X, that member function is named X::~X()

- In a class hierarchy, when an object reaches the end of its lifetime, what happens is

    (a) the destructor for that object gets called, then the same goes for
    
    (b) the destructor of each of its non-static data member in order of declaration followed by 
    
    (c) the destructor of each of its base class sub-objects (its “parents”, informally) in order of declaration

- When explicitly destroying an object through the application of operator delete on a pointer, the resulting process involves **the destruction of the pointee followed by the deallocation of the memory block** where the object was located Unsurprisingly, there are caveats to this as we will see Chapter 7

- In some situations, notably when some class X exposes at least one virtual member function, this sends the message that an X* might in practice point to an object of a class Y directly or indirectly derived from X. To ensure that the destructor of Y is actually called, not the destructor of X, it is customary to also qualify X::~X() as virtual. Not doing so risks not calling the correct destructor, leading to resource leaks.




# Managing resources

We can use try-catch block to manage our resources in case of exception

catch(...) will catch any C++ object used to represent an exception: you will not know what you caught, but you will have caught it

## Exception handling… or not?

We throw an exception from a function to signal that our function cannot achieve its postconditions (it cannot do the task it was meant to do)

in some cases (constructors and overloaded operators come to mind) exceptions really are the only sensible way to signal a problem to client code.




# The RAII idiom

C++ programmers tend to use destructors to automate the releasing of resources

**Resource acquisition is initialization (RAII)** \
The general idea is that objects tend to acquire resources at construction time (or later), but (and more importantly!) that releasing resources held by an object is something that usually should be done at the end of that object’s lifetime. Thus, RAII has more to do with destructors than with constructors

## RAII and C++’s special member functions

Numerous RAII objects can be said to be responsible for the resources we provide them with, which means that copying these objects could induce bugs (who would be responsible for the resources, the original or the copy?).

Thus, **consider deleting the copy operations for your RAII types** unless you have a good reason to implement them explicitly




# Some pitfalls

## Destructors should not throw

Indeed, **destructors are implicitly noexcept**, which means that **throwing from a destructor will call std::terminate()** and that will be the end of your program.

**what if I explicitly mark my destructor as noexcept(false) then, thus overriding the default behavior?** \
Well, this can work, but be careful as if a destructor throws during stack unwinding, such as what happens when an exception is already in flight, then this still calls std::terminate() and since you’ve been bad and have broken the rules, the compiler can optimize some of your code away.

## Know thy destruction order

automatic objects in scope are destroyed in reverse order of construction, and nested scopes behave as expected

Global objects are destroyed in reverse order of construction, but that order of construction is not always trivial to predict from our human perspective.




# Standard resource management automation tools

we will take a quick look at a few examples of types useful for resource management

## unique_ptr\<T> and shared_ptr\<T>

**unique_ptr\<T>**

- single ownership of the resource
- copy  ✗
- move  ✓
- Moving from a std::unique_ptr\<T> transfers ownership of the resource, leaving the moved-from object into an empty state conceptually analogous to a null pointer.
- The destructor of this type destroys the resource
managed by the object, if any.

**shared_ptr\<T>**

- shared ownership of the resource (mean co-owning the resource)

- copy  ✓
- copying an object means sharing the pointee
- copy assignment releases the resource held by the object on the left hand of the assignment and then shares the resource held by the object on the right side of the assignment between both objects

- move  ✓
- Moving from a std::shared_ptr\<T> transfers ownership of the resource, leaving the moved-from object into an empty state

- last co-owner of the resource is responsible for freeing it

- The destructor of this type releases ownership of the shared resource, destroying the resource managed by the object if that object was the last owner thereof.

## lock_guard and scoped_lock

std::lock_guard and std::scoped_lock support an object that locks a mutex at construction time and unlocks it when destroyed

## stream objects

In C++, stream objects are also resource owners.

Finally, the destructor of a stream object closes whatever representation of a stream it is responsible for.

Calling close() on a stream in C++ is unnecessary most of the time; just using the stream object in a limited scope generally suffices.

## vector<T> and other containers

C++ standard containers destructors manages memory





# References

C++ Memory Management | Patrice Roy

https://en.cppreference.com/cpp/memory/unique_ptr
https://en.cppreference.com/cpp/memory/shared_ptr
https://en.cppreference.com/cpp/memory/weak_ptr
https://en.cppreference.com/cpp/header/memory


