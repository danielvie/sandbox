
trait LandCapable {
    fn drive(&self) {
        println!("Default drive");
    }
}

trait WaterCapable {
    fn float(&self) {
        println!("Default float");
    }
}
trait Amphibious : WaterCapable + LandCapable {}

struct Hovercraft;
impl Amphibious for Hovercraft {}
impl LandCapable for Hovercraft {
    fn drive(&self) {
        println!("Hovercraft driving");
    }
}

impl WaterCapable for Hovercraft {
}

fn traverse_frozen_lake(vehicle: &impl Amphibious) {
    vehicle.drive();
    vehicle.float();
}

struct Sedan;
impl LandCapable for Sedan {
    fn drive(&self) {
        println!("Sedan is driving");
    }
}

struct Suv;
impl LandCapable for Suv {}

fn road_trip(vehicle: &impl LandCapable) {
    vehicle.drive();
}


fn main() {
    let car = Sedan;
    road_trip(&car);
    
    let suv = Suv;
    road_trip(&suv);
    
    let hc = Hovercraft;
    traverse_frozen_lake(&hc);

}
