/********

References:
	https://doc.rust-lang.org/book/ch09-00-error-handling.html
	https://doc.rust-lang.org/stable/rust-by-example/error.html

Error Handling
    Rust groups errors into two major categories:
    1. Recoverable error, such as a file not found error, we most likely just want to report the problem to the user and retry the operation
    2. Unrecoverable errors are always symptoms of bugs, like trying to access a location beyond the end of an array, and so we want to immediately stop the program.
    
    Rust doesn’t have exceptions.
    Instead, it has the type 
    Result<T, E> for recoverable errors and the 
    panic! macro that stops execution when the program encounters an unrecoverable error. 

Unrecoverable Errors with panic!
    Two ways to cause a panic in practice: 
    1. By taking an action that causes our code to panic (such as accessing an array past the end) 
    2. By explicitly calling the panic! macro

    By default, these panics will print a failure message, unwind, clean up the stack, and quit.
    Set environment variable RUST_BACKTRACE to display the call stack when a panic occurs to make it easier to track down the source of the panic.

Unwinding the Stack or Aborting in Response to a Panic
    By default, when a panic occurs, the program starts unwinding.
    Rust, allows you to choose the alternative of immediately aborting, which ends the program without cleaning up.
    In case of abort, memory that the program was using will then need to be cleaned up by the operating system.

    To switch from unwinding to aborting upon a panic, add panic = 'abort' to the appropriate [profile] sections in your Cargo.toml file.
    Example
    [profile.release]
    panic = 'abort'

Using a panic! Backtrace
    Set the RUST_BACKTRACE environment variable to get a backtrace of exactly what happened to cause the error.
    A backtrace is a list of all the functions that have been called to get to this point.


********/

pub fn main() {
    //panic!("Calling panic manually"); // explicit panic

    let v = vec![1,2,3];
    let _elem = v[7];   // implicit panic
}


/********
    END OF FILE
********/