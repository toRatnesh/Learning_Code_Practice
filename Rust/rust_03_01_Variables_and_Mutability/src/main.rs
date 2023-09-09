/***********

    References
        https://doc.rust-lang.org/book/ch03-00-common-programming-concepts.html

    1. Variables and Mutability
	    immutable: by default, variables are immutable
	    mutable: use mut in front of the variable name to make them mutable

    2. Constants
        constants are values that are bound to a name and are not allowed to change
        can not use mut with constants
        constants are always immutable
        to declare constants use the const keyword, and the type of the value
        constants may be set only to a constant expression, not the result of a value that could only be computed at runtime
        naming convention for constants is to use all uppercase with underscores between words

    3. Shadowing
        you can declare a new variable with the same name as a previous variable
        the first variable is shadowed by the second
        it happens when using the same variable’s name and repeating the use of the let keyword
        using shadowing we can change the type of the value but reuse the same name


 * *************/

fn main() {
    
    // 1. mutable and immutable variable
    println!("=== mutable and immutable varibale ===");
	let immutable_variable = 3;
	let mut mutable_variable = 6;
	println!("immutable_variable {immutable_variable} mutable_variable {mutable_variable}");

	//immutable_variable = 4;    // CE: cannot assign twice to immutable variable `immutable_variable`
	mutable_variable = 7;
	println!("immutable_variable {immutable_variable} mutable_variable {mutable_variable}");
	println!();


	// 2. const variable
	println!("=== const variable ===");
	const SECONDS_IN_A_DAY: u32 = 24*60*60;
	println!("const varible SECONDS_IN_A_DAY {SECONDS_IN_A_DAY}");
	println!();


	// 3. shadowing
	println!("=== varibale shadowing ===");
	let shadow_variable = "Learning Rust";
	println!("shadow_variable {shadow_variable}");
	let shadow_variable = shadow_variable.len();
	println!("shadow_variable {shadow_variable}");

	let shadow_variable = 5;
	println!("shadow_variable {shadow_variable}");
	let shadow_variable = shadow_variable * 3;
	println!("shadow_variable {shadow_variable}");
	{
		let shadow_variable = shadow_variable + 100;
	    println!("Different scope shadow_variable {shadow_variable}");
	}
	println!("shadow_variable {shadow_variable}");

}


/***********
 *  END OF FILE
 * *************/

