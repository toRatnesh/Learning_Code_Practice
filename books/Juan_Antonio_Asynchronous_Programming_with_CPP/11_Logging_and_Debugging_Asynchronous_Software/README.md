11 Logging and Debugging Asynchronous Software
================================================

# How to use logging to spot bugs

Logging is the process of keeping a log of events that occur in a program, storing information by using messages to record how a program executes, tracking its flow, and helping with identifying issues and bugs.

Logging is useful where debuggers are not, as we will see later, especially in distributed, multithreaded, real-time, scientific, or event-centric applications, where inspecting data or following the program flow using the debugger can become a tedious task.

## How to select a third-party library

before integrating it into software check support for

- Support
- Quality
- Security
- License

## Some relevant logging libraries

Boost logging library | https://github.com/boostorg/log  
Google logging library | https://github.com/google/glog  
Log4cxx | https://logging.apache.org/log4cxx/1.7.0/  
spdlog | https://github.com/gabime/spdlog  
NanoLog | https://github.com/PlatformLab/NanoLog  

**For low-latency**  
Quill (https://github.com/odygrd/quill) is an asynchronous low-latency C++ logging library  
XTR (https://github.com/choll/xtr) is a fast and convenient C++ logging library for low-latency and real-time environments.  
Reckless (https://github.com/mattiasflodin/reckless) is a low-latency and high-throughput logging library.

- For low-latency or real-time systems: Quill, XTR, or Reckless
- For high performance at nanosecond scale logging: NanoLog
- For asynchronous logging: Quill or lwlog
- For cross-platform, multi-process applications: uberlog
- For simple and flexible logging: Easylogging++ or glog
- For familiarity with Java logging: Log4cxx

## Logging a deadlock – an example

Check example code

# How to debug asynchronous software
GDB - GNU project debugger
LLDB - LLVM low-level debugger

## Some useful GDB commands

To start the debugger and pass the program as an argument

    $ gdb <program> --args <args>

To attach the debugger to a running program by using its process identifier (PID)

    $ gdb –p <PID>

To analyze core dump
After the coredump file is generated, just copy it to the location where the program binary is located

    $ gdb <program> <coredump>

Note that all binaries must have debugging symbols, thus compiled with the –g option.  
In production systems, release binaries usually have symbols stripped and stored in separate files. There are GDB commands to include those symbols and command-line tools to inspect them


- **info args:** This shows information about arguments used to call the current function.
- **info locals:** This shows local variables in the current scope.
- **whatis:** This shows the type of the given variable or expression.
- **return:** This returns from the current function without executing the rest of the instructions. A return value can be specified.
- **backtrace:** This lists all stack frames in the current call stack.
- **frame:** This lets you change to a specific stack frame.
- **up, down:** This moves across the call stack, toward the caller (up) or the callee (down) of the current function. 
- **print:** This evaluates and displays the value of an expression, being that expression a variable name, a class member, a pointer to a memory region, or directly a memory address. We can also define pretty printers to display our own classes.
- **dprintf:** command helps to set printf-style breakpoints

    ```
    $ dprintf <location>, <format>, <args>
    $ dprintf 25, "x = %d\n", x if x > 5
    ```

To enable the GDB built-in pretty printers

    (gdb) set print pretty on

## Debugging multithreaded programs

to check what threads are running

    (gdb) info threads

If there are many threads and we are only interested in a specific subset, let’s say threads 1 and 3

    (gdb) info thread 1 3

To switch to another thread, for example, thread 2

    (gdb) thread 2

To execute a command in different threads, just use the thread apply command, in this case, executing the bt command on threads 1 and 3

    (gdb) thread apply 1 3 bt

To execute a command in all threads

    (gdb) thread apply all <command>

When a breakpoint is reached in a multithreaded program, all threads of execution stop running, allowing the examination of the overall state of the program. When the execution is restarted by commands such as continue, step, or next, all threads resume. The current thread will move one statement forward, but that is not guaranteed for other threads, which could move forward several statements or even stop in the middle of a statement.

When the execution stops, the debugger will jump and show the context of the execution in the current thread.  
To avoid the debugger jumping between threads by locking the scheduler

    (gdb) set scheduler-locking <on/off>

To check the scheduler locking status

    (gdb) show scheduler-locking


## Debugging race conditions

One way of debugging race conditions is to use watchpoints to manually inspect if a variable changes
its value without any statement executed in the current thread modifying it, or placing breakpoints
in strategic locations triggered by specific threads when reached, as shown here:

    (gdb) break <linespec> thread <id> if <condition>

    (gdb) break test.cpp:11 thread 2

Another way is using assertions and checking if the current value of any variable accessed by different threads has the expected value.

```
int old_value = g_value;
int incr = (rand() % 10);
g_value += incr;
assert(g_value == old_value + incr);
```

## Reverse debugging (aka Time travel debugging)

allows a debugger to stop a program after failure and go back into the history of the execution of a program to investigate the reason for the failure

GDB (since version 7.0), rr (originally developed by Mozilla)  
Undo’s time travel debugger  
Windows Time Travel Debugging

To record and replay a program

    $ rr record <program> --args <args>

    $ rr replay

If the program crashed and you want just to start debugging at the end of the recording, use the –e option:

    $ rr replay -e


You can use any of the following commands to reverse debugging:
- **reverse-continue:** Start executing the program in reverse. Execution will stop when a breakpoint is reached or due to a synchronous exception.
- **reverse-next:** Run backward to the beginning of the previous line executed in the current stack frame.
- **reverse-nexti:** This executes a single instruction in reverse, jumping those moving to inner stack frames.
- **reverse-step:** Run the program backward until the control reaches the start of a new source line.
- **reverse-stepi:** Execute in reverse one machine instruction.
- **reverse-finish:** This executes until the current function invocation, that is, the beginning of the current function.


We can also reverse the direction of debugging and use regular commands for forward debugging (such as next, step, continue, and so on) in the opposite direction by using the following command:

    (rr) set exec-direction reverse

To set the execution direction back to forward, use the following command:

    (rr) set exec-direction forward

## Debugging coroutines

For C++ coroutines, debugging is even harder to master due to their suspend/resume nature.

**Clang compiles programs using coroutines in two steps:** Semantic analysis is performed by Clang, and coroutine frames are constructed and optimized in the LLVM middle-end.  
As debug information is generated in the Clang frontend, there will be insufficient debug information as coroutine frames are generated later in the compilation process.

GCC follows a similar approach.

Also, if the execution breaks inside a coroutine, the current frame will only have one variable, frame_ptr. In a coroutine, there are no pointer or function parameters.

In pure C++ routines, there are two expressions where setting breakpoints
could be interesting:

- **co_await:** The execution is suspended until the awaited operation is complete. Breakpoints
can be set at the point where the coroutine is resumed by inspecting the underlying await_
suspend, await_resume, or custom awaitable code.

- **co_yield:** Suspends execution and yields a value. During debugging, step into the co_yield
to observe how control flows between coroutines and their calling functions.

# References

Asynchronous Programming with C++ | Javier Reguera-Salgado & Juan Antonio Rufes  
Debugging with GDB | https://ftp.gnu.org/old-gnu/Manuals/gdb/html_node/gdb_toc.html



