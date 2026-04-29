
# Async futures and performance

Futures returned by std::async behave differently from the ones obtained from promises when their destructors are called.

When these futures are destroyed, their ~future destructor is called where the wait() function is executed, causing the thread that was spawned at creation to join.


