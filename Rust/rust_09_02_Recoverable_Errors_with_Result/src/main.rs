/*****

References
    https://doc.rust-lang.org/book/ch09-02-recoverable-errors-with-result.html
    https://doc.rust-lang.org/rust-by-example/error.html

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


9.2 Recoverable Errors with Result

Result
	Result enum is defined as having two variants, Ok and Err, as follows:

	enum Result<T, E> {
		Ok(T),
		Err(E),
	}

	T and E are generic type parameters
	T represents the type of the value that will be returned in a success case within the Ok variant
	E represents the type of the error that will be returned in a failure case within the Err variant

	use the Result type and the functions defined on it where the successful value and error value we want to return may differ

Matching on Different Errors
	We can add nested inner match expression 
	Example: code 

Alternatives to Using match with Result<T, E> (closures)
	closures, are used with many of the methods defined on Result<T, E>
	These methods can be more concise than using match when handling Result<T, E> values

Shortcuts for Panic on Error: unwrap and expect
	unwrap
		shortcut method implemented just like the match expression
		If the Result value is the Ok variant, unwrap will return the value inside the Ok
		If the Result is the Err variant, unwrap will call the panic! macro

	expect
		expect method lets us also choose the panic! error message
		
	In production-quality code, most Rustaceans choose expect rather than unwrap
	
Propagating Errors
	When a function’s implementation calls something that might fail, 
    instead of handling the error within the function itself, 
    you can return the error to the calling code so that it can decide what to do
	
A Shortcut for Propagating Errors: the ? Operator
	? placed after a Result value is defined to work in almost the same way as the match expressions
	? operator is defined to perform an early return of a value out of the function, in the same manner as the match expression
	
	If the value of the Result is an Ok, the value inside the Ok will get returned from this expression
	If the value is an Err, the Err will be returned from the whole function as if we had used the return keyword so the error value gets propagated to the calling code
	
	Difference between the match expression and ?
		error values that have the ? operator called on them go through the from function, 
        defined in the From trait in the standard library which is used to convert values from one type into another
		
		When the ? operator calls the from function, the error type received is converted into the error type defined in the return type of the current function
		
	Where The ? Operator Can Be Used
		? operator can only be used in functions whose return type is compatible with the value the ? is used on
		only allowed to use the ? operator in a function that returns Result, Option, or another type that implements FromResidual
		
NOTE:
	you can use the ? operator on a return value in a function that returns Result or Option,
	but you can’t mix and match
	
	The ? operator won’t automatically convert a Result to an Option or vice versa

Using Result in main
	main function may return any types that implement the std::process::Termination trait, 
    which contains a function report that returns an ExitCode

When a main function returns a Result<(), E>, the executable will exit with a value of 
    0 if main returns Ok(())
    a nonzero value if main returns an Err value

**********/

fn get_str_or_err(flag: bool) -> Result<String, std::io::Error> {

    let ret : Result<String, std::io::Error>; 

    if flag {
        ret = Ok(String::from("sample string"));
    } else {
        ret = Err(std::io::Error::new(std::io::ErrorKind::InvalidData, "Invalid input can not create data"));
    }

    return ret;
}

fn get_message(flag: bool) -> Result<String, std::io::Error> {

    let res = get_str_or_err(flag);

    match res {
        Ok(val) => Ok(val),
        Err(e)  => Err(e)
    }
}

fn get_message_02(flag: bool) -> Result<String, std::io::Error> {
    let res = get_str_or_err(flag)?;
    Ok(res)
}

fn main() {
    {
        println!("=== Recoverable Errors with Result ===");
        /*
        let file_ret = std::fs::File::open("read_this_file.txt");
        let file_h = match file_ret {
            Ok(fh)      => fh,
            Err(ferr) => panic!("Failed to open file {:?}", ferr)
        };

        let file_ret = std::fs::File::open("does_not_exist.txt");
        let file_h = match file_ret {
            Ok(fh)      => fh,
            Err(ferr) => panic!("Failed to open file {:?}", ferr)
        };
        */
    }
    

    {
        println!("\n=== Matching on Different Errors ===");
        /*
        let file_ret = std::fs::File::open("does_not_exist.txt");
        let file_h = match file_ret {
            Ok(fh)      => fh,
            Err(ferr)   => match ferr.kind() {
                std::io::ErrorKind::NotFound             => panic!("File not found"),   // may create file here
                std::io::ErrorKind::PermissionDenied     => panic!("File permission denied"),
                std::io::ErrorKind::AlreadyExists        => panic!("File already exist"),
                other_error => { panic!("Problem opening the file: {:?}", other_error); }
            }
        };
        */   
    }

    {
        println!("\n=== Alternatives to Using match with Result (closures) ===");

        /*
        let file_ret = std::fs::File::open("does_not_exist.txt").unwrap_or_else(
            | file_error | {

                let err_kind = file_error.kind();
                
                if err_kind == std::io::ErrorKind::NotFound {
                    panic!("File not found");
                } else if err_kind == std::io::ErrorKind::PermissionDenied {
                    panic!("File permission denied");
                } else if err_kind == std::io::ErrorKind::AlreadyExists {
                    panic!("File already exist");
                } else {
                    panic!("Problem opening the file: {:?}", file_error);
                }
            }
        );
        */
    }


    {
        println!("\n=== Shortcuts for Panic on Error: unwrap and expect ===");
        /*
        let file_h = std::fs::File::open("does_not_exist.log").unwrap();

        let file_h = std::fs::File::open("does_not_exist.log").expect(
            "Failed to open file does_not_exist.log"
        );
        */   
    }

    {
        println!("\n=== Propagating Errors ===");
        /*
        let res = get_message(true).expect(
            "Could not proceed because of invalid data"
        );
        println!("Result is: {}", res);

        let res = get_message(false).expect(
            "Could not proceed because of invalid data"
        );
        println!("Result is: {}", res);
        */
    }

    {
        println!("\n=== Propagating Errors: the ? Operator ===");
        
        let res = get_message_02(true).expect(
            "Could not proceed because of invalid data"
        );
        println!("Result is: {}", res);

        let res = get_message_02(false).expect(
            "Could not proceed because of invalid data"
        );
        println!("Result is: {}", res);
    }

}

/*****
    END OF FILE
**********/



