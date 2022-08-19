/*
    Concise Control Flow with if let
    The if let syntax lets you combine if and let into a less verbose way to handle values that match one pattern while ignoring the rest. 
    We can include an else with an if let.

*/

enum UserStatus {
    WHITELIST,
    GREYLIST,
    BLOCKED
}

fn notify_blocked_user() {
    println!("You have been blocked from accessing the service");
}

// first way to handle
fn check_user_status(ustatus: UserStatus) {
    match ustatus {
            UserStatus::BLOCKED => notify_blocked_user(),
            _ => () // ignore other status
    }
}

// second way to handle using if let 
fn check_user_status_2(ustatus: UserStatus) { 
    if let UserStatus::BLOCKED = ustatus {
        notify_blocked_user();
    }
    else {
        // do nothing
    }
}

pub fn main() {
    check_user_status(UserStatus::BLOCKED);
    check_user_status_2(UserStatus::BLOCKED);
}

