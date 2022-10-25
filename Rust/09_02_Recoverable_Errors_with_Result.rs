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

Recoverable Errors with Result
    Result enum is defined as
        enum Result<T, E> {
            Ok(T),
            Err(E),
        }
    T represents the type of the value that will be returned in a success case within the Ok variant
    E represents the type of the error that will be returned in a failure case within the Err variant


Matching on Different Errors
    std::io::Error struct is provided by the standard library. 
    This struct has a method kind that we can call to get an std::io::ErrorKind value.
    The enum std::io::ErrorKind is provided by the standard library and has variants representing the different kinds of errors that might result from an io operation.

Alternatives to Using match with Result<T, E>
    Closures, which are used with many of the methods defined on Result<T, E>. 
    These methods can be more concise than using match when handling Result<T, E> values in your code.


Shortcuts for Panic on Error: unwrap and expect
    The Result<T, E> type has many helper methods defined on it to do various, more specific tasks. 
    unwarp()
    is a shortcut method implemented just like the match expression. 
    If the Result value is
    Ok variant, unwrap will return the value inside the Ok. 
    Err variant, unwrap will call the panic! macro for us.
    expect()
    the expect method lets us also choose the panic! error message.
    In production-quality code, most Rustaceans choose expect rather than unwrap


Propagating Errors
	When a function’s implementation calls something that might fail, instead of handling the error within the function itself, you can return the error to the calling code so that it can decide what to do. This is known as propagating the error.

	We return the error value in the same way that we returned the error value in the match that handled the return value of File::open. For last expression in the function, we don’t need to explicitly say return.

A Shortcut for Propagating Errors: the ? Operator
	Rust provides the question mark operator ? to make error propagation easier.

	The ? placed after a Result value is defined to work in almost the same way as the match expressions we defined to handle the Result values.
	If the value of the Result is an Ok, the value inside the Ok will get returned from this expression, and the program will continue. 
	If the value is an Err, the Err will be returned from the whole function as if we had used the return keyword so the error value gets propagated to the calling code.

Difference between ? and match expression return error
	Error values that have the ? operator called on them go through the from function, defined in the From trait in the standard library, which is used to convert values from one type into another. When the ? operator calls the from function, the error type received is converted into the error type defined in the return type of the current function. This is useful when a function returns one error type to represent all the ways a function might fail, even if parts might fail for many different reasons.

	For example, we could change the read_username_from_file function to return a custom error type named OurError that we define. If we also define impl From<io::Error> for OurError to construct an instance of OurError from an io::Error, then the ? operator calls in the body of read_username_from_file will call from and convert the error types without needing to add any more code to the function.

Where The ? Operator Can Be Used
	The ? operator can only be used in functions whose return type is compatible with the value the ? is used on. This is because the ? operator is defined to perform an early return of a value out of the function, in the same manner as the match expression.
    
********/

use std::io::Read;

// 4. Propagating Errors
fn read_username_from_file() -> Result<String, std::io::Error> {
    let username_file_result = std::fs::File::open("hello.txt");

    let mut username_file = match username_file_result {
        Ok(file) => file,
        Err(e) => return Err(e),
    };

    let mut username = String::new();

    match username_file.read_to_string(&mut username) {
        Ok(_) => Ok(username),
        Err(e) => Err(e),
    }
}

// 5. A Shortcut for Propagating Errors: the ? Operator
fn read_username_from_file_02() -> Result<String, io::Error> {
    let mut username_file = File::open("hello.txt")?;
    let mut username = String::new();
    username_file.read_to_string(&mut username)?;
    Ok(username)

    /* shorten version
    let mut username = String::new();
    File::open("hello.txt")?.read_to_string(&mut username)?;
    Ok(username)
    */
}

pub fn main() {
    // 1. Recoverable Errors with Result
    /*
    let file1_res = std::fs::File::open("DoNotExist.txt");
    let _file1_handle = match file1_res {
        Ok(fh) => fh,
        Err(error) => panic!("Error opening the file: {:?}", error),
    };
    */
    

    // 2. Matching on Different Errors
    let file2_res = std::fs::File::open("file_2.txt");
    let _file2_handle = match file2_res {
        Ok(file) => file,
        Err(error) => match error.kind() {
            std::io::ErrorKind::NotFound => match std::fs::File::create("file_2.txt") {
                Ok(fh) => fh,
                Err(e) => panic!("Error creating the file: {:?}", e)
            },
            other_error => panic!("Error opening the file: {:?}", other_error)
        }
    };

    // alternative to match, closures
    let _file3_res = std::fs::File::open("file_3.txt").unwrap_or_else(|error| {
        if error.kind() == std::io::ErrorKind::NotFound {
            std::fs::File::create("file_3.txt").unwrap_or_else(|error| {
                panic!("Error creating the file: {:?}", error);
            })
        } else {
            panic!("Error opening the file: {:?}", error);
        }
    });

    // 3. unwrap and expect
    let _file4_res = std::fs::File::open("file_4.txt").unwrap();

    let _file5_res = std::fs::File::open("file_5.txt").expect("file_5.txt is not found");

}

/********
    END OF FILE
********/
