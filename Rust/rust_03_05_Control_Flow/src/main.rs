/*****

References
    https://doc.rust-lang.org/book/ch03-05-control-flow.html

Control Flow
    Control Flow is used to run a code when a condition is true
    or to repeat code exectuion while a condition is true

    if expressions and loop are used for control flow

if Expressions
    provide a condition and then state
    If the condition is met, run block of code. 
    If the condition is not met, do not run the block of code

    condition must be a bool

    All if expressions start with the keyword if, followed by a condition
    arms: Blocks of code associated with the conditions in if expressions are sometimes called arms, just like the arms in match expressions

    Optionally, we can also include an else expression, to give the program an alternative block of code to execute should the condition evaluate to false.

    If you don’t provide an else expression and the condition is false, the program will just skip the if block and move on to the next bit of code.

    Handling Multiple Conditions with else if
        use multiple conditions by combining if and else in an else if expression
        Using too many else if expressions can clutter your code, so if you have more than one, you might want to refactor your code

    Using if in a let Statement
        Because if is an expression, we can use it on the right side of a let statement to assign the outcome to a variable
        values that have the potential to be results from each arm of the if must be the same type

Repetition with Loops    
    Rust has three kinds of loops: loop, while, and for

    loop
        loop is used to execute a block of code over and over again forever or until you explicitly tell it to stop
        break is used to break out of a loop
        constinue is used to skip over any remaining code in this iteration of the loop and go to the next iteration

    Returning Values from Loops
        add the value you want returned after the break expression you use to stop the loop
        After the loop, we use a semicolon to end the statement that assigns the value to result
        Example
        let result = loop {
                counter += 1;
                if counter == 10 {
                    break counter * 2;
                }
            };

    Loop Labels to Disambiguate Between Multiple Loops
        If you have loops within loops, break and continue apply to the innermost loop at that point.
        You can optionally specify a loop label on a loop that you can then use with break or continue to specify that those keywords apply to the labeled loop instead of the innermost loop.
        Loop labels must begin with a single quote.

    Conditional Loops with while
        While the condition is true, the loop runs. When the condition ceases to be true, loop stops.
        It’s possible to implement behavior like this using a combination of loop, if, else, and break

    Looping Through a Collection with for
        for loop can be used to execute some code for each item in a collection
        The safety and conciseness of for loops make them the most commonly used loop construct in Rust.

**********/

fn main() {

    println!("=== if Expressions ===");
    let a = 8;
    let eo = a%2;

    if 0==eo {
        println!("{a} is even");
    }

    println!("=== if-else Expressions ===");
    let a = 7;
    let eo = a%2;
    if 0==eo {
        println!("{a} is even");
    } else {
        println!("{a} is odd");
    }

    println!("=== if-else if-else Expressions ===");
    let fruit = "orange";
    let rate;
    if "apple" == fruit {
        rate = 100;
    }
    else if "orange" == fruit {
        rate = 120;
    }
    else if "banana" == fruit {
        rate = 80;
    }
    else {
        rate = 0;
    }
    println!("{fruit} rate is {rate}");

    println!("=== if in let ===");
    let a = 3;
    let b = if 5==a {
            a * a
        } else {
            a * 2
            //"this will result in error" // CE error[E0308]: `if` and `else` have incompatible types
        };
    println!("value using if in let is {b}");
    println!();

    println!("=== loop ===");
    let mut a = 3;
    loop {
        println!("a is {a}");
        a = a-1;
        
        if 0==a {
            break;
        }
    }

    println!("=== Returning Values from Loops ===");
    let arr = [1,2,3,4,5,6,7,8,9,10];
    let mut itr = 0;
    let res = loop {
        itr += 1;
        if 7 == itr {
            break arr[itr];
        }
    };
    println!("value is {res}");

    println!("=== Loop Labels to Disambiguate Between Multiple Loops ===");
    let arr = [11,12,13,14,15,16,17,18,19,20,21,22];
    let mut i = 0;

    'row_loop : loop {
        let mut j = 0;

        'col_loop : loop {
            print!("{} ", arr[i+j]);
            j = j + 1;
            if 3 == j {
                break 'col_loop;
            }        
        }
        println!("");
        i = i + 3;
        if i >= 11 {
            break 'row_loop;
        }
    }

    println!("=== while loop ===");
    let mut a = 0;
    let mut b = 1;
    let mut new_num = a + b;

    println!("a {a} b {b} new_num {new_num}");
    while 17 >= new_num {
        a = b;
        b = new_num;
        new_num = a + b;

        println!("a {a} b {b} new_num {new_num}");
    }

    println!("=== for loop ===");
    let arr = [1,2,3,4,5,6,7,8,9,10];
    for elem in arr {
        print!("{elem} ");
    }
    println!();

}

/*****
    END OF FILE
**********/



