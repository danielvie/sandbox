use std::collections::HashMap;
use std::path::Path;

struct Node {
    children: HashMap<String, Node>,
}

impl Node {
    fn new() -> Self {
        Node {
            children: HashMap::new(),
        }
    }

    fn insert_path(&mut self, path: &Path) {
        let mut current_node = self;

        for part in path.components() {
            if let Some(part_str) = part.as_os_str().to_str() {
                current_node = current_node.children.entry(part_str.to_owned()).or_insert_with(Node::new);
            }
        }
    }
}

fn main() {
    let params = [
        "A       lib/sub/subsub/l7.h",
        "A       lib/sub/subsub/l8.h",
        "A       lib/sub/subsub/l9.h",
        "A       lib/sub/subsub/l10.h",
        "A       src/bla.txt",
        "A       src/ble.txt",
    ];

    let mut tree = Node::new();

    for param in &params {
        if let Some(captures) = regex::Regex::new(r"(?P<type>[A-Z])\s+(?P<param>[\w/\\.]+)").unwrap().captures(param) {
            let path = Path::new(captures.name("param").unwrap().as_str());
            tree.insert_path(path);
        }
    }
    
    println!("ending");
    println!("ending");
    println!("ending");
    println!("ending");
    // println!("{:#?}", tree);
}