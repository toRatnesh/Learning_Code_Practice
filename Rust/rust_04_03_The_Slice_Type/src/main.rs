/*****

References
    https://doc.rust-lang.org/book/ch04-03-slices.html

The Slice Type

    Slices let you reference a contiguous sequence of elements in a collection rather than the whole collection. 
    A slice is a kind of reference, so it does not have ownership.

String Slices

    A string slice is a reference to part of a String, and it looks like this:
        let s = String::from("hello world");

        let hello = &s[0..5];
        let world = &s[6..11];

    hello is a reference to a portion of the String, specified in the extra [0..5] bit

    We create slices using a range within brackets by specifying 
    [starting_index..ending_index]
    starting_index: first position in the slice
    ending_index:   one more than the last position in the slice

    Internally, the slice data structure stores the starting position and the length of the slice, 
    length = ending_index - starting_index

    Rust’s .. range syntax,
    to start at index 0, you can drop the value before the two periods
    let slice = &s[0..2];
    let slice = &s[..2];

    to end at last index, you can drop the trailing number
    let slice = &s[3..len];
    let slice = &s[3..];

    You can also drop both values to take a slice of the entire string
    let slice = &s[0..len];
    let slice = &s[..];

    NOTE:
    String slice range indices must occur at valid UTF-8 character boundaries. 
    If you attempt to create a string slice in the middle of a multibyte character, your program will exit with an error.

    &str    represents string slice
    &str    is an immutable reference
    
String Literals as Slices

    let s = "Hello, world!";
    The type of s here is &str: 
        it’s a slice pointing to that specific point of the binary.
    This is also why string literals are immutable

String Slices as Parameters

    You can take slice as parameters
    &str will be a better choice than &String as parameter
    because it allows us to use the same function on both &String values and &str values

Other Slices

    Similar to string slices, we can take slices of other collections

**********/

fn main() {

    println!("=== String Slices ===");

    let sval = String::from("Learning Rust Slice Type");
    let word_1 = &sval[..9];
    let word_2 = &sval[9..13];
    let word_3 = &sval[14..];

    println!("String value sval: {sval}");
    println!("Strig slice &sval[..9]: {word_2}");
    println!("Strig slice &sval[9..13]: {word_1}");
    println!("Strig slice &sval[14..]: {word_3}");

    let ret_val = get_first_word(&sval);
    println!("get_first_word(&sval) {ret_val}");
    println!();


    
    println!("=== String Literals as Slices ===");

    let slit = "This is a string literal";
    println!("String literal value: {slit}");
    
    // CE error[E0384]: cannot assign twice to immutable variable `slit`
    //slit = "Can not midify string literal value";
    println!();


    println!("=== String Slices as Parameters ===");

    let aslice  = "This a string literal which is an immutable slice";
    let astr    = String::from("This is a string value");

    println!();
    println!("--- Passing to string slice ---");

    string_slice_as_parameter(aslice);
    string_slice_as_parameter(&aslice);
    string_slice_as_parameter(&aslice[..22]);

    //string_slice_as_parameter(astr);      // error[E0308]: mismatched types
    string_slice_as_parameter(&astr);
    string_slice_as_parameter(&astr[10..]);

    println!();
    println!("--- Passing to string reference ---");
    println!("Can not pass string slice to string reference parameter");
    //string_as_ref_parameter(aslice);          // error[E0308]: mismatched types
    //string_as_ref_parameter(&aslice);         // error[E0308]: mismatched types
    //string_as_ref_parameter(&aslice[0..4]);   // error[E0308]: mismatched types


    //string_as_ref_parameter(astr);            // error[E0308]: mismatched types
    string_as_ref_parameter(&astr);
    //string_as_ref_parameter(&astr[0..4]);     // error[E0308]: mismatched types
    println!();

    println!("=== Other Slices ===");

    let arr = [1, 2, 3, 4, 5, 6, 7, 8, 9];
    let arr_slice = &arr[2..5];
    println!("Array slice :");

    for elem in arr_slice {
        println!("{elem}");
    }

}

fn get_first_word(sval: &String) -> &str {
    let l_bytes = sval.as_bytes();

    for(i, &item) in l_bytes.iter().enumerate() {
        if b' ' == item {
            return &sval[0..i];
        }
    }
    &sval[..]
}

fn string_slice_as_parameter(aslice : &str) {
    println!("{}", aslice);
}

fn string_as_ref_parameter(astr : &String) {
    println!("{}", astr);
}

/*****
    END OF FILE
**********/


