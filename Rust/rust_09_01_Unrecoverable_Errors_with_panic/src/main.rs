/*****

References
    https://doc.rust-lang.org/book/ch09-01-unrecoverable-errors-with-panic.html
    https://doc.rust-lang.org/rust-by-example/error/panic.html

9. Error Handling

Two major categories of error: 
    1. recoverable error
    2. unrecoverable error

	Rust doesn’t have exceptions

1. Recoverable error
	recoverable error, such as a file not found error, 
	we most likely just want to report the problem to the user and retry the operation

	 type Result<T, E> for recoverable errors

2. Unrecoverable error
	Unrecoverable errors are always symptoms of bugs, 
	like trying to access a location beyond the end of an array, 
	and so we want to immediately stop the program

	panic! macro that stops execution when the program encounters an unrecoverable error

9.1 Unrecoverable Errors with panic!

Two ways to cause a panic in practice:
    1. by taking an action that causes our code to panic (such as accessing an array past the end)
    2. by explicitly calling the panic! macro

	By default, these panics will print a failure message, unwind, clean up the stack, and quit
	Via an environment variable, you can also have Rust display the call stack when a panic occurs

Unwinding the Stack or Aborting in Response to a Panic
	By default, when a panic occurs, the program starts unwinding, which means Rust walks back up the stack and cleans up the data from each function it encounters.
	Rust, therefore, allows to choose the alternative of immediately aborting, which ends the program without cleaning up.

	To abort upon a panic add panic = 'abort' to the appropriate [profile] sections in your Cargo.toml file
	For example, to abort on panic in release mode, add this:
		[profile.release]
		panic = 'abort'

Using a panic! Backtrace
	set the RUST_BACKTRACE environment variable to get a backtrace of exactly what happened to cause the error
	A backtrace is a list of all the functions that have been called to get to this point
	 
	the key to reading the backtrace is to start from the top and read until you see files you wrote. That’s the spot where the problem originated.
	The lines above that spot are code that your code has called; the lines below are code that called your code.
	These before-and-after lines might include core Rust code, standard library code, or crates that you’re using 
	
	In order to get backtraces with this information, debug symbols must be enabled.

**********/

fn main() {

    // setting env variable RUST_BACKTRACE for backtrace
    // run with `RUST_BACKTRACE=full` for a verbose backtrace.
    std::env::set_var("RUST_BACKTRACE", "1");

    let args: Vec<String> = std::env::args().collect();
    println!("args[0] {}", args[0]);
    println!("args[1] {}", args[1]);

    let index : usize = args[1].trim().parse().unwrap();
    println!("index {}", index);

    let arr = [1, 2, 3, 4, 5];
    let aval = arr[index];
    println!("value {}", aval);

    panic!("Learning Rust Panic");

}

/*****
    END OF FILE
**********/



