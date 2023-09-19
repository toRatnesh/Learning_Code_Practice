

.. contents:: Table of Contents

Smart Pointers
==============

Raw Pointers
------------

Too many uses and issues

**Single object vs Array of objects**

- Single allocate with new and deallocate with delete
- Single can not use increment(++p), decrement(--p) and index access(p[n])
- Array allocate with new[] and deallocate with delete[]
- Array can use increment(++p), decrement(--p) and index access(p[n])

**Owning vs Non-owning**

- owner must free the memory when done
- non-owner must never free the memory

**Nullable vs Non-nullable**

- Some pointers can never be null
- If type system enforce that, Its a good thing
- For C++, type system doesn't help

In C++, T* can be used for all above characteristics

Smart Pointer
-------------

Smart Pointer are tool used to overcome expansive behavior of raw pointers

It Behaves like a pointer with extra featues added to it like

- Automatically release resources is most common
- Enforce restrictions, e.g. don’t allow nullptr

Sometime smart pointer are only a typedef to a raw pointer, these are not useful

.. note::

  - Use raw pointer for non-owing pointer to a single object
  - Use smart pointers for all owning pointers
  - Use std::span in place of non-owning pointers to arrays

**Smart Pointer Types**

#. Unique Pointer
#. Shared Pointer
#. Weak Pointer


Unique Pointer
--------------

- define in header <memory>

.. code:: cpp

    template< class T,class Deleter = std::default_delete<T>> 
    class unique_ptr;
    
    // specialization for array types
    template <class T, class Deleter>
    class unique_ptr<T[], Deleter>;
    
- Act as sole owner of memory
- deallocates memory when the object goes out of scope
- copy or assignment is not supported
- only move operation is supported
- useful for implementing RAII
- specialized to support array type

To transfer ownership to a function, pass std::unique_ptr by value

To return ownership from a function, return std::unique_ptr by value

**Safety Check**

Make sure a pointer is owned by only one unique_ptr else it will lead to duble free

Do not create a unique pointer from a raw pointer unless you know about its owner and scope

.. code:: cpp

    // Wrong Examples which leads to duble free
    T * raw_p;
    std::unique_ptr<T> ptr1{raw_p};
    std::unique_ptr<T> ptr2{raw_p};
    
    
    auto ptr1 = std::make_unique<T>{args};
    std::unique_ptr<T> ptr2{ptr1.get()};

std::make_unique
^^^^^^^^^^^^^^^^

In general 

.. code:: cpp

	template< class T, class... Args >
	unique_ptr<T> make_unique( Args&&... args );
    
Combines 3 operations in one

- Allocates memory
- Constructs a T with the given arguments
- Wraps it in a std::unique_ptr<>

type deduction does not works it must be provided

supports array type by providing number of elements



.. note::
	
    Prefer using make_unique to create unique_ptr to avoid pitfalls related to object creation and memory allocation
    
    auto up = std::make_unique<int>(5);    
    
	is better than    
    
	std::unique_ptr<int> up(new int(5));
    
    
    
Shared Pointer
--------------

- define in header <memory>

.. code:: cpp

    template<class T>
    class shared_ptr;
    
- Acts as the owner of memory but shares ownership
- deallocated and destroy the object when last reference to it goes out of scope
- copyable

It has a control block which keeps
	
    - a pointer to the object
    - a reference counter to number of pointers pointing to it
    
To share ownership, additional shared_ptr objects must be created or assigned from an existing shared_ptr , not from the raw pointer

**Supports array type since C++17**

When using array with shared_ptr be very careful

Unique pointer can be used to transfer the ownership to shared pointer

But shared pointer can not be used to transfer to the ownership to unique pointer

.. code:: cpp

    // Following shared_ptr does not share ownership
    T * p = new T();
    std:: shared_ptr <T> a(p);
    std:: shared_ptr <T> b(p); // runtime error: double free
    
    auto a = std:: make_shared<T>();
    std:: shared_ptr<T> b(a.get); // runtime error: double free
    
    // Following code is correct for share ownership
    auto a = std:: make_shared<T>();
    std::shared_ptr<T> b(a); // creating using shared pointer
    std::shared_ptr<T> c;
    c = b;
    
 
std::make_shared
^^^^^^^^^^^^^^^^

In general 

.. code:: cpp

	template< class T, class... Args >
	shared_ptr<T> make_shared( Args&&... args );
    
Combines together:

- One memory allocation for both the object and the control block
- Constructs a T with the given arguments
- Initializes the control block
- Wraps them in a std:: shared_ptr <T> object
  
.. note::

	Prefer using make_shared to creating a shared_ptr directly for performance benefit and clean code
    

**Supports array type since C++20**


Thread Safety for shared_ptr
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Updating the same control block from different threads is thread safe

Updating the managed object from different threads is not thread safe

Updating the same shared_ptr object from different threads is not thread safe
    
Unique vs Shared Pointer
------------------------

Use unique_ptr for single ownership

Use shared_ptr for shared ownership


For non-owning reference use something else

Prefer unique_ptr because moving code from unique_ptr to shared_ptr is easy


Weak Pointer
-------------

.. code:: cpp

	template<class T>
	class weak_ptr;

A non-owning reference to a shared_ptr managed object

It is aware of the existence of the managed object

Use it for

when object is managed by shared_ptr

For caching

	- Keep a reference to an object for faster access
	- Don’t want that reference to keep the object alive
    
Dangling references If there is a chance that non-owning raw pointer might dangle use weak pointer for safety


Custom Deleters
---------------

a deleter is the function object or lvalue reference to function or to function object, to be called from the destructor

deleter for unique_ptr
^^^^^^^^^^^^^^^^^^^^^^

unique pointer has an extra defaulted template parameter for the delete

thus deleter it part of unique_ptr type

.. code:: cpp

    template< class T, class Deleter = std::default_delete<T>>
    class unique_ptr;

deleter must have an operator()(T*)

make_unique doesn’t support custom deleters

unique_ptr with custom deleter must be constructed directly

deleter for shared_ptr
^^^^^^^^^^^^^^^^^^^^^^

custom deleter for shared_ptr is not part of type

custom deleter for shared_ptr is passed to constructor, where it is type erased

shared pointer allocates memory on heap for control block where it can store type erased information so it can take deleter in constructor unique_ptr does not have such feature so it has to make deleter as part of the type

when a shared pointer is copied its deleter is also copied

when all the shared_ptr object goes out of scope the deleter is called


Other Things About Smart Pointers
----------------------------------


Casts
^^^^^^

To have share_ptrs of different types that manage the same object

dynamic_pointer_cast, static_pointer_cast , const_pointer_cast , reinterpret_pointer_cast

Aliasing Constructor
^^^^^^^^^^^^^^^^^^^^

Two shared_ptrs use same control block, but have unrelated object pointers

Useful for pointers to subobjects of managed objects

shared_from_this
^^^^^^^^^^^^^^^^^

To convert this into a shared_ptr

- Class derives from enable_shared_from_this
- Object is already managed by a shared_ptr
- return this->shared_from_this();


Conclusions
-----------

Raw Pointers vs Smart Pointers
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Raw pointers can fulfill lots of roles

- Can’t fully communicate the programmer’s intent


Smart pointers can be very powerful

- Automatic tasks, especially cleanup
- Extra checking
- Limited API, to better express programmer’s intent

Standard vs Custom Smart Pointers
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Standard C++ has two commonly used smart pointers

unique_ptr and shared_ptr
	
	Use them whenever they fit your needs

Don’t limit yourself to standard smart pointers

	If your framework has smart pointers, use them
	
	Write your own if necessary
	
	“The Smart Pointers I Wish I Had” Matthew Fleming, CppCon 2019
	
Guidelines
^^^^^^^^^^^

Use smart pointers to represent ownership

Prefer unique_ptr over shared_ptr

Use make_unique and make_shared

Pass/return unique_ptr to transfer ownership between functions



References
----------

| `Back to Basics: C++ Smart Pointers - David Olsen - CppCon 2022 <https://www.youtube.com/watch?v=YokY6HzLkXs>`_
| https://en.cppreference.com/w/cpp/memory/unique_ptr
| https://en.cppreference.com/w/cpp/memory/shared_ptr
| https://en.cppreference.com/w/cpp/memory/unique_ptr/make_unique
| https://en.cppreference.com/w/cpp/memory/shared_ptr/make_shared



