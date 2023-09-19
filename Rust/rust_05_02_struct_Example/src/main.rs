/*****

References
	https://doc.rust-lang.org/book/ch05-02-example-structs.html
	https://doc.rust-lang.org/rust-by-example/custom_types/structs.html

Rust does include functionality to print out debugging information
    To do that, we add the outer attribute #[derive(Debug)] just before the struct definition

dbg! macro
    dbg! macro, which takes ownership of an expression (as opposed to println!, which takes a reference), 
    prints the file and line number of where that dbg! macro call occurs in your code 
    along with the resultant value of that expression, 
    and returns ownership of the value

**********/

#[derive(Debug)]
struct User {
    // we can not have mutable filed

    name:   String,
    age:    u8,
    department: String
}

fn main() {

    println!("=== Defining and Instantiating Structs ===");
    let user = User {
        name: String::from("User-1"),
        age: 18,
        department: dbg!(String::from("CSE"))
    };
    println!("user.name: {}, user.age: {}, user.department: {}",
                user.name, user.age, user.department);
    println!();

    println!("=== Print struct using {{:?}} ===");
    println!("{:?}", user);
    println!();

    println!("=== Print struct using {{:#?}} ===");
    println!("{:#?}", user);
    println!();

    println!("=== Print using dbg! macro ===");
    dbg!(&user);    // prints on stderr
    
}

/*****
    END OF FILE
**********/


