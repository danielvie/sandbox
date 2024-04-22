use wasm_bindgen::prelude::*;

// src/lib.rs
// #[link(name = "add", kind = "dylib", dead_strip, path = "cpp")]
// #[link(name = "add", kind = "dylib")]
pub extern "C" fn add(a: i32, b: i32) -> i32 {
    a + b
};


#[wasm_bindgen]
pub fn rust_add(a: i32, b: i32) -> i32 {
    a + b
}

// #[wasm_bindgen]
// pub fn cpp_add(a: i32, b: i32) -> i32 {
//     unsafe {
//         add(a, b)
//     }
// }