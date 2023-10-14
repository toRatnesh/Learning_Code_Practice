
pub mod my_pub_submodule;

pub fn pub_fun() {
    dbg!(println!("Inside public function of my_pub_module"));
    prv_fun();
}

fn prv_fun() {
    dbg!(println!("Inside private function of my_pub_module"));
    display();
}


//let pub_avar    = "A varible inside my_pub_module";
const   CONST_VAR:  &str   = "A const varible inside my_pub_module";
static  STATIC_VAR: &str   = "A static varible inside my_pub_module";

//pub const   const_var   = "A public const varible inside my_pub_module";
//pub static  static_var  = "A public static varible inside my_pub_module";

pub const   PUB_CONST_VAR:  &str   = "A public const varible inside my_pub_module";
pub static  PUB_STATIC_VAR: &str   = "A public static varible inside my_pub_module";

fn display() {

    dbg!(CONST_VAR);
    dbg!(STATIC_VAR);

    dbg!(PUB_CONST_VAR);
    dbg!(PUB_STATIC_VAR);

}


//println!("Inside module my_pub_module");

