// https://www.youtube.com/watch?v=TJTDTyNdJdY

#[derive(Debug)]
struct SomeStruct {
    num: i32,
}

fn print_some_struct(the_struct: &SomeStruct) {
    println!("{:?}", the_struct)
}

fn mutate_struct(the_struct: &mut SomeStruct) {
    the_struct.num = 6;
}

// lifetime: 'a
fn biggest<'a>(a: &'a SomeStruct, b: &'a SomeStruct) -> &'a SomeStruct {
    if a.num > b.num {
        a
    } else {
        b
    }
}

fn main() {
    let mut some_struct: SomeStruct = SomeStruct { num: 3 };
    print_some_struct(&some_struct);
    mutate_struct(&mut some_struct);
    print_some_struct(&some_struct);

    // lifetime
    // let bigger: SomeStruct;
    // {
    //     let other_struct = SomeStruct { num: 5 };
    //     bigger = biggest(&some_struct, &other_struct);
    // }

    let some_struct = SomeStruct { num: 3 };
    let other_struct = SomeStruct { num: 5 };
    let bigger = biggest(&some_struct, &other_struct);
    print_some_struct(bigger);
}

// :: terminal

//    Compiling rs_desmystified v0.1.0 (/Users/danielvieira/Sandbox/RUST/rs_desmystified)
//     Finished dev [unoptimized + debuginfo] target(s) in 0.25s
//      Running `/Users/danielvieira/Sandbox/RUST/rs_desmystified/target/debug/rs_desmystified`
// SomeStruct { num: 3 }
// SomeStruct { num: 6 }
// SomeStruct { num: 5 }