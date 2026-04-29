# Launch policies

- **std::launch::async:** The task is executed in a separate thread.

- **std::launch::deferred:** Enables lazy evaluation by executing the task in the calling thread the first time its result is requested via the future get() or wai () method.

*Default launch policy will be std::launch::async | std::launch::deferred.*


