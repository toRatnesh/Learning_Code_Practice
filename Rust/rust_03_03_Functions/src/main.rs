/*****

References
    https://doc.rust-lang.org/book/ch03-03-how-functions-work.html

Functions

    to define function use fn keyword followed by a function name and a set of parentheses
    curly brackets are used for function body
    naming convention: snake case, all letters are lowercase and underscores separate words

    to call a function use its name followed by a set of parentheses

    Rust doesn’t care where you define your functions, only that they’re defined somewhere in a scope that can be seen by the caller

Function Parameters
    parameters, are special variables that are part of a function’s signature
    In function signatures, you must declare the type of each parameter
    for multiple parameters, separate the parameter declarations with commas

    to call a function with parameter use arguments inside parentheses 

Statements and Expressions

    Function bodies are made up of a series of statements optionally ending in an expression
    Statements are instructions that perform some action and do not return a value.
    Expressions evaluate to a resultant value. For example, 5 + 6, which is an expression that evaluates to the value 11
    
    Expressions do not include ending semicolons.
    If you add a semicolon to the end of an expression, you turn it into a statement, and it will then not return a value.

    Expressions can be part of statements
    Calling a function is an expression. 
    Calling a macro is an expression
    A new scope block created with curly brackets is an expression

Functions with Return Values
    for return values, declare their type after an arrow (->)
    return value of the function is synonymous with the value of the final expression in the block of the body of a function
    to return early from a function by use the return keyword and specify a value, but most functions return the last expression implicitly

**********/

fn fun_with_no_parm_no_ret() {
    let x = 10;
    println!("Inside function 'fun_with_no_parm_no_ret()' x value is {x}");
}

fn fun_with_parm_no_ret(x : i32) {
    println!("Inside function 'fun_with_parm_no_ret()' x value is {x}");
}

fn fun_with_parm_and_ret(x : i32) -> i32 {
    println!("Inside function 'fun_with_parm_and_ret()' x value is {x}");
    let y = x + 10;
    y
}

fn main() {

    println!("Inside main");
   
    println!("=== Statements and Expressions ===");

    //let y = { let x = 3 }; // CE error: expected one of `.`, `;`, `?`, `else`, or an operator, found `}`

    let y = { 
        let x = 3; 
        x 
    };
    println!("y is {y}");

    let p = 3;
    let q = fun_with_parm_and_ret(p);
    println!("q is {q}");

    println!("=== Functions ===");

    fun_with_no_parm_no_ret();
    
    fun_with_parm_no_ret(10);

    fun_with_parm_and_ret(25);


}

/*****
    END OF FILE
**********/


