/*****

References
	https://doc.rust-lang.org/book/ch05-02-example-structs.html
	https://doc.rust-lang.org/rust-by-example/custom_types/structs.html

Three types of structures:

    1. Tuple structs, which are, basically, named tuples.
    2. The classic C structs
    3. Unit structs, which are field-less, are useful for generics.

Print Structs 
    Rust does include functionality to print out debugging information
    
    #[derive(Debug)]
        add #[derive(Debug)] just before the struct definition

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

#[derive(Debug)]
struct Pair(i32, i32);

#[derive(Debug)]
struct Unit;

fn main() {

    println!("=== Defining and Instantiating Structs ===");
    let user = User {
        name: String::from("User-1"),
        age: 18,
        department: dbg!(String::from("CSE"))
    };
    println!("user.name: {}, user.age: {}, user.department: {}",
                user.name, user.age, user.department);

    let pair = Pair(5, 7);
    println!("pair.0: {} pair.1: {}", pair.0, pair.1);

    let unit = Unit;
    //println!("unit {}", unit); 
    
    println!();

    println!("=== Print struct using {{:?}} ===");
    println!("{:?}", user);
    println!("{:?}", pair);
    println!("{:?}", unit);
    println!();

    println!("=== Print struct using {{:#?}} ===");
    println!("{:#?}", user);
    println!("{:#?}", pair);
    println!("{:#?}", unit);
    println!();

    println!("=== Print using dbg! macro ===");     // prints on stderr
    dbg!(&user);
    dbg!(&pair);
    dbg!(&unit);


    println!("=== Destructure ===");
    let User { name, age, department: dep  } = user;
    println!("name {name} age {age} department {dep}");

    let Pair(f, s) = pair;
    println!("first {f} second {s}");

}

/*****
    END OF FILE
**********/


