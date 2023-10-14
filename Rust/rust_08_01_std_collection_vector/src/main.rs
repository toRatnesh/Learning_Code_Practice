/*****

References
    https://doc.rust-lang.org/book/ch08-01-vectors.html
    https://doc.rust-lang.org/std/vec/struct.Vec.html
    https://doc.rust-lang.org/rust-by-example/std/vec.html
    
Common Collections
    collections:    a number of very useful data structures
    
    data these collections point to is stored on the heap

    Important Collections
        vector: store a variable number of values next to each other
        string: collection of characters
        hash map:   associate a value with a particular key ( particular implementation of map)


8.1 Storing Lists of Values with Vectors
    to store multiple value of same type
    values are stored next to each other

    A vector is represented using 3 parameters:
        1. pointer to the data
        2. length
        3. capacity

    capacity: memory is reserved for the vector
    The vector can grow as long as the length < capacity
    When this threshold needs to be surpassed, the vector is reallocated with a larger capacity.

Creating a New Vector
    empty vector
        let avec : Vec<i32> = Vec::new();
        need to add type because it can not be deduced in this case

    Non-empty vector
        let avec = vec![1, 2, 3];

        vec! macro, to create a new vector
        since we have provided value type can be deduced using value

Updating a Vector
    to update vector should be mutable
    
    push()
        to add elements to a vector

Reading Elements of Vectors
    using inddex []
        using & and [] gives us a reference to the element at the index value
        passing an index that is outside the vector will cause the program to panic


    using get()
        returns an Option<&T>
        passing an index that is outside the vector will return None without panicking

    When the program has a valid reference, the borrow checker enforces the ownership and borrowing rules 
    to ensure this reference and any other references to the contents of the vector remain valid.

Iterating over the Values in a Vector
    use a for loop to get immutable references to each element in a vector
    use mutable reference to make changes to all the elements

    If we attempted to insert or remove items in the for loop bodies, we would get a compiler error
    The reference to the vector that the for loop holds prevents simultaneous modification of the whole vector

Using an Enum to Store Multiple Types
    the variants of an enum are defined under the same enum type, 
    so when we need one type to represent elements of different types, 
    we can define and use an enum

    Using an enum plus a match expression means that Rust will ensure at compile time 
    that every possible case is handled

Dropping a Vector Drops Its Elements
    A vector is freed when it goes out of scope
    When the vector gets dropped, all of its contents are also dropped
    The borrow checker ensures that any references to contents of a vector are only used while the vector itself is valid


For all methods and details
    https://doc.rust-lang.org/std/vec/struct.Vec.html

**********/


enum UserData {
    Index(u32),
    UserName(String),
    Score(f32)
}

fn main() {
    println!("=== Creating a New Vector ===");
    {
        //let empty_vector = Vec::new();  // error[E0282]: type annotations needed for `Vec<T>`
        let empty_vector : Vec<i32> = Vec::new();
    }
    {
        let avec = vec![1, 2, 3];
    }  
    {
        let mut avec = Vec::new();
        avec.push(1);
    }

    println!("\n=== Updating a Vector ===");
    {
        let avec = vec![1, 2, 3];
        //avec.push(2);   // error[E0596]: cannot borrow `avec` as mutable, as it is not declared as mutable
    }
    {
        let mut avec = Vec::new();
        avec.push(1);
        avec.push(2);
    }         
    println!("\n=== Reading Elements of Vectors ===");
    {
        println!("accessing index within range");
        let avec = vec![1, 2, 3];
        let aval = &avec[2];
        println!("using [] value at index 2 is {aval}");

        let aval = avec.get(2);
        if let Option::Some(val) = aval {
            println!("using get() value at index 2 is {val}");
        } else {
            println!("using get() value at index 2 is None");
        }

        println!("\naccessing out of range index");
        let aval = avec.get(10);

        // use match to handle possible values
        match aval {
            Some(val)   => println!("using get() value at index 10 is {val}"),
            None        => println!("using get() value at index 10 is None")
        }

        // alternatively we may use if let also
        if let Option::Some(val) = aval {
            println!("using get() value at index 10 is {val}");
        } else {
            println!("using get() value at index 10 is None");
        }

        // RUN TIME ERROR 'main' panicked at 'index out of bounds: the len is 3 but the index is 10'
        // let aval = &avec[10];
    }

    println!("\n=== Iterating over the Values in a Vector ===");
    {
        let avec = vec![1, 2, 3];

        println!("immutable iterate");
        for val in &avec {
            print!("{val} ");
        }
        println!();
    }
    {
        let mut avec = vec![1, 2, 3];

        println!("mutable iterate");
        for val in &mut avec {
            *val *= 2;
        }

        for val in &avec {
            print!("{val} ");
        }
        println!();       
    }
    {
        let avec = vec![1, 2, 3];

        println!("iterating over vector");
        for val in avec.iter() {
            print!("{val} ");
        }
        println!();
    }    


    println!("\n=== Using an Enum to Store Multiple Types ===");
    {
        let avec: Vec<UserData> = vec![UserData::Index(1), UserData::UserName(String::from("User-01")), UserData::Score(71.67)];
        for val in &avec {
            match val {
                UserData::Index(val)      => println!("Index is {val}"),
                UserData::UserName(val)   => println!("User is {val}"),
                UserData::Score(val)      => println!("User score is {val}")
            }
        }
    }

    println!("\n=== Dropping a Vector Drops Its Elements ===");
    {
        let avec = vec![1, 2, 3];
    }   // vector is droped here after scope

    println!("\n=== Important vector methods ===");
    {
        let mut avec = vec![1, 2, 3, 4, 5];
        dbg!(avec.push(6));
        dbg!(avec.pop());

        dbg!(avec.insert(avec.len(), 6));
        dbg!(avec.remove(avec.len()-1));

        dbg!(avec.len());
        dbg!(avec.capacity());
        dbg!(avec.is_empty());

        dbg!(avec.clear());
        dbg!(avec.is_empty());

    }
}

/*****
    END OF FILE
**********/



