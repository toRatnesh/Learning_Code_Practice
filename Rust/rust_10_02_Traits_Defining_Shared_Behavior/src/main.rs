/*****

References
    https://doc.rust-lang.org/book/ch10-02-traits.html
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


Traits: Defining Shared Behavior
	A trait defines functionality a particular type has and can share with other types.
	can use traits to define shared behavior in an abstract way
	can use trait bounds to specify that a generic type can be any type that has certain behavior


Defining a Trait
	Trait definitions are a way to group method signatures together to define a set of behaviors necessary to accomplish some purpose.
	
	To declare a trait use the trait keyword and then the trait’s name
	Inside the curly brackets, we declare the method signatures that describe the behaviors of the types that implement this trait
	Each type implementing this trait must provide its own custom behavior for the body of the method
	
	pub trait TraitName {
		fn method_name(&self) -> ReturnType;
	}
	
	A trait can have multiple methods in its body: the method signatures are listed one per line and each line ends in a semicolon.
	Declare the trait as pub so that crates depending on this crate can make use of this trait too


Implementing a Trait on a Type
	After impl, we put the trait name, then use the for keyword, and then specify the name of the type we want to implement the trait for
	Within the impl block, define method signatures with the specific behavior that the trait definition has declared
	
	impl TraitName for ConcreteType {
		fn method_name(&self) -> ReturnType {
			// behavior logic
		}
	}
	
	NOTE: we can implement a trait on a type only if at least one of the trait or the type is local to our crate
	
	Coherence or Orphan rule
	We can’t implement external traits on external types
	This restriction is part of a property called coherence, and more specifically the orphan rule, so named because the parent type is not present
	This rule ensures that other people’s code can’t break your code and vice versa
	
	Without this rule, two crates could implement the same trait for the same type, and Rust wouldn’t know which implementation to use.


Default Implementations
	We may provide default implementation for some or all of the methods in a trait
	Then, as we implement the trait on a particular type, we can keep or override each method’s default behavior
	
	pub trait TraitName {
		fn method_name(&self) -> ReturnType {
			// behavior logic
		}
	}	
	
	To use a default implementation , we specify an empty impl block
	
	The syntax for overriding a default implementation is the same as the syntax for implementing a trait method that doesn’t have a default implementation
	
	Default implementations can call other methods in the same trait, even if those other methods don’t have a default implementation
	
	NOTE
	It isn’t possible to call the default implementation from an overriding implementation of that same method


Traits as Parameters
	Instead of a concrete type for the item parameter, we specify the impl keyword and the trait name
	This parameter accepts any type that implements the specified trait

	fn function_name(parm: & impl TraitName) {
		// code logic using trait method
	}


Trait Bound Syntax
	The impl Trait syntax is actually syntax sugar for a longer form known as a trait bound
	
	fn function_name<T: TraitName>(parm: &T) {
		// code logic using trait method
	}	
	
	We place trait bounds with the declaration of the generic type parameter after a colon and inside angle brackets
	
	Use following if we want this function to allow item1 and item2 to have different types (as long as both types implement TraitName)
	pub fn function_name(item1: &impl TraitName, item2: &impl TraitName) { }
	
	Use following If we want to force both parameters to have the same type
	pub fn function_name<T: TraitName>(item1: &T, item2: &T) { }
	
	
Specifying Multiple Trait Bounds with the + Syntax
	To specify more than one trait bound using the + syntax:

	impl Trait
	pub fn function_name(item: &(impl TraitName + Display)) { }
	
	Generic type
	pub fn function_name<T: TraitName + Display>(item: &T) { }
	
	
Clearer Trait Bounds with where Clauses
	To handle multiple generic type parameters that contain lots of trait bound information
	Rust has alternate syntax for specifying trait bounds inside a where clause after the function signature
	
	// without where clause
	fn some_function<T: Display + Clone, U: Clone + Debug>(t: &T, u: &U) -> i32 { }
	
	// with where clause
	fn some_function<T, U>(t: &T, u: &U) -> i32
	where
		T: Display + Clone,
		U: Clone + Debug,
	{ }


Returning Types that Implement Traits
	can use the impl Trait syntax in the return position to return a value of some type that implements a trait
	can only use impl Trait to return a single type
	
	useful in the context of closures and iterators
	Closures and iterators create types that only the compiler knows or types that are very long to specify 


Using Trait Bounds to Conditionally Implement Methods
	By using a trait bound with an impl block that uses generic type parameters, we can implement methods conditionally for types that implement the specified traits
	
	We can also conditionally implement a trait for any type that implements another trait.
	Implementations of a trait on any type that satisfies the trait bounds are called blanket implementations
	
**********/


// Default definition for a Trait
trait MyDisplay {
    fn my_display(&self) {
        println!("This is default implementation for MyDisplay::display() trait");
    }
}

// Defining a Trait
trait MyStringTrait {
    fn concat_self(&self) -> String;
}

struct StrData {
    data:   String
}

impl StrData {
    fn get_data(&self) -> String {
        self.data.clone()
    }
}

struct IData {
    data: u64
}

// Implementing a Trait on a Type
impl MyStringTrait for StrData {
    fn concat_self(&self) -> String {
        let res = self.get_data() + " " + &self.get_data();
        res
    }
}

// Default implementations for a Trait
impl MyDisplay for StrData { 

}

impl IData {
    fn get(&self) -> u64 {
        self.data
    }
}

// Override Default implementations for a Trait
impl MyDisplay for IData { 
    fn my_display(&self) {
        println!("data {}", self.get());
    }
}

// Traits as Parameters
fn fun_with_my_display_trait(val : &impl MyDisplay) {
    val.my_display();
}

// Trait Bound Syntax
fn fun_with_my_display_trait_bound<T: MyDisplay>(val : &T) {
    val.my_display();
}

// Specifying Multiple Trait Bounds with the + Syntax
fn fun_with_multiple_trait(val : &(impl MyDisplay + MyStringTrait)) {
    val.my_display();
    //let res_str = val.concat_self();
    println!("val.concat_self() {}", val.concat_self());
}

fn fun_with_multiple_trait_bound<T: MyDisplay + MyStringTrait>(val : &T) {
    val.my_display();
    //let res_str = val.concat_self();
    println!("val.concat_self() {}", val.concat_self());
}

// Clearer Trait Bounds with where Clauses
fn fun_trait_with_where_clause<T>(val : &T) 
where 
    T: MyDisplay + MyStringTrait,
{
    val.my_display();
    //let res_str = val.concat_self();
    println!("val.concat_self() {}", val.concat_self());
}

// Returning Types that Implement Traits
fn fun_ret_trait_idata() -> impl MyDisplay {
    let ret = IData {
        data: 124
    };
    ret
}

fn fun_ret_trait_strdata() -> impl MyDisplay {
    let ret = StrData {
        data: String::from("sample string data")
    };
    ret
}

fn fun_ret_trait_can_not_return_multiple_type(flag: bool) -> impl MyDisplay {

        let ret = IData {
            data: 124
        };
        ret

    // error[E0308]: `if` and `else` have incompatible types
    /*
    if true == flag {
        let ret = IData {
            data: 124
        };
        ret
    } else {
        let ret = StrData {
            data: String::from("sample string data")
        };
        ret          
    }
    */
}

// Using Trait Bounds to Conditionally Implement Methods
struct UseType<T> {
    x: T,
    y: T
}

impl<T> UseType<T> {
    fn new(x: T, y: T) -> Self {
        Self{x, y}
    }
}

impl<T: MyDisplay> UseType<T> {
    fn display(&self) {
        self.x.my_display();
        self.y.my_display();
    }
}

fn main() {

    println!("=== Defining a Trait ===");
    let data = StrData {
        data: String::from("sample data")
    };

    let idata = IData {
        data: 34
    };

    println!("data.get_data() {}", data.get_data());
    println!("data.concat_self() {}", data.concat_self());

    // error[E0599]: no method named `concat_self` found for struct `IData` in the current scope
    // println!("idata.concat_self() {}", idata.concat_self());

    
    println!("\n=== Default Implementations ===");
    print!("data.my_display() "); data.my_display();
    print!("idata.my_display() "); idata.my_display();


    println!("\n=== Traits as Parameters ===");
    fun_with_my_display_trait(&data);
    fun_with_my_display_trait(&idata);

    println!("\n=== Trait Bound Syntax ===");
    fun_with_my_display_trait_bound(&data);
    fun_with_my_display_trait_bound(&idata);


    println!("\n=== Specifying Multiple Trait Bounds with the + Syntax ===");
    fun_with_multiple_trait_bound(&data);
    // error[E0277]: the trait bound `IData: MyStringTrait` is not satisfied
    // fun_with_multiple_trait_bound(&idata);

    fun_with_multiple_trait(&data);
    // error[E0277]: the trait bound `IData: MyStringTrait` is not satisfied
    // fun_with_multiple_trait_bound(&idata);

    println!("\n=== Clearer Trait Bounds with where Clauses ===");
    fun_trait_with_where_clause(&data);
    // error[E0277]: the trait bound `IData: MyStringTrait` is not satisfied
    // fun_trait_with_where_clause(&idata);

    fun_trait_with_where_clause(&data);
    // error[E0277]: the trait bound `IData: MyStringTrait` is not satisfied
    // fun_trait_with_where_clause(&idata);


    println!("\n=== Returning Types that Implement Traits ===");
    let ret = fun_ret_trait_idata();
    ret.my_display();
    let ret = fun_ret_trait_strdata();
    ret.my_display();

    println!("\n=== Using Trait Bounds to Conditionally Implement Methods ===");
    let val1 = StrData{
        data: String::from("data-1")
    };
    let val2 = StrData{
        data: String::from("data-2")
    };
    let ut_val = UseType {
        x: val1,
        y: val2
    };
    ut_val.display();

    let val1 = IData{
        data: 23
    };
    let val2 = IData{
        data: 24
    };
    let ut_val = UseType {
        x: val1,
        y: val2
    };
    ut_val.display();

}

/*****
    END OF FILE
**********/


