/*****

References

    Programming with C++20 | Andreas Fertig
	https://en.cppreference.com/w/cpp/language/coroutines


Chapter 2 | Coroutines: Suspending functions

    A coroutine is a function that can suspend itself.

2.1 Regular functions and their control flow

    Consider the following example

    for(int i = 0; i < 5; ++i) { UseCounterValue(i); }

    // other code
    for(int i = 5; i < 10; ++i) { UseCounterValue(i); }

    one issue with this piece of code is the missing separation between creating the numbers and passing them to a function. 
    In other words, we have a mixture of generation and usage.


    A more general view on this code reveals that we have an algorithm that generates the numbers from 1 to N.
    Then, we use the generated data in UseCounterValue. 
    Such a separation would improve our code, because we then could reuse the forloop.

    Alternative
    .	a lambda with init-capture, but then making the lambda run only to 5 is hard
    .	write a function template that takes a callable as one parameter
        This would allow us to pass the using-part to the generator
        But then it is not easy to see what parameters this callable takes
    .	use a function with a static variable that stores the current counter value and increments the value during return
        We then use this function counter and pass the return value to UseCounterValue
        
        we have no way to reset the internal value of counter
        Even if we would add some kind of reset mechanism, counter will never be usable in a multi-threading context

	
    Ideally, the algorithm’s generator could just be resumed where it was suspended, keeping its state. 
    We could also spawn thousands of instances of the same generator, 
    each of them starting at the same initial value, and keeping track of its own state.

    This suspend and resume with state preservation is exactly what coroutines give us.

**********/

#include <iostream>
#include <format>

void useCounter(const int val) {
    std::cout << std::format("counter value: {}\n", val);
}

auto counter(const int start, const bool reset = false) {
    static int val = start;
    
    if(reset) {
        val = start;
    }
    return val++;
}

int main() {

    std::cout << std::format("=== using for loop ===\n");
    for(int i = 0; i < 5; ++i) {
        useCounter(i);
    }

    std::cout << std::format("\n=== using static value in function ===\n");
    for(int i = 0; i < 5; ++i) {
        useCounter(counter(11));
    }

    std::cout << std::format("\n=== using static value in function ===\n");
    for(int i = 0; i < 5; ++i) {
        useCounter(counter(11, i ? false : true));
    }

	return 0;
}

/*****
    END OF FILE
**********/
