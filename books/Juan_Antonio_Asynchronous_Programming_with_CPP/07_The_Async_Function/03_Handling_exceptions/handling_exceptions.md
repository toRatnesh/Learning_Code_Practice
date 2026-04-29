
# Handling exceptions

Exception propagation from the asynchronous task to the main thread is not supported when using std::async.

To enable exception propagation, we might need a promise object to store the exception that later can be accessed by the future returned when calling std::async. But that promise object is not accessible or provided by std::async.

We could also use nested exceptions, available since C++11, by using std::nested_exception.

## Exceptions when calling std::async

std::async might throw an exception:

- **std::bad_alloc:** If there is not enough memory to store internal data structures needed
by std::async.

- **std:system_error:** If a new thread cannot be started when using std::launch::async as the launch policy. In this case, the error condition will be std::errc::resource_unavailable_try_again.


