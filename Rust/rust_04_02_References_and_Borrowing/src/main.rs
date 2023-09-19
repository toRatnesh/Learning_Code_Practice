/*****

References
    https://doc.rust-lang.org/book/ch04-02-references-and-borrowing.html

References and Borrowing

    To pass a value without transferig ownership use reference

Reference

    A reference is like a pointer in that it’s an address we can follow to access the data stored at that address; that data is owned by some other variable. 
    Unlike a pointer, a reference is guaranteed to point to a valid value of a particular type for the life of that reference.
    '&' represent references, and they allow you to refer to some value without taking ownership of it
    
    Because a reference does not own the value, the value it points to will not be dropped when the reference stops being used.
    For reference parameter we does not need to return the value to give back ownership, because we never had ownership

    NOTE:
    The opposite of referencing is dereferencing, dereference operator * is used for dereferencing

Borrowing

    action of creating a reference is known as borrowing
    we can not change a reference value

Mutable References

    To allow a reference to modify the referenced value, use mutable reference
    for mutable reference use '&mut' in both argument and parameter

    Restriction: if you have a mutable reference to a value, you can not have other references to that value.

    Restriction Advantage:
    Rust can prevent data races at compile time. 
    A data race is similar to a race condition and happens when these three behaviors occur:

        1. Two or more pointers access the same data at the same time.
        2. At least one of the pointers is being used to write to the data.
        3. There’s no mechanism being used to synchronize access to the data.

    We also cannot have a mutable reference while we have an immutable one to the same value.
    However, multiple immutable references are allowed because no one can change data

    ** Reference’s scope starts from where it is introduced and continues through the last time that reference is used

Dangling References

    In Rust, by contrast, the compiler guarantees that references will never be dangling references: 
    if you have a reference to some data, the compiler will ensure that the data will not go out of scope before the reference to the data does.


**********/

fn main() {

    println!("=== Reference ===");

    let sval = String::from("Learning Reference");

    let len = calculate_len_with_reference(&sval);  // & is used to pass reference
    println!("The length of '{sval}' is {len}");

    change_reference(&sval);

    let len = calculate_len_with_ownership(sval);
    //println!("The length of '{sval}' is {len}");  // CE error[E0382]: borrow of moved value: `sval`

    println!();
    println!("=== Mutable Reference ===");

    let mut sval = String::from("Pass this value as mutable Reference");
    println!("value before passing as mutable refernce: {sval}");

    change_mutable_reference(&mut sval); 
    println!("value after passing as mutable refernce: {sval}");
    println!();

    {
        // after an immutable rerefence can not have a mutable any reference
        let r1 = &sval;
        let r2 = &sval;
        
        println!("Reference value-1: {r1}");
        println!("Reference value-2: {r2}");

        let mr = &mut sval;
        println!("Mutable reference value: {mr}");
        //println!("Reference value-2: {r2}");        // can not use immutable reference
        println!();
    }

    {
        // after a mutable reference, can not have any other reference
        let mr1 = &mut sval;
        println!("Mutable reference value: {mr1}");

        let mr2  = &mut sval;
        println!("Mutable reference value: {mr2}");
        //println!("Mutable reference value: {mr1}");   // can not use another reference

        let sref = &sval;
        println!("Reference value: {sref}");
        //println!("Mutable reference value: {mr2}");   // can not use another reference
    }

    println!();
    println!("=== Dangling Reference ===");

    //let dang_ref = get_dangling_reference();

}

fn calculate_len_with_reference(s: &String) -> usize {   // & is used to take parm by reference
    println!("Referenece parm value: {s}");
    s.len()
}

fn calculate_len_with_ownership(s: String) -> usize {
    s.len()
}

fn change_reference(s: &String) {
    // error[E0596]: cannot borrow `*s` as mutable, as it is behind a `&` reference
    //s.push_str("we can not change reference value, it will result in compilation error");
    println!("Can not modify refernce value: '{s}'");
}

fn change_mutable_reference(s: &mut String) {
    s.clear();
    s.push_str(" modified mutable reference value");
}

/*
fn get_dangling_reference() -> &String {
    let s = String::from("This data will be deallocated at the end of the function scope");
    &s  // returning reference to data which will be deallocated after this scope
}
*/

/*****
    END OF FILE
**********/


