use std::{io, fs};

// GET LIST OF FILES
fn get_files_in_folder() -> Result<Vec<String>, io::Error> {
    // getting current working dir
    let root = std::env::current_dir()?;
    
    // defining max deaph for recursive search
    let max_depth:i32 = 3;

    get_files_in_folder_helper(root.to_str().unwrap(), max_depth, 0)
}

fn get_files_in_folder_helper(path: &str, max_depth: i32, depth: i32) -> Result<Vec<String>, io::Error> {
    let entries = fs::read_dir(path)?;
    let mut files = Vec::new();
    
    // if depth is greater than `max_depth`
    if depth >= max_depth {
        return Ok(files)
    }
    
    // read path of entries
    for entry in entries {
        let path_i = entry?.path();
        
        // save to vector if its file
        if path_i.is_file() {
            files.push(path_i.to_string_lossy().to_string());
            continue;
        }

        // search directory if dir
        if path_i.is_dir() {
            files.append(&mut get_files_in_folder_helper(path_i.to_str().unwrap(), max_depth, depth + 1)?);
        } 
    }

    Ok(files)
}

// READ FILE


// MAIN
fn main() {

    let files = get_files_in_folder();
    
    println!("{:?}", files);
    println!("Hello, world!");
}