/*****

References
    https://doc.rust-lang.org/book/ch03-04-comments.html
    https://doc.rust-lang.org/rust-by-example/hello/comment.html

Comments

Single line comment

    single line comment is written using '//'
    this can start anywhere in the line and will follow till the end of the line from that point

Multi line comment
    Mutiline commnet is enclosed in /* */
    Its scope starts with '/*' and ends with '*/'

Documentation comment

    Documentation comments use three slashes, ///, instead of two and support Markdown notation for formatting the text. 
    Place documentation comments just before the item they’re documenting.

    /// Adds one to the number given.
    ///
    /// # Examples
    ///
    /// ```
    /// let arg = 5;
    /// let answer = my_crate::add_one(arg);
    ///
    /// assert_eq!(6, answer);
    /// ```
    fn add_one(x: i32) -> i32 {
        x + 1
    }

**********/

/// Adds one to the number given.
///
/// # Examples
///
/// ```
/// let arg = 5;
/// let answer = my_crate::add_one(arg);
///
/// assert_eq!(6, answer);
/// ```
fn add_one(x: i32) -> i32 {
    x + 1
}


fn main() {

    println!("=== Single line comment ===");
    // single line comment is written in this way
    println!("// single line comment is written in this way");

    let x = 1; // single line comment can be written in this way also
    println!("value of x is {x}");
    println!("let x = 3; // single line comment can be written in this way also");
    println!();

    println!("=== Multi line comment ===");
    /*Mutline comment is written in this way  
        and it can be extended till 
        multiple line*/
    println!("/* Mutline comment is written in this way  
        and it can be extended till 
        multiple line */");

    let x /* comment can be present in this way also */ = 2;
    println!("value of x is {x}");
    println!("let x /* comment can be present in this way also */ = 3;");
    println!();

    println!("=== Documentation comment ===");
    println!("
        /// Adds one to the number given.
        ///
        /// # Examples
        ///
        /// ```
        /// let arg = 5;
        /// let answer = my_crate::add_one(arg);
        ///
        /// assert_eq!(6, answer);
        /// ```
        fn add_one(x: i32) -> i32 {{
            x + 1
        }}
    ");
    let x = add_one(x);
    println!("value of x is {x}");

}

/*****
    END OF FILE
**********/


