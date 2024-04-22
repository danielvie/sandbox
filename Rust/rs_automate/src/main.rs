use mouse_rs::{types::keys::Keys, Mouse};

fn move_and_press() {
    let mouse = Mouse::new();
    mouse.move_to(1500, 500).expect("Unable to move mouse");
    mouse.press(&Keys::RIGHT).expect("Unable to press button");
    mouse.release(&Keys::RIGHT).expect("Unable to release button");
}

fn main() {
    move_and_press();
    println!("asdfasdfasdf");
}