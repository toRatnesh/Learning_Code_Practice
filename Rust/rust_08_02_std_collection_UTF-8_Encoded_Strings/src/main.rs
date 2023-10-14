/*****

References
    https://doc.rust-lang.org/book/ch08-01-vectors.html
    https://doc.rust-lang.org/rust-by-example/std/str.html
    https://doc.rust-lang.org/stable/std/string/struct.String.html


Storing UTF-8 Encoded Text with Strings
	strings are implemented as a collection of bytes
	strings methods provide useful functionality when those bytes are interpreted as text
	
	String is different from the other collections,
	indexing into a String is complicated by the differences between how people and computers interpret String data

What Is a String?

	String type, is a growable, mutable, owned, UTF-8 encoded string type
	String is actually implemented as a wrapper around a vector of bytes
	with some extra guarantees, restrictions, and capabilities
	
	string slice
		&str is a slice (&[u8]) that always points to a valid UTF-8 sequence, and can be used to view into a String

Creating a New String
	empty string
		let mut astr = String::new();
		to create a mutable new empty string called astr
		
	string with initial data
		1. Use String::from()
			let astr = String::from("sample string");
			
		2. Using to_string methods
			let data = "sample string";
			let astr = data.to_string();
			
			let astr = "this will also create a string".to_string();
		
	strings are UTF-8 encoded, so we can include any properly encoded data in them
		let hello = String::from("नमस्ते");

Updating a String
	A String can grow in size and its contents can change
	
	1. Append to a String with push_str and push
		push_str()	
			to append a string slice
			takes a string slice because we don’t want to take ownership of the parameter
			
		push()
			takes a single character as a parameter and adds it to the String
		
	2. use the + operator or the format! macro to concatenate String values
		+ operator
			+ operator uses the add method
			fn add(self, s: &str) -> String { ... }
			
			let s1 = String::from("Hello, ");
			let s2 = String::from("world!");
			let s3 = s1 + &s2;	// note s1 has been moved here and can no longer be used
			
			Query: the type of &s2 is &String, not &str, So why does above code compile?
			Ans: the compiler can coerce the &String argument into a &str
			
		format!
			it works like println!, with only difference, it returns a String with the contents
			format! macro uses references so that this call doesn’t take ownership of any of its parameters

Indexing into Strings
	Rust strings do not support indexing
	an index into the string’s bytes will not always correlate to a valid Unicode scalar value
	
	Internal Representation
		A String is a wrapper over a Vec<u8>
		
		let astr = "Rust";			// length 4
		let ch = astr[0];			// CE error[E0277]: the type `str` cannot be indexed by `{integer}`

		let astr = "Здравствуйте";	// length 24

		A character might be 1 or more than 1 byte long depending on its representation
		So Rust does not allow use of index to access a character in a string 
		to avoid returning an unexpected value and causing bugs that might not be discovered immediately
		
	Bytes, Scalar Values and Grapheme Clusters
	
		Three relevant ways to look at strings
		i.		as bytes
		ii.		as scalar values
		iii.	as grapheme clusters
	
		Example: For "नमस्ते"
		vector of u8 values
			[224, 164, 168, 224, 164, 174, 224, 164, 184, 224, 165, 141, 224, 164, 164, 224, 165, 135]
		
		Unicode scalar values
			['न', 'म', 'स', '्', 'त', 'े']
		
		grapheme clusters
			["न", "म", "स्", "ते"]
			
	Another Reason:
		indexing operations are expected to always take constant time (O(1))
		it isn’t possible to guarantee that performance with a String, 
		because Rust would have to walk through the contents from the beginning to the index to determine how many valid characters

Slicing Strings
	use [] with a range to create a string slice containing particular bytes
	
	let hello = "Здравствуйте";
	let str_slice = &hello[0..4];
	
	each of these characters is 2 bytes, which means str_slice will be Зд
	
	let str_slice = &hello[0..4];
	panic at runtime in the same way as if an invalid index were accessed in a vector
	
	use ranges to create string slices with caution
	
Methods for Iterating Over Strings
	Be explicit whether you want characters or bytes
	for individual Unicode scalar values, use the chars method
	
	for c in "Здравствуйте".chars() {
		println!("{c}");
	}

	for b in "Здравствуйте".bytes() {
		println!("{b}");
	}
	
	NOTE: valid Unicode scalar values may be made up of more than 1 byte

Important Methods
    as_bytes(&self)     Returns a byte slice of this String’s contents
    as_str(&self)       Extracts a string slice containing the entire String
    clear(&mut self)    Truncates this String, removing all contents

    insert(&mut self, idx: usize, ch: char)             Inserts a character into this String at a byte position
    insert_str(&mut self, idx: usize, string: &str)     Inserts a string slice into this String at a byte position

    is_empty(&self)     Returns true if this String has a length of zero, and false otherwise
    pop(&mut self)      Removes the last character from the string buffer and returns it

    push(&mut self, ch: char)           Appends the given char to the end of this String
    push_str(&mut self, string: &str)   Appends a given string slice onto the end of this String

    remove(&mut self, idx: usize)       Removes a char from this String at a byte position and returns it

**********/

fn main() {

    println!("=== Creating a New String ===");
    let empty_str = String::new();

    let astr = String::from("sample string");
    println!("let astr = String::from(\"sample string\"): {astr}");
    
    let astr = "sample string";
    println!("let astr = \"sample string\": {astr}");

    let astr = String::from(astr);
    println!("let astr = String::from(astr): {astr}");

    let astr = "sample string";

    let astr = astr.to_string();
    println!("let astr = astr.to_string(): {astr}");

    let astr = "sample string".to_string();
    println!("let astr = \"sample string\".to_string(): {astr}");


    println!("\n=== Updating a String ===");

    {
        let mut res_str = String::new();
        let s1 = "Learning";
        let s2 = "Rust";

        println!("Before update, s1: {s1} s2: {s2} res_str: {res_str}");
        res_str.push_str(s1);
        res_str.push(' ');
        res_str.push_str(s2);
        res_str.push_str(" using push_str() and push() to concat");
        println!("After update, s1: {s1} s2: {s2} res_str: {res_str}");
    }

    {
        let mut res_str = String::new();
        let s1 = "Learning";
        let s2 = "Rust";

        println!("Before update, s1: {s1} s2: {s2} res_str: {res_str}");
        //res_str = s1 + s2;    // error[E0369]: cannot add `&str` to `&str`
        res_str = res_str + s1;
        res_str = res_str + " Rust" + " using + to concat";
        println!("After update, s1: {s1} s2: {s2} res_str: {res_str}");
    }

    {
        let mut res_str = String::new();
        let s1 = String::from("Learning");
        let s2 = String::from("Rust");

        println!("Before update, s1: {s1} s2: {s2} res_str: {res_str}");
        res_str = s1 + " " + &s2 + " using + to concat";

        // error[E0382]: borrow of moved value: `s1`
        //println!("After update, s1: {s1} s2: {s2} res_str: {res_str}");

        println!("After update, s1:  s2: {s2} res_str: {res_str}");
    }


    {
        let s1 = String::from("Learning");
        let s2 = String::from("Rust");

        println!("Before update, s1: {s1} s2: {s2}");
        let res_str = format!("{s1} {s2} using format to concat");
    
        println!("After update, s1: {s1}  s2: {s2} res_str: {res_str}");
    }

    println!("\n=== Indexing into Strings ===");
    {
        let astr    = String::from("sample string");
        //let ch      = astr[1];  // error[E0277]: the type `String` cannot be indexed by `{integer}`
        println!("`String` cannot be indexed by {{integer}}");
    }

    println!("\n=== Slicing Strings ===");
    let astr = String::from("sample string");
    println!("astr {astr}");

    let aslice = &astr[0..];
    println!("&astr[0..] {aslice}");

    let aslice = &astr[..6];
    println!("&astr[..5] {aslice}");

    let aslice = &astr[2..5];
    println!("&astr[2..5] {aslice}");

    println!("\n=== Methods for Iterating Over Strings ===");
    {
        let astr = "Learning Rust";
        print!("Using chars: ");
        for achar in astr.chars() {
            print!("{achar} ");
        }
        println!();

        print!("Using bytes: ");
        for abyte in astr.bytes() {
            print!("{abyte} ");
        }
        println!();        
    }

    {
        let astr = "नमस्ते";
        print!("Using chars: ");
        for achar in astr.chars() {
            print!("{achar} ");
        }
        println!();

        print!("Using bytes: ");
        for abyte in astr.bytes() {
            print!("{abyte} ");
        }
        println!();        
    }

    println!("\n=== Important Methods ===");
    {
        let mut astr = String::from("sample string");
        dbg!(&astr);
        dbg!(astr.len());
        dbg!(astr.capacity());

        dbg!(astr.remove(0));
        dbg!(&astr);
        dbg!(astr.insert(0, 'S'));
        dbg!(&astr);
        dbg!(astr.insert_str(0, "Rust "));
        dbg!(&astr);
        dbg!(astr.pop());

        dbg!(astr.is_empty());
        dbg!(astr.clear());
        dbg!(astr.is_empty());
    }

}

/*****
    END OF FILE
**********/


