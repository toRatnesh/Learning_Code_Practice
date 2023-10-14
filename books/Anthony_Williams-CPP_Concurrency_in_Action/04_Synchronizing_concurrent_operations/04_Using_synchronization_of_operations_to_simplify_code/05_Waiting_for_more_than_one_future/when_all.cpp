/*****

References
    Anthony Williams - C++ Concurrency in Action

    https://en.cppreference.com/w/cpp/experimental/when_all
    https://en.cppreference.com/w/cpp/experimental/when_any

4.4 Using synchronization of operations to simplify code
	Rather than sharing data directly between threads, each task can be provided with the data it needs, and the result can be disseminated to any other threads that need it through the use of futures.

4.4.5 Waiting for more than one future
	use when_all to wait for all the futures to become ready, and then schedule the function using .then rather than async
	when_all gave you a future that wrapped the collection of futures you passed in
	
	If case of multiple task we have to wait for each future in turn, and then gather the results
	This occupy the thread doing the waiting, but it adds additional context switches as each future becomes ready, which adds additional overhead
	
	Using std::experimental::when_all, this waiting and switching can be avoided
	You pass the set of futures to be waited on to when_all, and it returns a new future that becomes ready when all the futures in the set are ready.
	This future can then be used with continuations to schedule additional work when the all the futures are ready.
	
**********/


int main() {

    return 0;
}

/*****
    END OF FILE
**********/



