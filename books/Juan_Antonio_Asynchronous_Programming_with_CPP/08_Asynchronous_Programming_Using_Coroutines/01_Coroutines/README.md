Coroutines are a mechanism that allows us, among other things, to perform multiple tasks in a single thread.
	
# Coroutines
		
A coroutine is a function that can suspend itself.

Coroutines suspend themselves while waiting for an input value (while they are suspended, they don’t execute)

or after yielding a value such as the result of a computation. 

Once the input value is available or the caller requests another value, the coroutine resumes execution.

