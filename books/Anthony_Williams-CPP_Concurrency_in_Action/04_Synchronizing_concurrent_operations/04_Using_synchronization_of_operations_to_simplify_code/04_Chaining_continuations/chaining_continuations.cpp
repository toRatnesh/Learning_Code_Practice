/*****

References
    Anthony Williams - C++ Concurrency in Action

    https://en.cppreference.com/w/cpp/experimental/concurrency/promise
    https://en.cppreference.com/w/cpp/experimental/future
    https://en.cppreference.com/w/cpp/experimental/shared_future

4.4 Using synchronization of operations to simplify code
	Rather than sharing data directly between threads, each task can be provided with the data it needs, and the result can be disseminated to any other threads that need it through the use of futures.

4.4.4 Chaining continuations
	Continuation support chaining, we may chain task on the previous one as a continuation
	
	Each continuation takes a std::experimental::future as the sole parameter, and then uses .get() to retrieve the contained value
	This means that exceptions get propagated all the way down the chain
	
	future-unwrapping
		If the continuation function you pass to a .then() call returns a future<some_type>, then the .then() call will return a future<some_type> in turn. It will not return future<future<some_type>>.
		
	std::experimental::shared_future also supports continuations. 
	std::experimental::shared_future objects can have more than one continuation
	continuation parameter is a std::experimental::shared_future rather than a std::experimental::future
	
	Because multiple objects can refer to the same shared state, if only one continuation was allowed, there would be a race condition between two threads that were each trying to add continuations to their own std::experimental::shared_future objects
	
	auto fut=spawn_async(some_function).share();
	auto fut2=fut.then([](std::experimental::shared_future<some_data> data){
		do_stuff(data);
	});
	auto fut3=fut.then([](std::experimental::shared_future<some_data> data){
		return do_other_stuff(data);
	});
	
	However, the return value from the continuation is a plain std::experimental::future
	
**********/


int main() {

    return 0;
}

/*****
    END OF FILE
**********/



