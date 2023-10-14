/*****

References
    Anthony Williams - C++ Concurrency in Action

    https://en.cppreference.com/w/cpp/experimental/concurrency/promise
    https://en.cppreference.com/w/cpp/experimental/future
    https://en.cppreference.com/w/cpp/experimental/shared_future

4.4 Using synchronization of operations to simplify code
	Rather than sharing data directly between threads, each task can be provided with the data it needs, and the result can be disseminated to any other threads that need it through the use of futures.

4.4.3 Continuation-style concurrency with the Concurrency TS
	Concurrency TS provides new versions of std::promise and std::packaged_task in the std::experimental namespace
	They return instances of std::experimental::future
	This enables to use std::experimental::future—continuations
	
	Suppose instead for the future to become ready, 
	What you want is a means of saying "When the data is ready, then do this processing"
	This is exactly what continuations give us
	
	A continuation is added with the call fut.then(continuation)
	
	std::experimental::future only allows the stored value to be retrieved once.
	If that value is being consumed by a continuation, this means it cannot be accessed by other code.
	
	Consequently, when a continuation is added with fut.then(), the original future, fut, becomes invalid. 
	Instead, the call to fut.then() returns a new future to hold the result of the continuation call.
	
	You cannot pass arguments to a continuation function, because the argument is already defined by the library—
	the continuation is passed a ready future that holds the result that triggered the continuation.
	
	The value returned from a then() call is a fully-fledged future itself.
	This means that you can chain continuations.
	
**********/


int main() {

    return 0;
}

/*****
    END OF FILE
**********/



