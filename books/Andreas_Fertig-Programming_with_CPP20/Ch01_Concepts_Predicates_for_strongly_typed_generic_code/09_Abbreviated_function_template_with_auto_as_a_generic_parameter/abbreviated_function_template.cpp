/*****

References
    Programming with C++20 | Andreas Fertig

Chapter 1 | Concepts: Predicates for strongly typed generic code

Sadly, when using the template with an unsupported type, finding any error requires a good understanding of the compiler’s error message.
The issue was that we had no way of specifying the requirements to prevent the misuse and at the same time give a clear error message.

1.9 Abbreviated function template with auto as a generic parameter
There are three places where we can use a concept in a function template to constrain a template parameter

We can use a concept in the so-called abbreviated function template syntax.
This syntax comes without a template-head, making the function terse. 
Instead, we declare what looks like a regular function, using the concept as a parameter type, together with auto.

1.9.1 What does such a construct do?

In the background, the compiler creates a function template for us.
Each concept parameter becomes an individual template parameter, to which the associated concept is applied as a constraint.

The constraining concept is optional. We can indeed declare a function, with only auto parameters.

1.9.2 Exemplary use case: Requiring a parameter type to be an invocable

Example: Following code

**********/

#include <iostream>
#include <type_traits>
#include <mutex>

std::mutex callable_lock;

template<typename T>
void callWithLock(T && callable) {
    std::lock_guard l_lock(callable_lock);
    callable();
}

// abbreviated function template syntax
void callWithLock_AFTS(std::invocable auto && callable) {
    std::lock_guard l_lock(callable_lock);
    callable();
}

int main() {

    callWithLock( [](){ std::puts("Using function template"); } );
    callWithLock_AFTS( [](){ std::puts("Using abbreviated function template"); } );

    // CE error: called object type 'int' is not a function or function pointer
    // callWithLock(2);
    
    // CE error: no matching function for call to 'callWithLock_AFTS'
    // note: candidate template ignored: constraints not satisfied [with callable:auto = int]
    // callWithLock_AFTS(2);

    return 0; 
}

/*****
    END OF FILE
**********/


