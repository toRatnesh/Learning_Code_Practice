/*****

References
    https://doc.rust-lang.org/book/ch06-03-if-let.html
    https://doc.rust-lang.org/rust-by-example/custom_types/enum.html

Concise Control Flow with if let

	combine if and let to handle values that match one pattern while ignoring the rest.
	syntax if let takes a pattern and an expression separated by an equal sign
	It works the same way as a match, where the expression is given to the match and the pattern is its first arm
	
	The code in the if let block isn’t run if the value doesn’t match the pattern.
	We can include an else with an if let.
	The block of code that goes with the else is the same as the block of code that would go with the _ case in the match expression.

**********/

enum IpAddrType {
    IPV4(String),
    IPV6(String)
}

fn display_ip(ip_val: IpAddrType) {
    if let IpAddrType::IPV4(ipval) = ip_val {
        println!("IPv4 address is {ipval}");
    } else {
        println!("Address is IPv6");
    }    
}

fn main() {

    println!("=== Control Flow with if let ===");

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
}

/*****
    END OF FILE
**********/


