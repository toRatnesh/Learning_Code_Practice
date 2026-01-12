/*****

References

    Programming with C++20 | Andreas Fertig
	https://en.cppreference.com/w/cpp/language/coroutines


Chapter 2 | Coroutines: Suspending functions

    A coroutine is a function that can suspend itself.

2.2 What are Coroutines

    A regular function is executed once in total. 

    In contrast to that, a coroutine can suspend itself and return to the caller.
    This can happen multiple times and a coroutine is also able to call another coroutine.

		function												coroutine
    -------------------------------------                 ----------------------------------------------
   |	                          return |               |      co_yield         co_return              |
   |    --------->--------------         |               |      --->----         --->----               |
    ---|------------------------|--------                 -----|--------|-------|--------|--------------
	   ^                        |                              ^        |       |        |
	   |                        |                              |        |       |        |
    ---|------------------------|--------                 -----|--------|-------|--------|--------------
   |   |                        |        |               |     |         --->---          ------>       |
   |  call 	                     ->      |               |   call                                       |
    -------------------------------------                  ---------------------------------------------
		caller													caller
	
	
2.2.1 Generating a sequence with coroutines

    we can use coroutines to suspend and resume them.

    IntGenerator			// A - Returning a coroutine object
    counter(int start, int end)
    {
        while(start < end) {
        co_yield start;		// B - Yielding a value and giving control back to the caller
        ++start;
        }
    }

    void UseCounter()
    {
        auto g = counter(1, 5);

        // C - This sequence runs from 1 to 5
        for(auto i : g) { UseCounterValue(i); }
    }


    A does not simply return an int. IntGenerator returns some coroutine object.

    Coroutines are functions that can suspend themselves and be resumed by a using function.
    Every time a coroutine reaches a co_yield, the coroutine suspends itself and yields a value.
    While suspended, the entire state is preserved and used again when resumed.
    This is the difference to the definition of a regular function as we know it.

**********/

int main() {

	return 0;
}

/*****
    END OF FILE
**********/


