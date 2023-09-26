/*****

References
    https://doc.rust-lang.org/book/ch06-01-defining-an-enum.html
    https://doc.rust-lang.org/rust-by-example/custom_types/enum.html

Defining an Enum
	Enums allow you to define a type by enumerating its possible variants
	Enums give you a way of saying a value is one of a possible set of values
	An enum value can only be one of its variants
	
	To define an enum use keyword enum followed by enum name
	variants: Then inside curly brackets use variants name separated by commas
	
	enum IpAddrType {
		IPV4,
		IPV6
	}

	IpAddrType is now a custom data type that we can use elsewhere in our code.


Enum Values
	let ipv4	= IpAddrType::IPV4;
	let ipv6	= IpAddrType::IPV6;

	Since after definition IpAddrType becomes a type
	We may use it as a function parameter type or return value

	As IpAddrType has only type to store data we might use another struct like following

	struct IpAddrValue {
		ip_type:	IpAddrType,
		ip_value:	String
	}

	Rust enum is more concise: 
		we can put data directly into each enum variant

	enum IpAddrType {
		IPV4(String),
		IPV6(String)
	}
		
	let ipv4	= IpAddrType::IPV4(String::from("127.0.0.1"));
	let ipv6	= IpAddrType::IPV6(String::from("0:0:0:0:0:0:0:1"));

	The name of each enum variant that we define also becomes a function that constructs an instance of the enum.
	We automatically get this constructor function defined as a result of defining the enum.
	
	Also each variant can have different types (strings, numeric types, or structs, for example) and amounts of associated data
	You can even include another enum
	enum IpAddrType {
		IPV4(u8, u8, u8, u8),
		IPV6(String)
	}


Enum Methods
	Like struct we may also define methods for enum using impl
	The body of the method would use self to get the value that we called the method on

The Option Enum and Its Advantages Over Null Values
	
	Option is defined by the standard library
	The Option type encodes the very common scenario in which a value could be something or it could be nothing.
	
	Rust does not have nulls, but it does have an enum that can encode the concept of a value being present or absent.
	enum Option<T> {
		None,
		Some(T),
	}
	
	
	In order to have a value that can possibly be null, you must explicitly opt in by making the type of that value Option<T>. 
	Then, when you use that value, you are required to explicitly handle the case when the value is null. 
	
	Everywhere that a value has a type that isn’t an Option<T>, you can safely assume that the value isn’t null. 
	This was a deliberate design decision for Rust to limit null’s pervasiveness and increase the safety of Rust code.	

	To get the T value out of a Some variant when you have a value of type Option<T>, Option<T> enum has a large number of methods.

**********/

enum IpAddr {
    IPV4,
    IPV6(String)
}

impl IpAddr {
    fn display(&self) {
        match self {
            IpAddr::IPV4 => (),
            IpAddr::IPV6(val) => {
                println!("IP address is {val}");
            }
        }
    }
}

fn use_ip_addr(ipval: IpAddr) {
    match ipval {
        IpAddr::IPV4 => (),
        IpAddr::IPV6(val) => {
            println!("IP address is {val}");
        }
    }
}

fn get_ip_addr(is_ip4: bool) -> IpAddr {
    if is_ip4 {
        IpAddr::IPV4
    } else {
        IpAddr::IPV6(String::from("0:0:0:0:0:0:0:1"))
    }
}

fn main() {

    println!("=== Defining an Enum ===");

    let ip4 = IpAddr::IPV4;
    let ip6 = IpAddr::IPV6(String::from("0:0:0:0:0:0:0:1"));

    ip4.display();
    ip6.display();
    println!();


    println!("=== Enum Values ===");

    let ip6 = IpAddr::IPV6(String::from("0:0:0:0:0:0:0:2"));

    let IpAddr::IPV6(val) = ip6 else {return () };
    println!("IPv6 address is {val}");

    let ip4 = IpAddr::IPV4;
    let ip6 = IpAddr::IPV6(String::from("0:0:0:0:0:0:0:2"));

    use_ip_addr(ip4);
    use_ip_addr(ip6);

    use_ip_addr(get_ip_addr(true));
    use_ip_addr(get_ip_addr(false));

    println!();


    println!("=== The Option Enum and Its Advantages Over Null Values ===");
    let aval = Option::<i32>::Some(32);
    let achr = Some('R');

    let Some(val) = aval else { return () };
    println!("Value is {val}");

    let Some(chr) = achr else { return () };
    println!("Character is {chr}");
    
    let aval : Option<i32> = None;
    let achr : Option<char> = None;

    let Some(val) = aval else { return () };
    println!("Value is {val}");

    let Some(chr) = achr else { return () };
    println!("Character is {chr}");
    



}

/*****
    END OF FILE
**********/


