using Grpc.Core;
using GrpcGreeter;

namespace GrpcGreeter.Services;

public class GreeterService : Greeter.GreeterBase
{
    private readonly ILogger<GreeterService> mLogger;
    public GreeterService(ILogger<GreeterService> logger)
    {
        mLogger = logger;
    }

    public override Task<HelloReply> SayHello(HelloRequest request, ServerCallContext context)
    {
        Console.WriteLine("entrei em `SayHello`!");
        return Task.FromResult(new HelloReply
        {
            Message = "Hello " + request.Name
        });
    }

    public override Task<BogusReply> SayBogus(BogusRequest request, ServerCallContext context)
    {
        Console.WriteLine("entrei em `SayBogus`!");

        string msg = "entrei em `SayBogus`!";
        // check bogus
        
        
        if (request.TypeCase == BogusRequest.TypeOneofCase.Boolean)
        {
            msg = $"eu sou um boolean, valor: `{request.Boolean}`";
        }
        else if (request.TypeCase == BogusRequest.TypeOneofCase.Integer)
        {
            msg = $"eu sou um integer, valor: `{request.Integer}`";
        }
        else if (request.TypeCase == BogusRequest.TypeOneofCase.Decimal)
        {
            msg = $"eu sou um Decimal, valor: `{request.Decimal}`";
        }
        else if (request.TypeCase == BogusRequest.TypeOneofCase.String)
        {
            msg = $"eu sou um String, valor: `{request.String}`";
        }


        return Task.FromResult(new BogusReply
        {
            Message = $"{msg}"
        });
    }
    
}
