/*****

References
	https://doc.rust-lang.org/book/ch05-03-method-syntax.html
	https://doc.rust-lang.org/rust-by-example/custom_types/structs.html
	

Method Syntax
	Methods are similar to functions
	declare them with the fn keyword and a name
	they can have parameters and a return value
	
	Unlike functions, methods are defined within the context of a struct (or an enum or a trait object)
	first parameter is always self, which represents the instance of the struct the method is being called on
	
	to define a method start an impl (implementation) block for the struct
	Everything within this impl block will be associated with the the struct type
	
	a method can have same name as one of the struct’s fields
	Rust can differentiate between a filed and method based on ()
	
self, &self, &mut self

	Within an impl block, the type Self is an alias for the type that the impl block is for	
	Methods can take ownership of self, borrow self immutably or borrow self mutably
	
	&self is actually short for self: &Self
	use &mut self as the first parameter, If we wanted to change the instance that we’ve called the method on
	
	using just self as the first parameter is rare; this technique is usually used when the method transforms self into something else and you want to prevent the caller from using the original instance after the transformation
	
Calling Method
	use instance name follwoed by dot and method call like function call
	
	
Associated Functions
	All functions defined within an impl block are called associated functions because they’re associated with the type named after the impl. 
	
	We can define associated functions that don’t have self as their first parameter (and thus are not methods) because they don’t need an instance of the type to work with.	
	Example String::from()
	
	Associated functions that aren’t methods are often used for constructors that will return a new instance of the struct. 
	These are often called new, but new isn’t a special name and isn’t built into the language.
	
	To call this associated function, we use the :: syntax with the struct name
	
	The Self keywords in the return type and in the body of the function are aliases for the type that appears after the impl

Multiple impl Blocks
	Each struct is allowed to have multiple impl blocks.
	
	

NOTE
	Where’s the -> Operator?
	automatic referencing and dereferencing
	Rust doesn’t have an equivalent to the -> operator; instead, Rust has a feature called automatic referencing and dereferencing. 
	Calling methods is one of the few places in Rust that has this behavior.
	
	when you call a method with object.something(), Rust automatically adds in &, &mut, or * so object matches the signature of the method
	
	This automatic referencing behavior works because methods have a clear receiver—the type of self. 
	Given the receiver and name of a method, Rust can figure out definitively whether the method is reading (&self), mutating (&mut self), or consuming (self). 
	The fact that Rust makes borrowing implicit for method receivers is a big part of making ownership ergonomic in practice.

**********/

struct Rectangle {
    width: u32,
    height: u32,
}

impl Rectangle {
    fn area(&self) -> u32 {
        self.width * self.height
    }

    // Mehtods can have same name as fields
    fn width(&self) -> u32 {
        self.width
    }

    fn height(&self) -> u32 {
        self.height
    }
}
// Each struct is allowed to have multiple impl blocks
impl Rectangle {
    
    fn square(size: u32) -> Rectangle { // associated function
        Rectangle {
            width: size,
            height: size,
        }
    }

    fn can_hold(&self, other: &Rectangle) -> bool {
        self.width > other.width && self.height > other.height
    }
}

fn main() {
    let rect = Rectangle {
        width: 5,
        height: 7,
    };

    println!("=== Calling method ===");

    println!( "Rectangle width: {}, height: {}",
                rect.width(), rect.height());
    println!("Area of rectangle: {}", rect.area());                

    let rect1 = Rectangle { width: 30, height: 50 };
    let rect2 = Rectangle { width: 10, height: 40 };
    let rect3 = Rectangle { width: 60, height: 45 };

    println!("Can rect1 hold rect2? {}", rect1.can_hold(&rect2));
    println!("Can rect1 hold rect3? {}", rect1.can_hold(&rect3));
    println!();

    println!("=== Associated Functions ===");
    let sq = Rectangle::square(3);
    println!("Area of square: {}", sq.area());
}

/*****
    END OF FILE
**********/


