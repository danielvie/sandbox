// build.rs

use std::process::Command;

fn main() {
    Command::new("wasm-pack")
        .arg("build")
        .arg("--target")
        .arg("web")
        .output()
        .expect("Failed to execute wasm-pack");
}
