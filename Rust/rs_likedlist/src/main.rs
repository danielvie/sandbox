


#[derive(Debug)]
pub struct LinkedList<T>(Option<(T, Box<LinkedList<T>>)>);

impl<T> LinkedList<T>{
    pub fn new() -> Self {
        LinkedList(None)
    }
    
    pub fn push_front(&mut self, data:T){
        let t = self.0.take();
        self.0 = Some((data, Box::new(LinkedList(t))));
    }
    
    pub fn push_back
}

fn main() {
    println!("Hello, world!");
}
