/**********
    8.2 Storing UTF-8 Encoded Text with Strings

    References:
    https://doc.rust-lang.org/book/ch08-02-strings.html

    1. What Is a String?
        Rust has only one string type in the core language, which is the string slice str that is usually seen in its borrowed form &str.
        string slices, are references to some UTF-8 encoded string data stored elsewhere.
        String literals, for example, are stored in the program’s binary and are therefore string slices.

        The String type, which is provided by Rust’s standard library rather than coded into the core language, is a growable, mutable, owned, UTF-8 encoded string type.

        Both String and string slices are UTF-8 encoded.

    2. Creating a New String
        2.1 using new
            let mut s = String::new();
        
        2.2 to_string()
            let data = "initial contents";
            let s = data.to_string();
            let s = "initial contents".to_string();

        2.3 String::from()
             let s = String::from("initial contents");


    3. Updating a String
        3.1 Appending to a String with push_str and push
            The push_str method takes a string slice because we don’t necessarily want to take ownership of the parameter.
            The push method takes a single character as a parameter and adds it to the String.

        3.2 Concatenation with the + Operator or the format! Macro
            The + operator uses the add method, whose signature looks something like this:
            fn add(self, s: &str) -> String { }

            For more complicated string combining, we can instead use the format! macro:

    4. Indexing into Strings
        if you try to access parts of a String using indexing syntax in Rust, you’ll get an error. 

        4.1 Internal Representation
        A String is a wrapper over a Vec<u8>
        let hello = String::from("Hola");
        Each of these letters takes 1 byte when encoded in UTF-8. len will be 4, which means the vector storing the string “Hola” is 4 bytes long.

        let hello = String::from("Здравствуйте");
        Because each Unicode scalar value in that string takes 2 bytes of storage, len will be 24.

        4.2 Bytes and Scalar Values and Grapheme Clusters
            Another point about UTF-8 is that there are actually three relevant ways to look at strings from Rust’s perspective: 
            a) as bytes, 
            b) scalar values, and 
            c) grapheme clusters (the closest thing to what we would call letters).

        Indexing into a string is often a bad idea because it’s not clear what the return type of the string-indexing operation should be: a byte value, a character, a grapheme cluster, or a string slice.

        If we look at the Hindi word “नमस्ते” written in the Devanagari script, it is stored as a vector of u8 values that looks like this:   
        [224, 164, 168, 224, 164, 174, 224, 164, 184, 224, 165, 141, 224, 164, 164, 224, 165, 135]
        That’s 18 bytes and is how computers ultimately store this data. If we look at them as Unicode scalar values, which are what Rust’s char type is, those bytes look like this:
		['न', 'म', 'स', '्', 'त', 'े']
        There are six char values here, but the fourth and sixth are not letters: they’re diacritics that don’t make sense on their own. Finally, if we look at them as grapheme clusters, we’d get what a person would call the four letters that make up the Hindi word:
		["न", "म", "स्", "ते"]

        For more detail visit: https://doc.rust-lang.org/book/ch08-02-strings.html#internal-representation

        A final reason Rust doesn’t allow us to index into a String to get a character is that indexing operations are expected to always take constant time (O(1)).
        But it isn’t possible to guarantee that performance with a String, because Rust would have to walk through the contents from the beginning to the index to determine how many valid characters there were.


    5. Slicing Strings
        Rather than indexing using [] with a single number, you can use [] with a range to create a string slice containing particular bytes:
        let hello = "Здравствуйте";
        let s = &hello[0..4];

    6. Methods for Iterating Over Strings
        The best way to operate on pieces of strings is to be explicit about whether you want characters or bytes.

        chars() method: returns values of type char, and you can iterate over the result to access each element
        bytes() method: returns each raw byte, which might be appropriate for your domain

        NOTE:
        Getting grapheme clusters from strings as with the Devanagari script is complex, so this functionality is not provided by the standard library. 
        Crates are available on crates.io if this is the functionality you need.

************/

pub fn main() {
    // 2. Creating a New String
    {
        let s = String::new();                  println!("{}", s);
        let data = "initial contents";              println!("{}", data);
        let s = data.to_string();                   println!("{}", s);
        let s = "initial contents".to_string();     println!("{}", s);
        let s = String::from("initial contents");   println!("{}", s);
    }

    // 3. Updating a String
    {
        let mut s1 = String::new();
        let s2 = "this will be appended";
        s1.push_str(s2);
        println!("s1: {}", s1);
        println!("s2: {}", s2);

        s1.push('@');
        println!("s1: {}", s1);

        let s1 = String::from("Good, ");
        let s2 = String::from("night!");
        //let s3 = &s1 + &s2;         // error[E0369]: cannot add `&String` to `&String`
        let s3 = s1 + &s2;        // note s1 has been moved here and can no longer be used
        //println!("s1: {}", s1);
        println!("s2: {}", s2);
        println!("s3: {}", s3);

        let s1 = String::from("This");
        let s2 = String::from("is very");
        let s3 = String::from("compicates string");

        let s = format!("{}-{}-{}", s1, s2, s3);
        println!("s1: {}", s1);
        println!("s2: {}", s2);
        println!("s3: {}", s3);
        println!("s : {}", s);
    }

    // 4. Indexing into Strings
    {
        let _s = String::from("hello");
        //let h = s[0];       // error[E0277]: the type `String` cannot be indexed by `{integer}`
    }

    // 5. Slicing Strings
    {
        let hello = "Здравствуйте";
        //let s = &hello[0..1];   // thread 'main' panicked at 'byte index 1 is not a char boundary; it is inside 'З' (bytes 0..2) of `Здравствуйте`', library/core/src/str/mod.rs:127:5
        let s = &hello[0..4];
        println!("s : {}", s);
    }

    // 6. Methods for Iterating Over Strings
    {
        let s = "Здравствуйте";
        for c in s.chars() {
            print!("{} ", c);
        }
        println!("");

        for b in s.bytes() {
            print!("{} ", b);
        }
        println!("");

        let s = "नमस्ते";
        for c in s.chars() {
            print!("{} ", c);
        }
        println!("");

        for b in s.bytes() {
            print!("{} ", b);
        }
        println!("");

    }
}

/*******
    END OF FILE
******/