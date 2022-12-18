// stating a new HelloGrpc

using System.Threading.Tasks;
using Grpc.Net.Client;
using GrpcGreeter;

namespace HelloGrpc
{
    class Program
    {
        static async Task Main(string[] args)
        {
            // The port number must match the port of the gRPC server.
            using var channel = GrpcChannel.ForAddress("http://localhost:50051");
            var client = new Greeter.GreeterClient(channel);
            var reply = await client.SayHelloAsync(
                            new HelloRequest { Name = "GreeterClient" });
            Console.WriteLine("Greeting: " + reply.Message);

            var replyBogus = await client.SayBogusAsync(
                            new BogusRequest { Decimal = 9.3f});

            Console.WriteLine("Greeting: " + replyBogus.Message);
        }
    }
}