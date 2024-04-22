
// mod tests {
//     use std::env::current_exe;
//     use super::*;
//     #[test]
//     fn works_build_list() {
//         let mut list = List::new();
//         list.push(5);
//         list.push(4);
//         list.push(3);
//         list.push(2);
//         list.push(1);
//         assert_eq!(list.head.is_some(), true);
//     }
// }

// #[derive(PartialEq, Eq, Clone, Debug)]
struct Node {
    pub value: i32,
    pub next: Option<Box<Node>>
}

impl Node {
    #[inline]
    fn new(value: i32) -> Self {
        Node { 
            value,
            next: None 
        }
    }
}

struct LinkedList {
    head: Option<Box<Node>>,
}

impl LinkedList {
    fn new() -> Self {
        LinkedList { head: None }
    }
    
    fn push(&mut self, value: i32) {
        let mut new_node = Box::new(Node::new(value));
        match self.head.take() {
            Some(old_head) => {
                new_node.next = Some(old_head);
                self.head = Some(new_node);
            }
            None => self.head = Some(new_node),
        }
    }
    
    fn print(&self) {
        let mut current = &self.head;
        while let Some(node) = current {
            println!("{}", node.value);
            current = &node.next;
        }
    }

    fn reverse_list(&self) -> LinkedList {
        let mut reversed_list = LinkedList::new();
        let mut current = &self.head;
        while let Some(node) = current {
            reversed_list.push(node.value);
            current = &node.next;
        }
        reversed_list
    }
}

fn reverse_list(list: &LinkedList) -> LinkedList {
    let mut reversed_list = LinkedList::new();
    let mut current = &list.head;
    while let Some(node) = current {
        reversed_list.push(node.value);
        current = &node.next;
    }
    reversed_list
}


struct Solution;

impl Solution {
    pub fn reverse_list(head: Option<Box<Node>>) -> Option<Box<Node>> {
        let mut new_node = None;
        let mut original_node = head;
        
        while let Some(mut node) = original_node {
            original_node = node.next;
            node.next = new_node;
            new_node = Some(node);
        }
        return new_node;
    }
}


fn main() {
    
    let mut list = LinkedList::new();
    
    list.push(1);
    list.push(2);
    list.push(3);
    list.push(4);
    
    let list2 = Solution::reverse_list(list);

    list.print();
}
