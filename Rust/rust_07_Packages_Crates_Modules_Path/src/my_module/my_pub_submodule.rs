

pub mod user_mgmt {
    #[derive(Debug)]

    pub enum UserType {
        ADMIN,
        SUPPORT,
        TEMP
    }

    pub struct User {
        pub name:   String,
        age:    u32,
        utype:  UserType
    }


    impl User {

        pub fn get() -> User {

            User {
                name:   String::from("User-01"),
                age:    32,
                utype:  UserType::ADMIN
            }

        }


        pub fn display(&self) {

            let user_type = match self.utype {
                UserType::ADMIN     => "ADMIN",
                UserType::SUPPORT   => "SUPPORT",
                UserType::TEMP      => "TEMP"
            };

            println!("User name {} age {} type {}", self.name, self.age, user_type);
        }

    }

}



pub fn display() {
    println!("Accessing parent module");
    super::pub_fun();
    super::prv_fun();

}


