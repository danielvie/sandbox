
all: r

i: install

l: list

r: run

b: build

run:
	dotnet run

build:
	dotnet build

install:
	dotnet add GrpcGreeterClient.csproj package Grpc.Net.Client
	dotnet add GrpcGreeterClient.csproj package Google.Protobuf
	dotnet add GrpcGreeterClient.csproj package Grpc.Tools
	
list:
	dotnet list package