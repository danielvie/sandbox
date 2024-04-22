use nom::{
    branch::alt,
    character::complete::{alfanumeric1, char, multispace0}, // Add alphanumeric1 import
    combinator::recognize,
    multi::separated_list0,
    sequence::{delimited, preceded, tuple},
    IResult,
};

// Define the basic elements of Julia syntax
fn identifier(input: &str) -> IResult<&str, &str> {
    recognize(tuple((char('_'), alt((char('_'), nom::alphanumeric1)))))(input)
}

fn parameter(input: &str) -> IResult<&str, &str> {
    preceded(multispace0, identifier)(input)
}

fn parameters(input: &str) -> IResult<&str, Vec<&str>> {
    delimited(
        char('('),
        separated_list0(char(','), parameter),
        char(')'),
    )(input)
}

fn function(input: &str) -> IResult<&str, (&str, Vec<&str>)> {
    tuple((identifier, parameters))(input)
}

fn main() {
    let julia_function = "add_numbers(x, y) = x + y";
    match function(julia_function) {
        Ok((_, (name, params))) => {
            println!("Function Name: {}", name);
            println!("Parameters: {:?}", params);
        }
        Err(err) => println!("Error: {:?}", err),
    }
}
