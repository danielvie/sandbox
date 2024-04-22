use std::os::macos;



fn main() {

    // ---- Ownership rules -----
    // 1. Each value in Rust has a variable tha's called its owner
    // 2. There can only be one owner at a time
    // 3. When the owner goes out of scope, the value will be dropped

    let s = String::from("hello");
    takes_ownership(s);
    println!("{}", s);

    let x: i32 = 5;
    makes_copy(x);
    println!("{}", x);
    
}

fn takes_ownership(some_string: String) {
    println!("{}", some_string);
}

fn makes_copy(some_integer: i32) {
    println!("{}", some_integer);
}
