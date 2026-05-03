# Coroutines and exceptions
			
if the exception is thrown before the coroutine is executed, the code creating the coroutine must handle the exception,

if the exception is thrown when the coroutine is executed, then unhandled_exception() is called.

There are different strategies to handle such exceptions.

- Rethrow the exception so we can handle it outside the promise type (that is, in our code).
- Terminate the program (for example, calling std::terminate).
- Leave the function empty. In this case, the coroutine will crash and it will very likely crash the program too.
