/*****

References
    https://doc.rust-lang.org/book/ch04-01-what-is-ownership.html

What Is Ownership?
	set of rules to manage memory
	Rust uses a new approach called Ownership: memory is managed through a system of ownership with a set of rules that the compiler checks.
	If any of the rules are violated, the program won’t compile.
	None of the features of ownership will slow down your program while it’s running.

The Stack and the Heap
	Both the stack and the heap are parts of memory available to your code to use at runtime, but they are structured in different ways. 

	Stack
		The stack stores values in the order it gets them and removes the values in the opposite order. This is referred to as last in, first out.

	Heap
		The heap is less organized: when you put data on the heap, you request a certain amount of space. The memory allocator finds an empty spot in the heap that is big enough, marks it as being in use, and returns a pointer, which is the address of that location. This process is called allocating on the heap and is sometimes abbreviated as just allocating (pushing values onto the stack is not considered allocating).
		Because the pointer to the heap is a known, fixed size, you can store the pointer on the stack, but when you want the actual data, you must follow the pointer.
		Comparatively, allocating space on the heap requires more work because the allocator must first find a big enough space to hold the data and then perform bookkeeping to prepare for the next allocation.
		Accessing data in the heap is slower than accessing data on the stack because you have to follow a pointer to get there.

Ownership Rules

	Each value in Rust has an owner.
	There can only be one owner at a time.
	When the owner goes out of scope, the value will be dropped.

Variable Scope

	A scope is the range within a program for which an item is valid.
	Example

		fn main() {
			{                      // s is not valid here, it’s not yet declared
				let s = "hello";   // s is valid from this point forward

				// do stuff with s
			} // this scope is now over, and s is no longer valid
		}
	

The String Type
	To understand ownership concept we will use String type
	String uses heap memory and as such is able to store an amount of text that is unknown to us at compile time

Memory and Allocation

	To use String 
		The memory must be requested from the memory allocator at runtime.
		We need a way of returning this memory to the allocator when we’re done with our String.

	That first part is done by us: when we call String::from, its implementation requests the memory it needs.
	For second part, Rust takes a different path: the memory is automatically returned once the variable that owns it goes out of scope.
	
	Example
		fn main() {
			{
				let s = String::from("hello"); // s is valid from this point forward

				// do stuff with s
			} // this scope is now over, and s is no longer valid
		}	
	
	

	drop
		 When a variable goes out of scope, Rust calls a special function for us. 
		 This function is called drop, and it’s where the author of String can put the code to return the memory. 
		 Rust calls drop automatically at the closing curly bracket.

Variables and Data Interacting with Move

	Multiple variables can interact with the same data in different ways in Rust.
	Example
		let x = 5;
		let y = x;

	bind the value 5 to x; then make a copy of the value in x and bind it to y
	because integers are simple values with a known, fixed size, and these two 5 values are pushed onto the stack	


	String version:
		let s1 = String::from("hello");
		let s2 = s1;

	A String is made up of three parts, shown on the left: a pointer to the memory that holds the contents of the string, a length, and a capacity.
				s1
	-------------------------
	| name		|	value	|
	-------------------------
	| ptr		|			|
	-------------------------
	| len 		| 5			|
	-------------------------
	| capacity	|	5		|
	-------------------------

	When we assign s1 to s2, the String data is copied, meaning we copy the pointer, the length, and the capacity that are on the stack. We do not copy the data on the heap that the pointer refers to.  If Rust did this, the operation s2 = s1 could be very expensive in terms of runtime performance if the data on the heap were large.

	This is a problem: when s2 and s1 go out of scope, they will both try to free the same memory. This is known as a double free error and is one of the memory safety bugs we mentioned previously.

	To ensure memory safety, after the line let s2 = s1;, Rust considers s1 as no longer valid. Therefore, Rust doesn’t need to free anything when s1 goes out of scope.
	So operation, s2 = s1 is known as a move. In this example, we would say that s1 was moved into s2. 
	That solves our problem! With only s2 valid, when it goes out of scope it alone will free the memory.

	Rust will never automatically create “deep” copies of your data.


Variables and Data Interacting with Clone

	Clone is used for deep copy of heap data
	It could be an expensive operation
	Example
		let s1 = String::from("hello");
		let s2 = s1.clone();

		println!("s1 = {}, s2 = {}", s1, s2);

Stack-Only Data: Copy

	Consider Example
		let x = 5;
		let y = x;

		println!("x = {}, y = {}", x, y);
	
	we don’t have a call to clone, but x is still valid and wasn’t moved into y, How?
	Types such as integers that have a known size at compile time are stored entirely on the stack, so copies of the actual values are quick to make.

	Copy trait	
	Rust has a special annotation called the Copy trait that we can place on types that are stored on the stack, as integers are. If a type implements the Copy trait, variables that use it do not move, but rather are trivially copied, making them still valid after assignment to another variable.	

	Rust won’t let us annotate a type with Copy if the type, or any of its parts, has implemented the Drop trait.

	Types that implement Copy:

	->	All the integer types, such as u32.
	->	The Boolean type, bool, with values true and false.
	->	All the floating-point types, such as f64.
	->	The character type, char.
	->	Tuples, if they only contain types that also implement Copy. For example, (i32, i32) implements Copy, but (i32, String) does not.
		
Ownership and Functions
	The mechanics of passing a value to a function are similar to those when assigning a value to a variable.
	Passing a variable to a function will move or copy, just as assignment does.

Return Values and Scope
	Returning values can also transfer ownership.

**********/

fn heap_data_as_arg(heap_data : String) {   // takes ownersip of heap_data
    println!("heap_data inside function: {heap_data}");
} // msg scope ends here, and is freed using drop

fn stack_data_as_arg(stack_data : (u32, u32)) {
    let (e1, e2) = stack_data;
    println!("tuple elements inside function: {e1} {e2}");
}

fn get_value() -> String {
    let ret_val = String::from("Ownership of this will be transferred from function to callee of function");
    ret_val
}

fn pass_and_get_value(mut msg : String) -> (String, usize) {
    msg.push_str(" 1. taking ownersip 2. updating value 3. returning ownersip as return value");
    let l_len = msg.len();
    (msg, l_len)
}

fn main() {

    println!("=== Memory and Allocation ===");
    {
        let str_val = String::from("a string allocated on heap");   // str is allocated memory on heap
        println!("str_val {str_val}");
    }                      // this scope is now over, and memory of str is freed by calling drop
    println!();

    println!("=== Variables and Data Interacting with Move ===");
    {
        let data = 5;
        let copy_data = data;
        println!("data {data} copy_data {copy_data}");

        let data = String::from("Data allocated on heap is not be copied, its moved after assignment");
        println!("string data before assignment: {data}");

        let copy_data = data;
        //println!("string data after assignment: {data}");    // CE error[E0382]: borrow of moved value: `data`
        println!("new varibale after assignment, {copy_data}");
    }
    println!();

    println!("=== Variables and Data Interacting with Clone ===");
    {
        let str_val = "For deep copy use clone(), it may be expensive opeartion";
        println!("string value before clone: {str_val}");

        let clone_str_val = str_val.clone();
        println!("string value after clone: {str_val}");
        println!("cloned value: {clone_str_val}");
    }
    println!();

    println!("=== Stack-Only Data: Copy ===");
    {
        let data = 3;
        let copy_data = data;
        println!("data {data}, copy_data {copy_data}");
    }
    println!();

    println!("=== Ownership and Functions ===");
    {
        let str_data = String::from("a string allocated on heap");
        println!("heap data before passing to function: {str_data}");
        heap_data_as_arg(str_data);
        // CE error[E0382]: borrow of moved value: `str_data
        //println!("heap data after passing to function: {str_data}"); 
        println!();

        let tuple_val = (32, 56);
        let (e1, e2) = tuple_val;
        println!("tuple elements before passing to function: {e1} {e2}");
        stack_data_as_arg(tuple_val);
        let (e1, e2) = tuple_val;
        println!("tuple elements after passing to function: {e1} {e2}");
    }
    println!();

    println!("=== Return Values and Scope ===");
    {
        let ret_val = get_value();  // ownership is transferred to ret_val
        println!("Return value from function is: {ret_val}");
        println!();

        let str_val = String::from("Passing and getting ownership,");
        println!("Value before passing to function: {str_val}");

        // ownership of str_val is transferred to function, 
        // and ownership of retuerned value from fucntion is transferred back 
        let (msg, slen) = pass_and_get_value(str_val);
        
        // CE error[E0382]: borrow of moved value: `str_val`
        //println!("Value after passing to function: {str_val}");

        println!("value returned from function: {msg}");
        println!("length of string returned from function: {slen}");
    } // ret_val goes out of scope, memory is freed using drop

}

/*****
    END OF FILE
**********/


