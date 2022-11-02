use tonic::{transport::Server, Request, Response, Status};

use helloworld::greeter_server::{Greeter, GreeterServer};
use helloworld::{HelloNroRequest, HelloReply, HelloRequest};

pub mod helloworld
{
    tonic::include_proto!("helloworld");
}

#[derive(Debug, Default)]
pub struct GreeterService {}

#[tonic::async_trait]
impl Greeter for GreeterService
{
    async fn say_hello_nro(&self, request: Request<HelloNroRequest>)
            -> Result<Response<HelloReply>, Status>
    {
        let req = request.into_inner();
        println!("recebi mensagem com name: {name} e nro: {nro}", name = req.name, nro = req.nro);

        let reply = HelloReply
        {
            message : format!("return message from rust: name = {name}, nro = {nro}", name = req.name, nro = req.nro).into()
        };

        Ok(Response::new(reply))
    }

    async fn say_hello(&self, request: Request<HelloRequest>)
            -> Result<Response<HelloReply>, Status>
    {
        let req = request.into_inner();
        println!("recebi mensagem com name: {:?}", req.name);

        let reply = HelloReply
        {
            message : "return message from rust server".to_owned()
        };

        Ok(Response::new(reply))
    }
}

#[tokio::main]
async fn main() -> Result<(), Box<dyn std::error::Error>>
{
    let addr = "[::1]:50051".parse()?;
    let hello_service = GreeterService::default();

    Server::builder()
        .add_service(GreeterServer::new(hello_service))
        .serve(addr)
        .await?;

    Ok(())
}