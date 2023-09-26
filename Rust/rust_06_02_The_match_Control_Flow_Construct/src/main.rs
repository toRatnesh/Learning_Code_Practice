/*****

References
    https://doc.rust-lang.org/book/ch06-02-match.html
    https://doc.rust-lang.org/rust-by-example/custom_types/enum.html

The match Control Flow Construct
	match allows you to compare a value against a series of patterns and then execute code based on which pattern matches
	Patterns can be made up of literal values, variable names, wildcards, and many other things
	
Using match
	List match keyword followed by an expression, the expression can be any type
	Next are the match arms. An arm has two parts: a pattern and some code
	=> operator separates the pattern and the code to run
	Each arm is separated from the next with a comma.
	If you want to run multiple lines of code in a match arm, you must use curly brackets, and the comma following the arm is then optional
	
	
	The code associated with each arm is an expression, and the resultant value of the expression in the matching arm is the value that gets returned for the entire match expression
	
Patterns That Bind to Values
	match arms can bind to the parts of the values that match the pattern
	This is how we can extract values out of enum variants

Matching with Option<T>
	handle Option<T> using match to get the inner T value out of the Some case when using Option<T>

Matches Are Exhaustive
	the arms’ patterns must cover all possibilities
	
Catch-all Patterns and the _ Placeholder
	catch-all pattern meets the requirement that match must be exhaustive
	we have to put the catch-all arm last because the patterns are evaluated in order
	If we put the catch-all arm earlier, the other arms would never run
	
	to catch-all but don’t want to use the value in the catch-all pattern: 
	_ is a special pattern that matches any value and does not bind to that value
	
**********/


enum UserStatus {
    BLOCKED,
    ALLOWED
}

fn user_is_blocked(usr_status: UserStatus) -> bool {
    match usr_status {
        UserStatus::BLOCKED => true,
        UserStatus::ALLOWED => false
    }
}

fn display_user_status(usr_status: UserStatus) {
    if user_is_blocked(usr_status) {
        println!("User is blocked for service");
    } else {
        println!("User is allowed for service");
    }
}

enum IpAddrType {
    IPV4(String),
    IPV6(String)
}

fn use_ip(ipval: &str) {
    println!("IP value is {ipval}");
}

fn display_ip(ip_val: IpAddrType) {
    match ip_val {
        IpAddrType::IPV4(_) => {
            println!("IP address is IPv4");
        }
        IpAddrType::IPV6(val) => {
            print!("IP address is IPv6, ");
            use_ip(&val);
        }
    }  
}

fn increment_value(ival : Option<i32>) -> Option<i32> {
    match ival {
        None => None,
        Some(val) => Some(val+1)
    }
}

fn display_optional(ival : Option<i32>) {
    match ival {
        None => {
            println!("Value is None");
        }
        Some(val) => {
            println!("Value is {val}");
        }
    }    
}

fn main() {
    println!("=== match Control Flow Construct ===");
    let usr_status = UserStatus::BLOCKED;
    display_user_status(usr_status);

    let usr_status = UserStatus::ALLOWED;
    display_user_status(usr_status);
    println!();


    println!("=== Patterns That Bind to Values ===");

    let ipv4_val = IpAddrType::IPV4(String::from("127.0.0.1"));
    let ipv6_val = IpAddrType::IPV6(String::from("0:0:0:0:0:0:0:1"));

    display_ip(ipv4_val);
    display_ip(ipv6_val);

    // bring names in scope to use without 'IpAddrType::'
    use IpAddrType::{IPV4, IPV6};

    let ipv4_val = IPV4(String::from("127.0.0.2"));
    let ipv6_val = IPV6(String::from("0:0:0:0:0:0:0:2"));

    display_ip(ipv4_val);
    display_ip(ipv6_val);
    println!();


    println!("=== Matching with Option<T> ===");

    let ival = Option::Some(13);
    let res = increment_value(ival);
    display_optional(res);

    let none_val = Option::<i32>::None;
    let res = increment_value(none_val);
    display_optional(res);
    println!();

    println!("=== Matches Are Exhaustive ===");
    /*
    // Not covering None will result in compilation error
    match ival {
        Some(val) => {
            println!("Value is {val}");
        }
    }
    */
    println!();

    println!("=== Catch-all Patterns and the _ Placeholder ===");

    let ipv4_val = IpAddrType::IPV4(String::from("127.0.0.1"));
    let ipv6_val = IpAddrType::IPV6(String::from("0:0:0:0:0:0:0:1"));

    match ipv4_val {
        IpAddrType::IPV4(val) => use_ip(&val),
        other => display_ip(other)
    }

    match ipv6_val {
        IpAddrType::IPV4(val) => use_ip(&val),
        other => display_ip(other)
    }

    let ipv4_val = IpAddrType::IPV4(String::from("127.0.0.1"));
    let ipv6_val = IpAddrType::IPV6(String::from("0:0:0:0:0:0:0:1"));

    match ipv4_val {
        IpAddrType::IPV6(val) => use_ip(&val),
        _ => ()
    }

    match ipv6_val {
        IpAddrType::IPV6(val) => use_ip(&val),
        _ => ()
    }
    
}

/*****
    END OF FILE
**********/



