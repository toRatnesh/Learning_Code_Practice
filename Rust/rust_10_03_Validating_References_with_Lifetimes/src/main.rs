/*****

References
    https://doc.rust-lang.org/book/ch10-03-lifetime-syntax.html
    https://doc.rust-lang.org/rust-by-example/trait.html


Generic Types, Traits, and Lifetimes
    Generics allow code to operate on abstract types.

    We can express the behavior of generics without knowing what will be in their place when compiling and running the code.
    Functions can take parameters of some generic type, in the same way a function takes parameters with unknown values to run the same code on multiple concrete values.
    Examples
        Option<T>
        Vec<T>
        HashMap<K, V>
        Result<T, E>

    You may define types, functions, and methods with generics

    Traits: You can combine traits with generic types to constrain a generic type to accept only those types that have a particular behavior, as opposed to just any type.

    Lifetimes: a variety of generics that give the compiler information about how references relate to each other.


10.3 Validating References with Lifetimes
    
    Lifetimes are another kind of generic that we’ve already been using
    Lifetimes ensure that references are valid as long as we need them to be

    Every reference in Rust has a lifetime, which is the scope for which that reference is valid
    Most of the time, lifetimes are implicit and inferred

    We must annotate lifetimes when the lifetimes of references could be related in a few different way

    Rust requires us to annotate the relationships using generic lifetime parameters 
        to ensure the actual references used at runtime will definitely be valid
        
Preventing Dangling References with Lifetimes
	The main aim of lifetimes is to prevent dangling references
	Example

		fn main() {
			let r;
			{
				let x = 5;
				r = &x;
			}
			println!("r: {}", r);
		}
		
	Compilation error, because what the value r is referring to has gone out of scope before we try to use it
	
	Rust uses a borrow checker

The Borrow Checker
	Borrow checker compares scopes to determine whether all borrows are valid
	
	Example: Invalid code, showing the lifetime of variables
	
	fn main() {
		let r;                // ---------+-- 'a
		{                     //          |
			let x = 5;        // -+-- 'b  |
			r = &x;           //  |       |
		}                     // -+       |
		println!("r: {}", r); //          |
	}                         // ---------+

	The lifetime of x('b block) is much smaller than the lifetime of r('a block)
	At compile time, Rust compares the size of the two lifetimes and sees that r has a lifetime of 'a but that it refers to memory with a lifetime of 'b.
	The program is rejected because 'b is shorter than 'a: the subject of the reference doesn’t live as long as the reference.

	Example: Valid code, showing the lifetime of variables
	
	fn main() {
		let x = 5;            // ----------+-- 'b
		let r = &x;           // --+-- 'a  |
		println!("r: {}", r); //   |       |
							  // --+       |
	}                         // ----------+	
	
	Here, x has the lifetime 'b, which in this case is larger than 'a. 
	This means r can reference x because Rust knows that the reference in r will always be valid while x is valid.


Generic Lifetimes in Functions
	Consider a function that returns the longer of two string slices
	
	fn longest(x: &str, y: &str) -> &str {
		if x.len() > y.len() {
			x
		} else {
			y
		}
	}

	Compilation error: error[E0106]: missing lifetime specifier
	help: this function's return type contains a borrowed value, but the signature does not say whether it is borrowed from `x` or `y`
	help: consider introducing a named lifetime parameter
		|
		| fn longest<'a>(x: &'a str, y: &'a str) -> &'a str {
	
	
	The return type needs a generic lifetime parameter on it because Rust can’t tell whether the reference being returned refers to x or y
	
	Issue with above code
		We don’t know whether the if case or the else case will execute
		We also don’t know the concrete lifetimes of the references that will be passed in, 
			so we can’t look at the scopes to determine whether the reference we return will always be valid.
		The borrow checker can’t determine this either, because 
			it doesn’t know how the lifetimes of x and y relate to the lifetime of the return value


Lifetime Annotation Syntax
	Lifetime annotations describe the relationships of the lifetimes of multiple references to each other without affecting the lifetimes
	Functions can accept references with any lifetime by specifying a generic lifetime parameter
	
	Lifetime annotations syntax:
		ames of lifetime parameters must start with an apostrophe (') and 
		are usually all lowercase and very short, like generic types

		Common name is 'a for the first lifetime annotation
		
	Place lifetime parameter annotations after the & of a reference, using a space to separate the annotation from the reference’s type
	
	Examples
		&i32        // a reference
		&'a i32     // a reference with an explicit lifetime
		&'a mut i32 // a mutable reference with an explicit lifetime

	
Lifetime Annotations in Function Signatures
	We need to declare the generic lifetime parameters inside angle brackets between the function name and the parameter list
	The signature express the following constraint: the returned reference will be valid as long as both the parameters are valid
	This is the relationship between lifetimes of the parameters and the return value
	
	fn longest<'a>(x: &'a str, y: &'a str) -> &'a str {
	
	The function signature also tells Rust that the string slice returned from the function will live at least as long as lifetime 'a
	In practice, it means that the lifetime of the reference returned by the longest function is the same as 
		the smaller of the lifetimes of the values referred to by the function arguments
	When we specify the lifetime parameters in this function signature,
		We’re specifying that the borrow checker should reject any values that don’t adhere to these constraints


Thinking in Terms of Lifetimes
	The way in which you need to specify lifetime parameters depends on what your function is doing
	Example
		if the longest function always return first parameter, there is no need to specify a lifetime on the second parameter
		fn longest<'a>(x: &'a str, y: &str) -> &'a str {
			x
		}		
		
	When returning a reference from a function, the lifetime parameter for the return type needs to match the lifetime parameter for one of the parameters. 
	If the reference returned does not refer to one of the parameters, it must refer to a value created within this function. 
	However, this would be a dangling reference because the value will go out of scope at the end of the function.
	
	Ultimately, lifetime syntax is about connecting the lifetimes of various parameters and return values of functions.
	To allow memory-safe operations and disallow operations that would create dangling pointers or otherwise violate memory safety
	

Lifetime Annotations in Struct Definitions
	For structs to hold references, add a lifetime annotation on every reference in the struct’s definition

	
Lifetime Elision
	Every reference has a lifetime and we need to specify lifetime parameters for functions or structs that use references
	Sometimes we do not need to specify lifetime parameters, Example
		fn first_word(s: &str) -> &str {
	
	In early versions (pre-1.0) of Rust, 
		fn first_word<'a>(s: &'a str) -> &'a str {
		
	The developers programmed these patterns into the compiler’s code so the borrow checker could 
		infer the lifetimes in these situations and wouldn’t need explicit annotations.
		
	Lifetime Elision Rules
		They’re a set of particular cases that the compiler will consider, and if your code fits these cases, 
		you don’t need to write the lifetimes explicitly.
		
	Input Lifetimes
		Lifetimes on function or method parameters
	
	Output Lifetimes
		Lifetimes on return values
		
	The compiler uses three rules to figure out the lifetimes of the references when there aren’t explicit annotations
	These rules apply to fn definitions as well as impl blocks.
	
	1st Rule:
		applies to input lifetimes
		compiler assigns a lifetime parameter to each parameter that’s a reference
		
		fn foo<'a>(x: &'a i32);
		fn foo<'a, 'b>(x: &'a i32, y: &'b i32);
		
	2nd Rule:
		applies to output lifetimes
		if there is exactly one input lifetime parameter, that lifetime is assigned to all output lifetime parameters
		
		fn foo<'a>(x: &'a i32) -> &'a i32
		
	3rd Rule:
		if there are multiple input lifetime parameters, but one of them is &self or &mut self because this is a method, 
		the lifetime of self is assigned to all output lifetime parameters
		
	If the compiler gets to the end of the three rules and there are still references for which it can’t figure out lifetimes, 
	the compiler will stop with an error.
	
	Example
		fn first_word(s: &str) -> &str {						// initial		
		fn first_word<'a>(s: &'a str) -> &str {					// after 1st rule
		fn first_word<'a>(s: &'a str) -> &'a str {				// after 2nd rule
		
		fn longest(x: &str, y: &str) -> &str {					// initial
		fn longest<'a, 'b>(x: &'a str, y: &'b str) -> &str {	// after 1st rule
		2nd rule doesn’t apply because there is more than one input lifetime
		3rd rule doesn’t apply either, because longest is not a method
		After working through all three rules, we still haven’t figured out what the return type’s lifetime is.
		So we will get compilation error
		
		
Lifetime Annotations in Method Definitions
	Lifetime names for struct fields always need to be declared after the impl keyword and then used after the struct’s name, 
		because those lifetimes are part of the struct’s type
	In method signatures inside the impl block, references might be tied to the lifetime of references in the struct’s fields, 
		or they might be independent
	In addition, the lifetime elision rules often make it so that lifetime annotations aren’t necessary in method signatures
	
	Example-01
		impl<'a> ImportantExcerpt<'a> {
			fn level(&self) -> i32 {
				3
			}
		}
		
		The lifetime parameter declaration after impl and its use after the type name are required, 
		but we’re not required to annotate the lifetime of the reference to self because of the first elision rule.

	Example-02
		impl<'a> ImportantExcerpt<'a> {
			fn announce_and_return_part(&self, announcement: &str) -> &str {
				println!("Attention please: {}", announcement);
				self.part
			}
		}

		Rust applies the first lifetime elision rule and gives both &self and announcement their own lifetimes
		Then, because one of the parameters is &self, the return type gets the lifetime of &self, and all lifetimes have been accounted for
		

The Static Lifetime
	'static, denotes that the affected reference can live for the entire duration of the program
	All string literals have the 'static lifetime
	
	let s: &'static str = "I have a static lifetime.";

	The text of this string is stored directly in the program’s binary, which is always available.
	
	Most of the time, an error message suggesting the 'static lifetime results from 
		attempting to create a dangling reference or a mismatch of the available lifetimes.
	In such cases, the solution is fixing those problems, not specifying the 'static lifetime.


Generic Type Parameters, Trait Bounds, and Lifetimes Together
	
	use std::fmt::Display;

	fn longest_with_an_announcement<'a, T>(
		x: &'a str,
		y: &'a str,
		ann: T,
	) -> &'a str
	where
		T: Display,
	{
		println!("Announcement! {}", ann);
		if x.len() > y.len() {
			x
		} else {
			y
		}
	}

**********/

/*****
// Generic Lifetimes in Functions
fn largest_str_without_lifetime(first: &str, second: &str) -> &str {    // error[E0106]: missing lifetime specifier
    if first.len() > second.len() {
        first
    } else {
        second
    }
}
*****/

fn largest_str_with_lifetime<'a>(first: &'a str, second: &'a str) -> &'a str {
    if first.len() > second.len() {
        first
    } else {
        second
    }
}

/*****
// Thinking in Terms of Lifetimes
fn invalid_return<'a>() -> &'a str {
    let result = String::from("This will destroy at the end of function 
                                and any reference to it will become danglimg");
    result.as_str()     // error[E0515]: cannot return value referencing local variable `result`
}
*****/

// Thinking in Terms of Lifetimes
fn display_me<'a>(first: &'a str, second: &str) -> &'a str {
    println!("first {first} second {second}");
    first
}

// Lifetime Annotations in Struct Definitions
struct Data<'a> {
    //data: &str      // error[E0106]: missing lifetime specifier
    data: &'a str
}

// Lifetime Annotations in Method Definitions
impl<'a> Data<'a> {
    fn display_with_data(&self, val: &str) -> &str {
        println!("{} {}", self.data, val);
        //let res = self.data
        self.data
    }
}

// Lifetime Elision
// No need to specify lifetime parameter (since Rust 1.0) compiler can deduce in this case
fn display_one_parm(val: &str) -> &str {    
    println!("string value is {val}");
    val
}

fn display_two_parm<'a>(val1: &'a str, val2: &'a str, ret_first: bool) -> &'a str {
    println!("1st value is {val1} 2nd value is {val2}");
    if ret_first {
        val1
    } else {
        val2
    }
}

// The Static Lifetime
fn use_static_lfetime() -> &'static i32 {
    let val: &'static i32 = &5;
    println!("static value is {val}");
    val
}

// Generic Type Parameters, Trait Bounds, and Lifetimes Together
fn generic_trait_and_lifetime_together<'a, T>
    (x: &'a str, y: &'a str, msg: T) -> &'a str
where 
    T: std::fmt::Display
{
    println!("{}", msg);
    if x.len() > y.len() {
        x
    } else {
        y
    }
}

fn main() {

    {
        println!("=== Preventing Dangling References with Lifetimes ===");

        let r;
        {
            let val: u32 = 25;
            r = &val;
            println!("Inner scope, Value using reference is {{r}} {r}");
        }
        
        //println!("Value using reference is {{r}} {r}");   // error[E0597]: `val` does not live long enough
    }

    {
        println!("\n=== The Borrow Checker ===");

        let r;
        let val: u32 = 25;
        r = &val;
        println!("Value using reference is {{r}} {r}");   // error[E0597]: `val` does not live long enough
    }

    {
        let val: u32 = 25;
        {
            let r = &val;
            println!("Value using reference is {{r}} {r}");   
        }
    }

    {
        println!("\n=== Generic Lifetimes in Functions ===");
        println!("We might get compilation error without lifetime annotation");
    }

    {
        println!("\n=== Lifetime Annotation Syntax ===");
        println!("Use lifetime annotation as following: ");
        println!("  &'a i32");
        println!("  &'a mut i32");

    }

    {
        println!("\n=== Lifetime Annotations in Function Signatures ===");

        {
            let str1 = String::from("small str");
            let str2 = String::from("large string");
            let result = largest_str_with_lifetime(str1.as_str(), str2.as_str());
            println!("largest_str_with_lifetime(str1.as_str(), str2.as_str()): {result}");
        }   
        {
            let str1 = String::from("small str");
            {
                let str2 = String::from("large string");
                let result = largest_str_with_lifetime(str1.as_str(), str2.as_str());
                println!("largest_str_with_lifetime(str1.as_str(), str2.as_str()): {result}");
            } 
        }
        {
            let str1 = String::from("small str");
            let result;
            {
                let str2 = String::from("large string");
                result = largest_str_with_lifetime(str1.as_str(), str2.as_str());
            }
            //println!("largest_str_with_lifetime(str1.as_str(), str2.as_str()): {result}");  // error[E0597]: `str2` does not live long enough
        } 
        {
            let str2 = String::from("large string");
            let result;
            {
                let str1 = String::from("small str");       
                result = largest_str_with_lifetime(str1.as_str(), str2.as_str());
            }
            //println!("largest_str_with_lifetime(str1.as_str(), str2.as_str()): {result}");  // error[E0597]: `str1` does not live long enough
        }                    
    }

    {
        println!("\n=== Thinking in Terms of Lifetimes ===");
        let str1 = String::from("string - 1");
        let str2 = String::from("string - 2");
        let result = display_me(str1.as_str(), str2.as_str());
        println!("result {result}");
    }

    {
        println!("\n=== Lifetime Annotations in Struct Definitions ===");

        {
            let sval = String::from("First#Second#Third#Fourth");
            let apart = sval.split('#').next().expect("Could not find # in string value");
            let data = Data {
                data: apart
            };
            println!("Part of string data is {}", data.data);
        }

        {
            let apart;
            {
                let sval = String::from("First#Second#Third#Fourth");
                apart = sval.split('#').next().expect("Could not find # in string value");
            }
            /*
            error[E0597]: `sval` does not live long enough
            let data = Data {
                data: apart
            };
            println!("Part of string data is {}", data.data);
            */
        }
    }

    {
        println!("\n=== Lifetime Elision ===");
        let str1 = String::from("string - 1");
        let str2 = String::from("string - 2");
        {
            let result = display_one_parm(str1.as_str());
            println!("Result is {result}");
        }
        {
            let result = display_two_parm(str1.as_str(), str2.as_str(), true);
            println!("Result is {result}");
        } 
        {
            let result = display_two_parm(str1.as_str(), str2.as_str(), false);
            println!("Result is {result}");
        }        
    }

    {
        println!("\n=== Lifetime Annotations in Method Definitions ===");
        let sval = String::from("First#Second#Third#Fourth");
        let apart = sval.split('#').next().expect("Could not find # in string value");
        let data = Data {
            data: apart
        };
        data.display_with_data("this is parm value");
    }

    {
        println!("\n=== The Static Lifetime ===");
        use_static_lfetime();
        use_static_lfetime();
    }

    {
        println!("\n=== Generic Type Parameters, Trait Bounds, and Lifetimes Together ===");
        let str1 = String::from("small string");
        let result;
        {
            let str2 = String::from("another sample string");
            result = generic_trait_and_lifetime_together(str1.as_str(), str2.as_str(), "this will fail");
            println!("Result {result}");

            let data = Data {
                data: str1.as_str()
            };

            // error[E0277]: `Data<'_>` doesn't implement `std::fmt::Display`
            // result = generic_trait_and_lifetime_together(str1.as_str(), str2.as_str(), data);
        }
        //println!("Result {result}");    // error[E0597]: `str2` does not live long enough

    }
}

/*****
    END OF FILE
**********/


