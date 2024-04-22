// src/main.rs
use wasm_bindgen::prelude::*;

extern "C" {
    fn cpp_function();
}

fn main() {
    unsafe {
        println!("Hello from Rust!");
        let value = cpp_function();
        println!("hei {}", value);
    }
}
