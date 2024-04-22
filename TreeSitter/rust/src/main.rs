use tree_sitter::{Parser, TreeCursor};

fn main() {
  let code = "
fn fibonacci(n: u32) -> u32 {
  match n {
    0 => 0,
    1 => 1,
    n => fibonacci(n-1) + fibonacci(n-2), 
  }
}
";

  let mut parser = Parser::new();
  parser.set_language(tree_sitter_rust::language()).expect("Error loading Rust grammar");

  let tree = parser.parse(code, None).unwrap();

  let mut cursor = tree.walk();

  println!("{:#?}", tree.root_node());
  
  walk(&mut cursor, 0);
}

// Recursively walk and print syntax tree
fn walk(cursor: &mut TreeCursor, depth: usize) {
    let mut nodes_to_visit = vec![];
    
    for node in cursor.node().children(cursor) {
        nodes_to_visit.push(node);
    }

    for node in nodes_to_visit {
        println!("{:#?}", node);
    
        if node.kind() != "comment" {
            cursor.goto_first_child();
            walk(cursor, depth + 1);
            cursor.goto_parent();  
            cursor.goto_next_sibling();
        }
    }
}
