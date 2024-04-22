
// Box::
// trait Vehicle {
//     fn drive(&self);
// }

// struct Truck {
//     next_truck: Option<Box<Truck>>,
// }

// impl Vehicle for Truck {
//     fn drive(&self) {
//         println!("Truck is driving");
//     }
// }

use std::sync::Arc;

#[derive(Debug)]
struct Truck {
    capacity: i32,
}

fn main() {
    // Box::
    // let t = Box::new(Truck { next_truck: None});
    
    let (truck_a, truck_b, truck_c) = (
        Arc::new(Truck { capacity: 1}),
        Arc::new(Truck { capacity: 2}),
        Arc::new(Truck { capacity: 3}),
    );


    let thread = std::thread::spawn(move || {
        let facility_one = vec![Arc::clone(&truck_a), Arc::clone(&truck_b)];
        let facility_two = vec![Arc::clone(&truck_b), Arc::clone(&truck_c)];
        (facility_one, facility_two)
    });

    let (facility_one, facility_two) = thread.join().unwrap();
    
    println!("facility one {:?}", facility_one);
    println!("facility two {:?}", facility_two);


    let truck_b = Arc::clone(&facility_one[1]);
    println!("Truck b strong count: {:?}", Arc::strong_count(&truck_b));
    
    std::mem::drop(facility_two);

    println!("Truck b strong count: {:?}", Arc::strong_count(&truck_b));
    println!("facility one after drop {:?}", facility_one);
}
