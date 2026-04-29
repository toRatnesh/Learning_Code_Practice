

# What is std::async?

It is used to run a function asynchronously, allowing the main thread (or other threads) to continue running concurrently.

It immediately returns a future that will hold the value that the function or callable object will compute, as we saw in the previous chapter when using promises and futures.

Its automatic management and lack of control over the thread of execution, among other aspects, can also make it unsuitable for certain tasks where fine-grained control or cancellation is required.

