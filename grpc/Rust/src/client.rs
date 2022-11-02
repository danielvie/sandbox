// use hello
// use helloworld::HelloRequest;

use helloworld::greeter_client::GreeterClient;
use helloworld::HelloNroRequest;

pub mod helloworld
{
    tonic::include_proto!("helloworld");
}

#[tokio::main]
async fn main() -> Result<(), Box<dyn std::error::Error>>
{
    let mut client = GreeterClient::connect(
        "http://[::1]:50051"
    ).await?;

    let request = tonic::Request::new(
        HelloNroRequest
        {
            name : "daniel from rust".to_owned(),
            nro : 89,
        }
    );

    let response = client.say_hello_nro(request).await?;

    println!("RESPONSE={:?}", response);

    Ok(())
}