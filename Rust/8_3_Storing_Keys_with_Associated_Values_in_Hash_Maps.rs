/***********
    8.3 Storing Keys with Associated Values in Hash Maps
    
    References:
    https://doc.rust-lang.org/book/ch08-03-hash-maps.html

    The last of our common collections is the hash map. 
    The type HashMap<K, V> stores a mapping of keys of type K to values of type V using a hashing function, which determines how it places these keys and values into memory.

    Just like vectors, hash maps store their data on the heap.
    Like vectors, hash maps are homogeneous: all of the keys must have the same type as each other, and all of the values must have the same type.

    1. Creating a New Hash Map
        using new:
        let mut scores = std::collections::HashMap::new();

    2. Accessing Values in a Hash Map
        I. using get method
            The get method returns an Option<&V>; if there’s no value for that key in the hash map, get will return None.
            let team_name = String::from("Blue");
            let score = scores.get(&team_name);

        II. using for loop
            to iterate over each key/value pair in a hash map
            for (key, value) in &scores {
                println!("{}: {}", key, value);
            }

    3. Hash Maps and Ownership
        For types that implement the Copy trait, like i32, the values are copied into the hash map. 
        For owned values like String, the values will be moved and the hash map will be the owner of those values

        If we insert references to values into the hash map, the values won’t be moved into the hash map.
        The values that the references point to must be valid for at least as long as the hash map is valid.
        (How to maintain validity?) visit reference

    4. Updating a Hash Map
        each unique key can only have one value associated with it at a time

        I. Overwriting a Value
            If we insert a key and a value into a hash map and then insert that same key with a different value, the value associated with that key will be replaced.
            scores.insert(String::from("Blue"), 10);

        II. Adding a Key and Value Only If a Key is not Present
            Hash maps have a special API for this called entry that takes the key you want to check as a parameter. The return value of the entry method is an enum called Entry that represents a value that might or might not exist.
            scores.entry(String::from("Yellow")).or_insert(50);

            The or_insert method on Entry is defined to return a mutable reference to the value for the corresponding Entry key if that key exists, and if not, inserts the parameter as the new value for this key and returns a mutable reference to the new value.

        III. Updating a Value Based on the Old Value
            let count = map.entry(word).or_insert(0);
            *count += 1

            The or_insert method returns a mutable reference (&mut V) to the value for the specified key.
            Here we store that mutable reference in the count variable, so in order to assign to that value, we must first dereference count using the asterisk (*).
            The mutable reference goes out of scope at the end of the for loop, so all of these changes are safe and allowed by the borrowing rules.

    5. Hashing Functions
        By default, HashMap uses a hashing function called SipHash that can provide resistance to Denial of Service (DoS) attacks involving hash tables1.

************/

pub fn main() {

    // 1. Creating a New Hash Map
    let mut scores = std::collections::HashMap::new();
    
    scores.insert(String::from("Blue"), 10);
    scores.insert(String::from("Yellow"), 20);

    // 2. Accessing Values in a Hash Map
    // 2.I using get method
    let team_name = String::from("Blue");
    let _score = scores.get(&team_name);
    //println!("{}, {}", team_name, score);

    // 2.II using for loop
    for (key, value) in &scores {
        println!("{}: {}", key, value);
    }

    // 3. Hash Maps and Ownership
    let key = String::from("Black");
    let value = 15;
    scores.insert(key, value);
    //println!("{}", key); // error[E0382]: borrow of moved value: `key`
    println!("{}", value);


    // 4. Updating a Hash Map
    // 4.I  Overwriting a Value
    scores.insert(String::from("Blue"), 10);
    scores.insert(String::from("Blue"), 25);
    println!("{:?}", scores);

    // 4.II Adding a Key and Value Only If a Key Isn’t Present
    scores.entry(String::from("Yellow")).or_insert(50);
    scores.entry(String::from("White")).or_insert(50);
    println!("{:?}", scores);

    // 4.III Updating a Value Based on the Old Value
    let text = "hello world wonderful hello world";
    let mut wc_map = std::collections::HashMap::new();
    for word in text.split_whitespace() {
        let count = wc_map.entry(word).or_insert(0);
        *count += 1;
    }
    println!("{:?}", wc_map);    

}

/*****
    END OF FILE
*****/