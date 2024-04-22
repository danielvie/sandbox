
use std::collections::HashMap;

fn main() {

    let mut marks = HashMap::new();
    
    // Add values
    marks.insert("Rust Programming", 96);
    marks.insert("Web Development", 94);
    marks.insert("UX Design", 75);
    marks.insert("Professional Computing Studies", 45);
    

    // Find length of HashMap
    println!("How many? {}", marks.len());

    
    // Get value
    match marks.get("Web Development") {
        Some(mark) => println!("You got {} for Web Dev!", mark),
        None => println!("You didnt study Web Development")
    }

    
    // Remove value
    marks.remove("UX Design");
    

    // Loop through HashMap
    for (subject, mark) in &marks {
        println!("For {}, you got {}", subject, mark);
    }
    
    // Check for value
    println!("Did you study C++? {}", marks.contains_key("C++ Programming"));

}
