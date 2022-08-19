/*
    6.2 The match Control Flow Construct

    match that allows you to compare a value against a series of patterns and then execute code based on which pattern matches. Patterns can be made up of literal values, variable names, wildcards, and many other things
    If you want to run multiple lines of code in a match arm, you must use curly brackets.

    Patterns that Bind to Values
    match arms can bind to the parts of the values that match the pattern. This is how we can extract values out of enum variants.

    Matches Are Exhaustive
    Rust knows that we didn’t cover every possible case and even knows which pattern we forgot! Matches in Rust are exhaustive: we must exhaust every last possibility in order for the code to be valid.

    Catch-all Patterns and the _ Placeholder
    catch-all pattern meets the requirement that match must be exhaustive.
    Rust also has a pattern we can use when we don’t want to use the value in the catch-all pattern: _ which is a special pattern that matches any value and does not bind to that value.



*/

enum IpAddrType {
    IPV4,
    IPV6,
}

fn get_addr(ip_type: IpAddrType) -> String {
    match ip_type {
        // If you want to run multiple lines of code in a match arm, you must use curly brackets.
        IpAddrType::IPV4 => {
            println!("IP version 4");
            String::from("127.0.01")
        }
        IpAddrType::IPV6 => String::from("0000:0000:0000:0000:0000:0000:0000:0001"),
    }
}

#[derive(Debug)]
enum EntryStatus {
    GRANTED,
    BLOCKED
}

enum EmployeeType {
    PERMANENT,
    CONTRACT,
    FIELD(EntryStatus)
}

fn display_emplyee_status(emp : EmployeeType) -> bool {
    match emp {
        EmployeeType::PERMANENT => true,
        EmployeeType::CONTRACT => false,
        EmployeeType::FIELD(status) => {
            println!("Emplyee status is {:?}", status);
            true
        }
    }
}

// Matching with Option<T>
fn plus_five(x : Option<u32>) -> Option<u32> {
    match x {
        None => None,
        Some(i) => Some(i+1)
    }
}

// Catch-all Patterns and the _ Placeholder
enum BinaryType {
    BIN00,
    BIN01,
    BIN10,
    BIN11
}

fn match_binary_type(bt: BinaryType) -> bool {
    match bt {
        /*
        BinaryType::BIN00 => true,
        BinaryType::BIN01 => true,
        BinaryType::BIN10 => false,
        BinaryType::BIN11 => true
        */

        BinaryType::BIN10 => false,
        _ => true
    }
}

pub fn main() {

    let ipv4 = get_addr(IpAddrType::IPV4);
    println!("{}", ipv4);
    let ipv6 = get_addr(IpAddrType::IPV6);
    println!("{}", ipv6);

    let _femp = EmployeeType::PERMANENT;
    let _femp = EmployeeType::CONTRACT;
    let femp = EmployeeType::FIELD(EntryStatus::GRANTED);
    display_emplyee_status(femp);
    let femp = EmployeeType::FIELD(EntryStatus::BLOCKED);
    display_emplyee_status(femp);

    let val_five = 5;
    let res = plus_five(Some(val_five));
    println!("{:?}", res);
    let res = plus_five(None);
    println!("{:?}", res);

    println!("{:?}", match_binary_type(BinaryType::BIN00));
    println!("{:?}", match_binary_type(BinaryType::BIN01));
    println!("{:?}", match_binary_type(BinaryType::BIN10));
    println!("{:?}", match_binary_type(BinaryType::BIN11));

}

