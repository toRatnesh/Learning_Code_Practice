/********
    8.1 Storing Lists of Values with Vectors

    References:
    https://doc.rust-lang.org/book/ch08-01-vectors.html

    Vector
    -> store multiple values
    -> type of each value should be same
    -> values are present next to each other in memory

    1. Creating a New Vector
    let v: Vec<i32> = Vec::new();
    type annotation is needed becaus we are not inserting any value, 
    so Rust does not know what kind of value we intend to store

    let v = vec![1, 2, 3];
    with initial values and Rust will infer the type of value you want
    the vec! macro, will create a new vector that holds the values you give it.

    2. Updating a Vector
    let mut v = Vec::new();
    v.push(5);
    The numbers we place inside are all of type i32, and Rust infers this from the data, so we don’t need the Vec<i32> annotation.

    3. Reading Elements of Vectors
    two ways to reference a value stored in a vector: 
        a)  via indexing
        b)  using the get method
    -> Using & and [] gives us a reference to the element at the index value. 
    -> When we use the get method with the index passed as an argument, we get an Option<&T> that we can use with match.
    -> When the program has a valid reference, the borrow checker enforces the ownership and borrowing rules 

    4. Iterating over the Values in a Vector
    iterate over immutable reference to get value or mutable references to get and update value
    Iterating over a vector, whether immutably or mutably, is safe because of the borrow checker's rules.
    If we attempted to insert or remove items in the for loop bodies, we would get a compiler error.
    The reference to the vector that the for loop holds prevents simultaneous modification of the whole vector.

    5. Using an Enum to Store Multiple Types
    We can define an enum whose variants will hold the different value types, and all the enum variants will be considered the same type: that of the enum.
    Then we can create a vector to hold that enum and so, ultimately, holds different types.

    6. Dropping a Vector Drops Its Elements
    When the vector gets dropped, all of its contents are also dropped, meaning the integers it holds will be cleaned up.
    The borrow checker ensures that any references to contents of a vector are only used while the vector itself is valid.

********/

pub fn main() {

    // 1. Creating a New Vector
    let _vempty: Vec<i32> = Vec::new();
    let _vinitz = vec![1, 2, 3];
    
    //let _vexp1 = vec![];  // error[E0282]: type annotations needed for `Vec<T>`
    let _vexp1: Vec<i32> = vec![];

    // 2. Updating a Vector
    let mut vec1 = Vec::new();
    vec1.push(5);
    vec1.push(66);
    vec1.push(777);
    //vec1.push(5.2);       // error[E0308]: mismatched types

    // 3. Reading Elements of Vectors
    let vec2 = vec![1, 2, 3, 4, 5];
    let elem1: &i32 = &vec2[2];
    println!("vector element at index {} is {}", 2, elem1);

    let elem2: Option<&i32> = vec2.get(2);
    match elem2 {
        Some(elem2) => println!("vector element at index {} is {}", 2, elem2),
        None => println!("No vector element at index {}", 2)
    }

    let index_does_not_exist = 10;
    //let elem21: &i32 = &vec2[index_does_not_exist]; // thread 'main' panicked at 'index out of bounds: the len is 5 but the index is 10', /app/example.rs:63:25
    
    let elem22: Option<&i32> = vec2.get(index_does_not_exist);
    match elem22 {
        Some(elem22) => println!("vector element at index {} is {}", index_does_not_exist, elem22),
        None => println!("No vector element at index {}", index_does_not_exist)
    }
    
    // you can’t have mutable and immutable references in the same scope
    let mut vec1 = vec![1,2,3,4,5];
    let first_elem = &vec1[0];
    //vec1.push(9);       // error[E0502]: cannot borrow `vec1` as mutable because it is also borrowed as immutable
    println!("The first element is: {}", first_elem);

    // 4. Iterating over the Values in a Vector
    println!("vector elemnets are: ");
    for val in &vec1 {
        print!("{} ", val);
    }
    println!("");

    for val in &mut vec1 {
        *val *= 2;
    }

    println!("vector elemnets are: ");
    for val in &vec1 {
        print!("{} ", val);
    }
    println!("");

    // 5. Using an Enum to Store Multiple Types
    enum SpreadsheetCell {
        Int(i32),
        Float(f64),
        Text(String),
    }
    let _row = vec![
        SpreadsheetCell::Int(3),
        SpreadsheetCell::Text(String::from("blue")),
        SpreadsheetCell::Float(10.12),
    ];

    // 6. Dropping a Vector Drops Its Elements
    {
        let _v = vec![1, 2, 3, 4];
        // do stuff with v
    } // <- v goes out of scope and is freed here
}

/******
	END OF FILE
******/