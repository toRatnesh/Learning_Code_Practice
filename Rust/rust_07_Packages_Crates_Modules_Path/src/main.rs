/*****

References
    Anthony Williams - C++ Concurrency in Action
    

7. Managing Growing Projects with Packages, Crates, and Modules
	As a project grows, you should organize code by splitting it into multiple modules and then multiple files.
	A package can contain multiple binary crates and optionally one library crate.
	As a package grows, you can extract parts into separate crates that become external dependencies.
	
	For very large projects comprising a set of interrelated packages that evolve together, Cargo provides workspaces.
	
	Encapsulating implementation
		Once you’ve implemented an operation, other code can call your code via its public interface without having to know how the implementation works.
	
	Scope
		The nested context in which code is written has a set of names that are defined as “in scope.
		You can create scopes and change which names are in or out of scope.
		You can’t have two items with the same name in the same scope.
	
	Rust provides module system, to manage your code’s organization
		Packages:	A Cargo feature that lets you build, test, and share crates
		Crates:		A tree of modules that produces a library or executable
		Modules and use:	Let you control the organization, scope, and privacy of paths
		Paths:		A way of naming an item, such as a struct, function, or module



7.1. Packages and Crates
	Crate
		A crate is the smallest amount of code that the Rust compiler considers at a time.
		Crates can contain modules, and the modules may be defined in other files that get compiled with the crate.
		
	Two forms of Crate:
		A binary crate
			Binary crates are programs you can compile to an executable that you can run.
			Each must have a function called main that defines what happens when the executable runs.
			
		A library crate
			Library crates don’t have a main function, and they don’t compile to an executable.
			Instead, they define functionality intended to be shared with multiple projects.
			
		Crate root
			The crate root is a source file that the Rust compiler starts from and makes up the root module of your crate.
			
	Package
		A package is a bundle of one or more crates that provides a set of functionality.
		A package contains a Cargo.toml file that describes how to build those crates.
		
		A package can contain as many binary crates as you like, but at most only one library crate.
		A package must contain at least one crate, whether that’s a library or binary crate.
		
		Cargo is a package that contains the binary crate for the command-line tool to build code.

	What happens when we create a package?
		$ cargo new my-project
			Created binary (application) `my-project` package
		$ ls my-project
		Cargo.toml
		src
		$ ls my-project/src
		main.rs
		
		In the project directory, there’s a Cargo.toml file, giving us a package. 
		There’s also a src directory that contains main.rs. Inside Cargo.toml there’s no mention of src/main.rs. 
		Cargo follows a convention that src/main.rs is the crate root of a binary crate with the same name as the package. 
		
		Likewise, If the package directory contains src/lib.rs, the package contains a library crate with the same name as the package, and src/lib.rs is its crate root. 
		
		Cargo passes the crate root files to rustc to build the library or binary.
		
		If a package contains src/main.rs and src/lib.rs, it has two crates: a binary and a library, both with the same name as the package.
		A package can have multiple binary crates by placing files in the src/bin directory: each file will be a separate binary crate.

		src/main.rs and src/lib.rs are called crate roots. 
		The reason for their name is that the contents of either of these two files form a module named "crate" at the root of the crate’s module structure, known as the module tree.



7.2. Defining Modules to Control Scope and Privacy
	Modules Cheat Sheet
	
		Start from the crate root:
			When compiling a crate, the compiler first looks in the crate root file (src/lib.rs or src/main.rs) for code to compile.
			
		Declaring modules:
			In the crate root file, you can declare new modules
			If you declare a "garden" module with mod garden;. The compiler will look for the module’s code in these places:			
				Inline, within curly brackets that replace the semicolon following mod garden
				In the file src/garden.rs
				In the file src/garden/mod.rs
		
		Declaring submodules:
			In any file other than the crate root, you can declare submodules.
			you might declare mod vegetables; in src/garden.rs. The compiler will look for the submodule’s code within the directory named for the parent module in these places:
				Inline, directly following mod vegetables, within curly brackets instead of the semicolon
				In the file src/garden/vegetables.rs
				In the file src/garden/vegetables/mod.rs
							
		Paths to code in modules:
			Once a module is part of your crate, you can refer to code in that module from anywhere else in that same crate, as long as the privacy rules allow, using the path to the code.
			For example, an Asparagus type in the garden vegetables module would be found at crate::garden::vegetables::Asparagus.

		Private vs public:
			Code within a module is private from its parent modules by default. 
			To make a module public, declare it with pub mod instead of mod. 
			To make items within a public module public as well, use pub before their declarations.
			
		The use keyword:
			Within a scope, the use keyword creates shortcuts to items to reduce repetition of long paths.
			In any scope that can refer to crate::garden::vegetables::Asparagus, you can create a shortcut with 
			use crate::garden::vegetables::Asparagus; 
			and from then on you only need to write Asparagus to make use of that type in the scope.

		Example directory structure
		
			backyard
			├── Cargo.lock
			├── Cargo.toml
			└── src
				├── garden
				│	└── vegetables.rs
				├── garden.rs
				└── main.rs

	
	Grouping Related Code in Modules
		Modules let us organize code within a crate for readability and easy reuse
		Code within a module is private by default
		We can choose to make modules and the items within them public
		
		src/main.rs and src/lib.rs are called crate roots.
		The reason for their name is that the contents of either of these two files form a module named "crate" at the root of the crate’s module structure, known as the module tree.



7.3. Paths for Referring to an Item in the Module Tree

	A path can take two forms:

		1. Absolute path:	Full path starting from a crate root;
			for code from an external crate, the absolute path begins with the crate name
			for code from the current crate, it starts with the literal crate
		2. Relative path:	starts from the current module and uses self, super, or an identifier in the current module

		Both absolute and relative paths are followed by one or more identifiers separated by double colons (::).
		
		Example
		
			// Filename: src/lib.rs
			
			mod front_of_house {
				mod hosting {
					fn add_to_waitlist() {}
				}
			}

			pub fn eat_at_restaurant() {
				// Absolute path
				crate::front_of_house::hosting::add_to_waitlist();

				// Relative path
				front_of_house::hosting::add_to_waitlist();
			}


		The add_to_waitlist function is defined in the same crate as eat_at_restaurant, which means we can use the crate keyword to start an absolute path.
		Relative path starts with front_of_house, the name of the module defined at the same level of the module tree as eat_at_restaurant.
		Preference in general is to specify absolute paths
	
	
	Exposing Paths with the pub Keyword
		Items in a parent module can’t use the private items inside child modules, but items in child modules can use the items in their ancestor modules.
		
		pub:
			To expose inner parts of child modules’ code to outer ancestor modules use the pub keyword to make an item public
			The pub keyword on a module only lets code in its ancestor modules refer to it, not access its inner code.
			
			Because modules are containers, there’s not much we can do by only making the module public; so we need to make one or more of the items within the module public as well.
			
		Example
		
			// Filename: src/lib.rs
			
			mod front_of_house {
				pub mod hosting {
					pub fn add_to_waitlist() {}
				}
			}

			pub fn eat_at_restaurant() {
				// Absolute path
				crate::front_of_house::hosting::add_to_waitlist();

				// Relative path
				front_of_house::hosting::add_to_waitlist();
			}


	Starting Relative Paths with super
		We can construct relative paths that begin in the parent module, rather than the current module or the crate root, by using super at the start of the path.
		Using super allows us to reference an item that we know is in the parent module

		Example
		
			// Filename: src/lib.rs

			fn deliver_order() {}

			mod back_of_house {
				fn fix_incorrect_order() {
					cook_order();
					super::deliver_order();
				}

				fn cook_order() {}
			}


	Making Structs and Enums Public
		If we use pub before a struct definition, we make the struct public, but the struct’s fields will still be private. 
		We can make each field public or not on a case-by-case basis.
		
		In contrast, if we make an enum public, all of its variants are then public.
		


7.4. Bringing Paths Into Scope with the use Keyword

	use
		we can create a shortcut to a path with the use keyword once, and then use the shorter name everywhere else in the scope.
		By adding 
			use crate::front_of_house::hosting 
		in the crate root, hosting is now a valid name in that scope, just as though the hosting module had been defined in the crate root.
		
	Creating Idiomatic use Paths
		Bringing the function’s parent module into scope with use means we have to specify the parent module when calling the function.
		It makes it clear that the function isn’t locally defined
		
		When bringing in structs, enums, and other items with use, it’s idiomatic to specify the full path
			use std::collections::HashMap;
	
		Rust doesn’t allow to bring two items with the same name into scope with use statements.
		Use parent modules to distinguish the same name.
		
	Providing New Names with the as Keyword
		With use; after the path, we can specify as and a new local name, or alias, for the type.
		A name into a scope with the use keyword, is private.
		Combine pub and use to make it public
		This technique is called re-exporting because we’re bringing an item into scope but also making that item available for others to bring into their scope.
		
	Using External Packages
		1. add package to Cargo.toml
		2. Using use keyword bring the names that you require from package into scope
		
		Example: to use rand
			Cargo.toml
				rand = "0.8.5"
			
			use rand::Rng;

	Using Nested Paths to Clean Up Large use Lists
		If we’re using multiple items defined in the same crate or same module, we can use nested paths to bring the same items into scope in one line.
		We do this by specifying the common part of the path, followed by two colons, and then curly brackets around a list of the parts of the paths that differ.
		
		use std::{cmp::Ordering, io};
		
		We can use a nested path at any level in a path, which is useful when combining two use statements that share a subpath.
		Example
			use std::io;
			use std::io::Write;
			
			To merge these two paths into one use statement
			
			use std::io::{self, Write};
			
	The Glob Operator
		If we want to bring all public items defined in a path into scope, we can specify that path followed by the * glob operator:
		
			use std::collections::*;
		
		

7.5. Separating Modules into Different Files
	We can separate code for multiple module present in a single file; to there respective file as exaplained in section 7.2 Defining Modules to Control Scope and Privacy.
	
	src/front_of_house/hosting.rs		(what we covered)
	src/front_of_house/hosting/mod.rs	(older style, still supported path)
	
	If you use both styles for the same module, you’ll get a compiler error.

**********/



mod my_module;
use crate::my_module::{PUB_CONST_VAR, PUB_STATIC_VAR};
use crate::my_module::my_pub_submodule;


pub mod pub_mod {

    mod prv_mod {
        fn display() {
            println!("Inside my_pub_mod::priv_mod::display()");
        }
    }

    pub mod pub_mod {
        fn display() {
            println!("Inside my_pub_mod::publ_mod::display()");
        }
    }

}

mod prv_mod {

    mod prv_mod {
        pub fn display() {
            dbg!(println!("Inside my_pub_mod::priv_mod::display()"));
        }
    }

    pub mod pub_mod {
        pub fn display() {
            dbg!(println!("Inside my_pub_mod::publ_mod::display()"));
        }
    }

}

fn main() {


    dbg!(println!("Inside main"));
    println!();


    dbg!(println!("Accessing things of prv_mod"));
    // prv_mod is sibling module so it can be accessed
    dbg!(prv_mod::pub_mod::display());
    //dbg!(prv_mod::prv_mod::display());
    println!();

    dbg!(println!("Accessing things of pub_mod"));
    //dbg!(pub_mod::pub_mod::display());
    //dbg!(pub_mod::prv_mod::display());
    println!();


    dbg!(println!("Accessing things of my_module"));
    dbg!(crate::my_module::pub_fun());
    //crate::my_module::prv_fun();

    //dbg!(crate::my_module::CONST_VAR);
    //dbg!(crate::my_module::STATIC_VAR);
    
    dbg!(crate::my_module::PUB_CONST_VAR);
    dbg!(crate::my_module::PUB_STATIC_VAR);

    dbg!(PUB_CONST_VAR);
    dbg!(PUB_STATIC_VAR);

    println!();


    dbg!(println!("Accessing things of my_pub_submodule"));
    {
        let auser = crate::my_module::my_pub_submodule::user_mgmt::User::get();
        auser.display();

        dbg!(auser.name);
        //dbg!(auser.age);
    }

    /*
    {
        let auser = crate::my_module::my_pub_submodule::user_mgmt::User{
            name:   String::from("User-02"),
            //age:    21,
            //utype:  crate::my_module::my_pub_submodule::user_mgmt::UserType::SUPPORT 
        };
    }
    */
    println!();

    dbg!(my_pub_submodule::display());

}

/*****
    END OF FILE
**********/


