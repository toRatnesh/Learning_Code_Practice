/*****

References
    Anthony Williams - C++ Concurrency in Action

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

9.3 To panic! or Not to panic!
	You could call panic! for any error situation, whether there’s a possible way to recover or not
	When you return a Result value,
		calling code could choose to attempt to recover in a way that’s appropriate for its situation, or 
		it can call panic! and turn your recoverable error into an unrecoverable one
	Therefore, returning Result is a good default choice
	
	In situations such as examples, prototype code, and tests, 
	it’s more appropriate to write code that panics instead of returning a Result

Cases in Which You Have More Information Than the Compiler
	If you can ensure by manually inspecting the code that you’ll never have an Err variant, 
	it’s perfectly acceptable to call unwrap, and even better to document 
	the reason you think you’ll never have an Err variant in the expect text
	
	use std::net::IpAddr;

    let home: IpAddr = "127.0.0.1"
        .parse()
        .expect("Hardcoded IP address should be valid");
		
Guidelines for Error Handling
	code should panic when it’s possible that your code could end up in a bad state
	a bad state is when some assumption, guarantee, contract, or invariant has been broken,
	such as when invalid values, contradictory values, or missing values are passed to your code
		The bad state is something that is unexpected
		code after this point needs to rely on not being in this bad state
		There’s not a good way to encode this information in the types you use
		
	it’s best to return an error if you can so the user of the library can decide what they want to do in that case
	in cases where continuing could be insecure or harmful, the best choice might be to call panic!
	panic! is often appropriate if you’re calling external code 
	that is out of your control and it returns an invalid state that you have no way of fixing
	
	However, when failure is expected, it’s more appropriate to return a Result than to make a panic!
	
Creating Custom Types for Validation
	we can make a new type and put the validations in a function 
	to create an instance of the type rather than repeating the validations everywhere

	The conditions in which type might panic should be discussed in its public-facing API documentation
	also implement a method to get the value 

**********/

struct ValidAge {
    age: u32
}

impl ValidAge {
    fn new(value: u32) -> ValidAge {
        if value < 18 || value > 25 {
            panic!("Age should be between 18 and 25");
        }

        ValidAge{age: value}
    }

    fn get_age(&self) -> u32 {
        self.age
    }
}

fn main() {

    println!("=== Cases in Which You Have More Information Than the Compiler ===");
    let homeaddr : std::net::IpAddr = "127.0.0.1".parse().expect(
        "Hardcoded IP address should be valid"
    );
    println!("IP address {}", homeaddr);

    /*
    let homeaddr : std::net::IpAddr = "256.0.0.1".parse().expect(
        "Hardcoded IP address should be valid"
    );
    println!("IP address {}", homeaddr);
    */


    println!("\n=== Creating Custom Types for Validation ===");
    let age = ValidAge::new(20);
    println!("Age is {}", age.get_age());

    let age = ValidAge::new(17);
    println!("Age is {}", age.get_age());

}

/*****
    END OF FILE
**********/



