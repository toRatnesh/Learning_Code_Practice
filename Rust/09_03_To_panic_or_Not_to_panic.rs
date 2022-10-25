/********

References:
    https://doc.rust-lang.org/book/ch09-03-to-panic-or-not-to-panic.html
    https://doc.rust-lang.org/stable/rust-by-example/error.html


To panic! or Not to panic!
	When you should call panic! and when you should return Result?
	Call panic! for any error situation, whether there’s a possible way to recover or not
	Retutn Result, to give calling code options to recover or call panic! according to its situation
	Therefore, returning Result is a good default choice when you’re defining a function that might fail.
	In situations such as examples, prototype code, and tests, it’s more appropriate to write code that panics instead of returning a Result.
	
Creating Custom Types for Validation
	using Rust’s type system to ensure we have a valid value one step further and look at creating a custom type for validation

********/

// Creating Custom Types for Validation
struct Aget {
    age: u32
}

impl Aget {
    fn new(age : u32) -> Aget {
        if (age < 1) || (age > 100) {
            panic!("Age should be between 1 and 100. Entered value is {}", age);
        }
        Aget {age}
    }

    fn age(&self) -> u32 {
        self.age
    }
}

pub fn main() {
    let _localhost: std::net::IpAddr = "127.0.0.1".parse().expect(
        "Hardcoded IP address should be valid");


    // takign input and validating
    loop {

        println!("Please input your person_age.");
        let mut person_age = String::new();

        std::io::stdin()
            .read_line(&mut person_age)
            .expect("Failed to read line");

        let person_age: i32 = match person_age.trim().parse() {
            Ok(num) => num,
            Err(_) => continue,
        };

        if person_age < 1 || person_age > 100 {
            println!("Age should be between 1 and 100.");
            continue;
        }
        else {
            println!("Person age is {}", person_age);
            break;
        }
    }


    // takign input and validating using custom type
    loop {

        println!("Please input your person_age.");
        let mut person_age = String::new();

        std::io::stdin()
            .read_line(&mut person_age)
            .expect("Failed to read line");

        let person_age: Aget = match person_age.trim().parse() {
            Ok(num) => Aget::new(num),
            Err(_) => continue,
        };
        
        println!("Person age is {}", person_age.age());
        break;
    }

}

/********
    END OF FILE
********/
