/*****

References
    https://doc.rust-lang.org/book/ch10-01-syntax.html
    https://doc.rust-lang.org/rust-by-example/generics/gen_fn.html
    https://doc.rust-lang.org/rust-by-example/generics/impl.html

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

Generic Data Types

In Function Definitions
	To parameterize the types in a new single function, we need to name the type parameter
	You can use any identifier as a type parameter name
	Short for “type,” T is the default choice
	
	To define the generic function, place type name declarations inside angle brackets, <>, between the name of the function and the parameter list, like this:
	fn function_name<T>(list: &[T]) -> &T {}
	
	
In Struct Definitions
	Declare the name of the type parameter inside angle brackets just after the name of the struct
	Then we use the generic type in the struct definition where we would otherwise specify concrete data types
	
	We can use multiple generic type parameters


In Enum Definitions
	Like structs, we can define enums to hold generic data types in their variants
	Enums can use multiple generic types as well
		enum Result<T, E> {
			Ok(T),
			Err(E),
		}

In Method Definitions
	We can implement methods on structs and enums and use generic types in their definitions, too.
	We have to declare T just after impl so we can use T to specify that we’re implementing methods on the type Point<T>.
	
	We could have chosen a different name for this generic parameter than the generic parameter declared in the struct definition, but using the same name is conventional.
	We can also specify constraints on generic types when defining methods on the type.
	
	Generic type parameters in a struct definition aren’t always the same as those you use in that same struct’s method signatures.
	
	
Performance of Code Using Generics
	using generic types won't make your program run any slower
	Monomorphization is the process of turning generic code into specific code by filling in the concrete types that are used when compiled.
	In this process, the compiler looks at all the places where generic code is called and generates code for the concrete types the generic code is called with.
	
	Example
		let integer = Some(5);
		let float = Some(5.0);
		
		When Rust compiles this code, it performs monomorphization.
		During that process, the compiler reads the values that have been used in Option<T> instances and identifies two kinds of Option<T>: one is i32 and the other is f64.

**********/

fn get_double<T>(val : T) -> T {
    let ret = val;
    //let ret = val * 2;
    ret
}

struct Point<T> {
    x:  T,
    y:  T
}

impl<T: std::fmt::Display> Point<T> {
    fn display(&self) {
        println!("({}, {})", self.x, self.y);
    }
}

enum IPVal<T> {
    V4(T),
    V6(T)
}

fn use_enum<T: std::fmt::Display>(ip_val : IPVal<T>) {
    match ip_val {
        IPVal::V4(val) => println!("IPv4 is {}", val),
        IPVal::V6(val) => println!("IPv6 is {}", val),
    }
}

fn main() {
    println!("=== Generic Function ===");
    let res = get_double(2);
    println!("res {res}");

    let res = get_double(3.6);
    println!("res {res}");

    println!("\n=== Generic Struct and Methods ===");
    let p1 = Point{
        x: 3,
        y: 4
    };
    p1.display();

    let p2 = Point{
        x: 3.7,
        y: 4.2
    };
    p2.display();

    println!("\n=== Generic Enum ===");
    let ipv4 = IPVal::V4("127.0.0.1");
    use_enum(ipv4);
    let ipv6 = IPVal::V6("0:0:0:0:0:0:0:1");
    use_enum(ipv6);

    let ipv4 = IPVal::V4(127.01);
    use_enum(ipv4);
    
    let ipv6 = IPVal::V6(255);
    use_enum(ipv6);

}

/*****
    END OF FILE
**********/


