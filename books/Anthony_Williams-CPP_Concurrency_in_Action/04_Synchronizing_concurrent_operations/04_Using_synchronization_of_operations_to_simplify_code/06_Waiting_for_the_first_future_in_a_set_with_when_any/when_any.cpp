/*****

References
    Anthony Williams - C++ Concurrency in Action

    https://en.cppreference.com/w/cpp/experimental/when_all
    https://en.cppreference.com/w/cpp/experimental/when_any

4.4 Using synchronization of operations to simplify code
	Rather than sharing data directly between threads, each task can be provided with the data it needs, and the result can be disseminated to any other threads that need it through the use of futures.

4.4.6 Waiting for the first future in a set with when_any
	use std::experimental::when_any to gather the futures together, and provide a new future that is ready when at least one of the original set is ready
	
	when_any adds a further layer, combining the collection with an index value that indicates which future triggered the combined future to be ready into an instance of the std::experimental::when_any_result class template
	
	when_all and when_any also come in variadic forms, where they accept a number of futures directly as parameters to the function
	In this case, the result is a future holding a tuple (or a when_any_result holding a tuple) rather than a vector

**********/


int main() {

    return 0;
}

/*****
    END OF FILE
**********/



