/*****

    References
        https://doc.rust-lang.org/book/ch03-02-data-types.html


    Rust is a statically typed language, which means that it must know the types of all variables at compile time

	Rust Data Types
        1. Scalar types:	integer, floating, boolean, character
        2. Compiund types:  tuple, array

    In cases when many types are possible, we must add a type annotation

    Integer Types in Rust
        ==================================
        Length      Signed      Unsigned
        ==================================
        8-bit       i8          u8
        16-bit      i16         u16
        32-bit      i32         u32
        64-bit      i64         u64
        128-bit     i128        u128
        arch        isize       usize
        ==================================

        Signed numbers are stored using two’s complement representation
        signed variant can store numbers from -(2^n - 1) to (2^n - 1) - 1 inclusive
        unsigned variants can store numbers from 0 to (2^n - 1)
        isize and usize types depend on the architecture of the computer

    Integer Literals in Rust
        ==================================
        Number literals     Example
        ==================================
        Decimal             98_222
        Hex                 0xff
        Octal               0o77
        Binary              0b1111_0000
        Byte (u8 only)      b'A'
        ==================================
        Number literals can also use _ as a visual separator to make the number easier to read

        integer types default to i32.
        The primary situation in which you’d use isize or usize is when indexing some sort of collection.

		To explicitly handle the possibility of overflow, you can use these families of methods provided by 
		the standard library for primitive numeric types:
			Wrap in all modes with the wrapping_* methods, such as wrapping_add.
			Return the None value if there is overflow with the checked_* methods.
			Return the value and a boolean indicating whether there was overflow with the overflowing_* methods.
			Saturate at the value’s minimum or maximum values with the saturating_* methods.


	Floating-Point Types
		f32 and f64, which are 32 bits and 64 bits in size, respectively
		default type is f64 because on modern CPUs, it’s roughly the same speed as f32 but is capable of more precision
		all floating-point types are signed
		
		Floating-point numbers are represented according to the IEEE-754 standard.
		The f32 type is a single-precision float, and f64 has double precision.

	Numeric Operations
		basic mathematical operations for all the number types: addition, subtraction, multiplication, division, and remainder
		Integer division truncates toward zero to the nearest integer
		
	The Boolean Type
		specified using bool
		two possible values: true and false
		one byte in size

	The Character Type
		specified using char
		specify char literals with single quotes
		char type is four bytes in size and represents a Unicode Scalar Value
		it can represent a lot more than just ASCII
		
		Accented letters; Chinese, Japanese, and Korean characters; emoji; and zero-width spaces are all valid char values in Rust
		Unicode Scalar Values range from U+0000 to U+D7FF and U+E000 to U+10FFFF inclusive
		
		However, a “character” isn’t really a concept in Unicode, 
		so your human intuition for what a “character” is may not match up with what a char is in Rust.
		For more detail refer Chapter-08
		
	The Tuple Type
		Grouping of a number of values with a variety of types into one compound type.
		Tuples have a fixed length: once declared, they cannot grow or shrink in size.

		We create a tuple by writing a comma-separated list of values inside parentheses. 
		Each position in the tuple has a type, and the types of the different values in the tuple don’t have to be the same.
		
		Destructuring: To get the individual values out of a tuple, we can use pattern matching to destructure a tuple value
		
		We can also access a tuple element directly by using a period (.) followed by the index of the value we want to access.
		
		unit
			The tuple without any values
			This value and its corresponding type are both written () and represent an empty value or an empty return type. 
			Expressions implicitly return the unit value if they don’t return any other value.
		
		
	The Array Type
		every element of an array must have the same type
		arrays in Rust have a fixed length
		the values in an array as a comma-separated list inside square brackets
		
		Arrays are useful when you want your data allocated on the stack rather than the heap
		to declare array use square brackets with the type of each element, a semicolon, and then the number of elements in the array
		let a: [i32; 5] = [1, 2, 3, 4, 5];
		
		You can also initialize an array to contain the same value for each element by specifying the initial value, 
			followed by a semicolon, and then the length of the array in square brackets
		let a = [3; 5];
		let a = [3, 3, 3, 3, 3];	// same as above

		Accessing Array Elements
			using index starting with 0
			
		Invalid Array Element Access
			 program resultes in a runtime error at the point of using an invalid value in the indexing operation
			 
		
**********/

fn main() {

    println!("=== integer type ===");
	let u8_val : u8 = 5;
	let i8_val : i8 = -2;
	println!("u8_val is {u8_val}");
	println!("i8_val is {i8_val}");
    println!();

    println!("=== floating type ===");
	let fval = 4.5;
	let f32_val : f32 = 6.9;
	println!("fval is {fval}");
	println!("f32_val is {f32_val}");
    println!();

    println!("=== boolean type ===");
	let bool_val = true;
    println!("bool_val is {bool_val}");
	let bool_val: bool = false;
    println!("bool_val is {bool_val}");
    println!();
	
    println!("=== character type ===");
	let char_val = '😻';
    println!("char_val is {char_val}");
	let char_val: char = '😂';
	println!("char_val is {char_val}");
    println!();
	
    println!("=== tuple type ===");
	let atup = (1, -2, 'C', "a string", 3.9);
	println!("tuple elements using index:");
	println!("{}, {}, {}, {}, {}", {atup.0}, {atup.1}, {atup.2}, {atup.3}, {atup.4});
    println!("tuple elements using destructuring:");
    let (a, b, c, d, e) = atup;
    println!("{}, {}, {}, {}, {}", {a}, {b}, {c}, {d}, {e});
    println!();

    println!("=== array type ===");
	let arr = [1, 2, 3, 4, 5];
	println!("array elements using index:");
	println!("{}, {}, {}, {}, {}", arr[0], arr[1], arr[2], arr[3], arr[4]);
    println!("invaliad array elements access:");
    
    // error: this operation will panic at runtime
    // index out of bounds: the length is 5 but the index is 5
    //println!("{} ", arr[5]);

}

/*****
	END OF FILE
**********/



