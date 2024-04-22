// src/lib.rs

use wasm_bindgen::prelude::*;

#[wasm_bindgen]
extern "C" {
    fn alert(s: &str);
}

#[wasm_bindgen]
extern "C" {
    fn log_to_console(message: &str);
}

#[wasm_bindgen]
pub fn run() {
    unsafe {
        let result = cpp_function();
        log_to_console(&format!("Result from C++ function: {}", result));
    }
}

#[wasm_bindgen]
extern "C" {
    fn cpp_function() -> i32;
}