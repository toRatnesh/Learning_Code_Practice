/*****

References
    https://doc.rust-lang.org/book/ch08-03-hash-maps.html
    https://doc.rust-lang.org/rust-by-example/std/hash.html
    https://doc.rust-lang.org/stable/std/collections/hash_map/struct.HashMap.html

    https://doc.rust-lang.org/stable/std/collections/hash_map/enum.Entry.html

Storing Keys with Associated Values in Hash Maps
	HashMap<K, V> stores a mapping of keys of type K to values of type V using a hashing function
	hashing function,	determines how it places these keys and values into memory
	
Creating a New Hash Map
	create an empty hash map using new
	add elements with insert
	there’s no built-in macro to construct hash map
	hash maps store their data on the heap
	HashMap has keys of type String and values of type i32
	hash maps are homogeneous: all keys have the same type, and all values have the same type
	
Accessing Values in a Hash Map
	get(key)
		use key to get associated value
		returns an Option<&V>
		returns None, if there’s no value for that key
	
Iterate over each key/value pair
	use for loop
	
	for (key, value) in &hash_map_coll {
        println!("{key}: {value}");
    }
	
Hash Maps and Ownership
	For types that implement the Copy trait, like i32, the values are copied into the hash map
	For owned values like String, the values will be moved and the hash map will be the owner of those values
	
	If we insert references to values into the hash map, the values that the references point to must be valid for at least as long as the hash map is valid.
	
Updating a Hash Map
	Overwriting a Value
		reinserting a key with a different value will overwrite the value associated with that key
	Adding a Key and Value Only If a Key Isn’t Present
		entry method takes the key you want to check as a parameter
		The return value of the entry method is an enum called Entry that represents a value that might or might not exist
	Updating a Value Based on the Old Value
		Get a mutable reference to the value using key and update it
	
Hashing Functions
    By default, HashMap uses a hashing function called SipHash
    better security is preferred over performance

    you may specify a different hasher
    A hasher is a type that implements the BuildHasher trait

Important Methods
    clear(&mut self)                Clears the map, removing all key-value pairs
    contains_key<Q>(&self, k: &Q)   Returns true if the map contains a value for the specified key
    is_empty(&self)                 Returns true if the map contains no elements
    
    keys(&self)                     An iterator visiting all keys in arbitrary order
    len(&self)                      Returns the number of elements in the map
    remove<Q>(&mut self, k: &Q)     Removes a key from the map, returning the value at the key if the key was previously in the map
    values(&self)                   An iterator visiting all values in arbitrary order

**********/

use std::collections::HashMap;

fn main() {

    println!("=== Creating a New Hash Map ===");
    let empty_map : HashMap<String, u32>    = HashMap::new();

    let mut map_coll : HashMap<String, i32> = HashMap::new();
    map_coll.insert("key-1".to_string(), 1);
    map_coll.insert("key-2".to_string(), 2);
    map_coll.insert("key-3".to_string(), 3);

    println!("\n=== Accessing Values in a Hash Map ===");
    let val = map_coll.get("key-2");
    match val {
        Some(v) => println!("map_coll.get(\"key-2\") {v}"),
        None    => println!("None")
    }

    let val = map_coll.get("does-not-exist");
    match val {
        Some(v) => println!("map_coll.get(\"does-not-exist\") {v}"),
        None    => println!("map_coll.get(\"does-not-exist\") None"),
    }

    let val = map_coll.get("key-2").copied().unwrap_or(0);
    println!("map_coll.get(\"key-2\").copied().unwrap_or(0) {val}");

    let val = map_coll.get("does-not-exist").copied().unwrap_or(-1);
    println!("map_coll.get(\"does-not-exist\").copied().unwrap_or(-1) {val}");

    println!("\n=== Iterate over each key/value pair ===");
    for(k, v) in &map_coll {
        println!("key {k} - value {v}");
    }

    println!("\n=== Hash Maps and Ownership ===");
    {
        let astr = String::from("key-4");
        let aval = 4;
        //map_coll.insert(&astr, aval);   // error[E0597]: `astr` does not live long enough
    }
    {
        let astr = String::from("key-4");
        let aval = 4;
        println!("Before insertion in map key {astr} value {aval}");
        map_coll.insert(astr, aval);
        //println!("After insertion in map {astr} {aval}");   // CE error[E0382]: borrow of moved value: `astr`
        println!("After insertion in map key (moved to map) value {aval}");
    }
    println!("{:?}", map_coll);

    println!("\n=== Updating a Hash Map ===");
    println!("--- Overwriting a Value ---");
    map_coll.insert("key-4".to_string(), 14);
    println!("{:?}", map_coll);

    println!("--- Adding a Key and Value Only If a Key Isn’t Present ---");
    let ret = map_coll.entry("key-4".to_string()).or_insert(24);
    println!("return value of entry {ret}");
    println!("{:?}", map_coll);

    let ret = map_coll.entry("key-5".to_string()).or_insert(5);
    println!("return value of entry {ret}");
    println!("{:?}", map_coll);

    let ret = map_coll.entry("key-5".to_string());
    match ret {
        std::collections::hash_map::Entry::Occupied(elem)  => {
            println!("key {} exist with value {}", elem.key(), elem.get());
        }
        std::collections::hash_map::Entry::Vacant(elem)    => {
            println!("key {} does not exist", elem.key());
        }
    }

    let ret = map_coll.entry("key-7".to_string());
    match ret {
        std::collections::hash_map::Entry::Occupied(elem)  => {
            println!("key {} exist with value {}", elem.key(), elem.get());
        }
        std::collections::hash_map::Entry::Vacant(elem)    => {
            println!("key {} does not exist", elem.key());
        }
    }

    println!("--- Updating a Value Based on the Old Value ---");
    println!("{:?}", map_coll);
    let ret = map_coll.entry("key-2".to_string()).or_insert(0);
    *ret += 2;
    println!("{:?}", map_coll);

    println!("\n=== Important Methods ===");
    dbg!(map_coll.keys());
    dbg!(map_coll.values());
    dbg!(map_coll.len());
    dbg!(map_coll.is_empty());
    dbg!(map_coll.clear());
    dbg!(map_coll.is_empty());

}

/*****
    END OF FILE
**********/



