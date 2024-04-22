// def DummyData():
//     params = [
//         'M       main.py', 
//         'M       Makefile', 
//         'A       lib/lib1.h', 
//         'A       lib/lib2.h', 
//         'A       lib/sub/l3.h', 
//         'A       lib/sub/l4.h', 
//         'A       lib/sub/l5.h', 
//         'A       lib/sub/subsub/l7.h', 
//         'A       lib/sub/subsub/l8.h', 
//         'A       lib/sub/subsub/l9.h', 
//         'A       lib/sub/subsub/l10.h', 
//         'A       src/bla.txt', 
//         'A       src/ble.txt', 
//     ]
//     return params
fn dummy_data() -> Vec<&'static str> {
    vec![
        "M       main.py",
        "M       Makefile",
        "A       lib/lib1.h",
        "A       lib/lib2.h",
        "A       lib/sub/l3.h",
        "A       lib/sub/l4.h",
        "A       lib/sub/l5.h",
        "A       lib/sub/subsub/l7.h",
        "A       lib/sub/subsub/l8.h",
        "A       lib/sub/subsub/l9.h",
        "A       lib/sub/subsub/l10.h",
        "A       src/bla.txt",
        "A       src/ble.txt",
    ]
}

struct Tree {
    root: Option<Vec<Box<Node>>>,
}

struct Node {
    value: String,
    children: Option<Vec<Box<Node>>>,
}

impl Node {
    fn new(value: String) -> Self {
        Node {
            value,
            children: None,
        }
    }

    // fn find_child(&self, value: &str) -> Option<&Box<Node>> {
    //     self.children.as_ref()?.iter().find(|node| node.value == value)
    // }

    // fn insert_child(&mut self, value: String) {
    //     if self.find_child(&value).is_none() {
    //         if self.children.is_none() {
    //             self.children = Some(Vec::new());
    //         }

    //         self.children.as_mut().unwrap().push(Box::new(Node::new(value)));
    //     }
    // }
    
    fn print_with_indentation(&self, indent: usize) {
        for _ in 0..indent {
            print!("  ");  // Using two spaces for indentation.
        }
        println!("{}", self.value);

        if let Some(children) = &self.children {
            for child in children {
                child.print_with_indentation(indent + 1);
            }
        }
    }
}

impl Tree {
    fn new() -> Self {
        Tree { root: None }
    }

    fn insert(&mut self, path: &str) {
        let parts: Vec<&str> = path.split('/').collect();
        if self.root.is_none() {
            self.root = Some(Vec::new());
        }

        let mut current_nodes = &mut self.root;

        for part in parts {
            let current_value = part.to_string();
            let node_exists = current_nodes.as_ref().unwrap().iter().any(|node| node.value == current_value);
            if node_exists {
                let node = current_nodes.as_mut().unwrap().iter_mut().find(|node| node.value == current_value).unwrap(); 
                if node.children.is_none() {
                    node.children = Some(Vec::new());
                }
                current_nodes = &mut node.children;
            } else {
                let mut new_node = Node::new(current_value);
                new_node.children = Some(Vec::new());
                current_nodes.as_mut().unwrap().push(Box::new(new_node));
                current_nodes = &mut current_nodes.as_mut().unwrap().last_mut().unwrap().children;
            }
        }
    }
    
    fn print(&self) {
        if let Some(root_nodes) = &self.root {
            for node in root_nodes {
                node.print_with_indentation(0);
            }
        }
    }
}



fn main() {
    
    let mut tree = Tree::new();
    for data in dummy_data() {
        tree.insert(data);
    }
    
    tree.print();

    let _bla = 1;
}

// cargo run
//     Finished dev [unoptimized + debuginfo] target(s) in 0.00s
//      Running `/Users/danielvieira/Sandbox/RUST/rs_tree/target/debug/rs_tree`
// M       main.py
// M       Makefile
// A       lib
//   lib1.h
//   lib2.h
//   sub
//     l3.h
//     l4.h
//     l5.h
//     subsub
//       l7.h
//       l8.h
//       l9.h
//       l10.h
// A       src
//   bla.txt
//   ble.txt