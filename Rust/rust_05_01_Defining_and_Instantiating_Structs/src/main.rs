/*****

References
	https://doc.rust-lang.org/book/ch05-01-defining-structs.html
	https://doc.rust-lang.org/rust-by-example/custom_types/structs.html

Defining and Instantiating Structs

	struct or structure
		a custom data type  
		to put together and name multiple related values
		like tuple, data of a struct can be different types
		unlike tuple, we can name each data item
		
		structs are more flexible than tuples
		don’t have to rely on the order of the data to specify or access the values of an instance


    Three types of structures:

        1. Tuple structs, which are, basically, named tuples.
        2. The classic C structs
        3. Unit structs, which are field-less, are useful for generics.


	Defining a struct
		use keyword struct followed by struct name
		fields: Then, inside curly brackets, we define the names and types of the pieces of data, which we call fields
		Example

		struct User {
			name:	String,
			age:	u8
		}

	Using a struct
		use struct name and then add curly brackets containing key(names of the fields): value pairs
		order of fields does not matter
		
	Accessing a field value
		use instance followed by . and field name
		
	Updating a filed value
		use mutable instance
		access fileld and assign it different value
		
		NOTE: the entire instance must be mutable
		Rust doesn’t allow us to mark only certain fields as mutable
		
	Returning a struct instance
		construct a new instance of the struct as the last expression in the function body to implicitly return that new instance
	

Using the Field Init Shorthand
	in field init shorthand syntax, if we have a variable with the same name as filed
	we use the variable name direclty to intialize the filed value

	
Creating Instances with Struct Update Syntax
	syntax .. specifies that the remaining fields not explicitly set should have the same value as the fields in the given instance
	syntax .. must be at last
	
	NOTE:
	the struct update syntax uses = like an assignment; this is because it moves the data


Tuple structs
	A struct with struct name and only filed type
	don’t have names associated with their fields
	
	Used to give the whole tuple a name and make the tuple a different type from other tuples
	Example
	struct Color(i32, i32, i32);
	struct Point(i32, i32, i32);
	
	Here Color and Point are two different types
	
Unit-Like Structs Without Any Fields
	unit-like structs - structs that don’t have any fields
	they behave similarly to (), the unit type
	
	To define use struct keyword, the name we want, and then a semicolon. 
	No need for curly brackets or parentheses
	
	Used to implement a trait on some type but don’t have any data that you want to store in the type itself


NOTE
    It’s also possible for structs to store references to data owned by something else, but to do so requires the use of lifetimes, 
    a Rust feature that we’ll discuss in Chapter 10

**********/

struct User {
    // we can not have mutable filed

    name:   String,
    age:    u8,
    department: String
}

fn get_user(user_name: String, age: u8, department: String) -> User {
    User {
        name:   user_name,
        age:    age,
        department
    }
}

fn use_user(user: &User) {
    println!("user.name: {}, user.age: {}, user.department: {}",
                user.name, user.age, user.department);   
}

/*  
struct UserWithRef {
    name:   &str,   // CE error[E0106]: missing lifetime specifier
    age:    u8,
    department: String
}
*/

fn main() {

    println!("=== Defining and Instantiating Structs ===");
    let user_1 = User {
        name: String::from("User-1"),
        age: 18,
        department: String::from("CSE")
    };

    println!("user_1.name: {}, user_1.age: {}, user_1.department: {}",
                user_1.name, user_1.age, user_1.department);

    // CE error[E0594]: cannot assign to `user_1.age`, as `user_1` is not declared as mutable
    //user_1.age = 20;

    let mut user_2 = User {
        name: String::from("User-2"),
        age: 19,
        department: String::from("ECE")
    };

    println!("user_2.name: {}, user_2.age: {}, user_2.department: {}",
                user_2.name, user_2.age, user_2.department);

    user_2.age = 21;
    println!("user_2.name: {}, user_2.age: {}, user_2.department: {}",
                user_2.name, user_2.age, user_2.department);
    println!();


    println!("===  Using the Field Init Shorthand ===");

    let user_3 = get_user(String::from("User-3"), 17, String::from("EEE"));
    println!("user_3.name: {}, user_3.age: {}, user_3.department: {}",
                user_3.name, user_3.age, user_3.department);

    use_user(&user_3);
    
    let name    = String::from("User-4");
    let age     = 21;
    let department  = String::from("Civil");

    println!("name {name}, age {age}, department {department}");

    let user_4 = User{name, age, department};
    println!("user_4.name: {}, user_4.age: {}, user_4.department: {}",
                user_4.name, user_4.age, user_4.department);

    // CE ownership of name, age, department has been moved to user_4
    //println!("name {name}, age {age}, department {department}");
    println!();


    println!("=== Creating Instances from Other Instances with Struct Update Syntax ===");
    {
        let user = User {
            name: String::from("Rust"),
            age: 10,
            department: String::from("Programming")
        };
        println!("user.name: {}, user.age: {}, user.department: {}",
                    user.name, user.age, user.department);

        let copy_user = User {
            name:       user.name,
            age:        user.age,
            department: user.department
        };
        println!("copy_user.name: {}, copy_user.age: {}, copy_user.department: {}",
                    copy_user.name, copy_user.age, copy_user.department);
        // can not user user's moved value                    
        //println!("user.name: {}, user.age: {}, user.department: {}",
        //            user.name, user.age, user.department);
        println!("user.age: {} ", user.age);

    }
    {
        let user = User {
            name: String::from("Rust"),
            age: 10,
            department: String::from("Programming")
        };
        println!("user.name: {}, user.age: {}, user.department: {}",
                    user.name, user.age, user.department);

        let copy_user = User {
            name:   String::from("New User"),
            .. user
        };
        println!("copy_user.name: {}, copy_user.age: {}, copy_user.department: {}",
                    copy_user.name, copy_user.age, copy_user.department);
    }
    {
        let user = User {
            name: String::from("Rust"),
            age: 10,
            department: String::from("Programming")
        };
        println!("user.name: {}, user.age: {}, user.department: {}",
                    user.name, user.age, user.department);

        let copy_user = User { .. user };
        println!("copy_user.name: {}, copy_user.age: {}, copy_user.department: {}",
                    copy_user.name, copy_user.age, copy_user.department);                    
    }
    println!();


    println!("=== Using Tuple Structs Without Named Fields to Create Different Types ===");
    
    struct Color(u8, u8, u8);
    struct Point3d(u16, u16, u16);

    let mut red = Color(1, 0, 0);
    let black = Color(0, 0, 1);
    println!("Red color {} {} {}", red.0, red.1, red.2);
    println!("Black color {} {} {}", black.0, black.1, black.2);

    let line_o = Point3d(0, 1, 2);
    let line_e = Point3d(9, 8, 7);
    println!("Line origin ({} {} {}) end ({} {} {})", 
                line_o.0, line_o.1, line_o.2,
                line_e.0, line_e.1, line_e.2);

    red = black;
    println!("Red color {} {} {}", red.0, red.1, red.2);

    // CE error[E0308]: mismatched types
    //red = line_o;
    println!();
    

    println!("=== Unit-Like Structs Without Any Fields ===");
    struct NoDepartment;
    let department = NoDepartment;
}

/*****
    END OF FILE
**********/


