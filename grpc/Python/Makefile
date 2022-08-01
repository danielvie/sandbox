
protodir = ../Protos

b: build

s:
	python greeter_server.py

c:
	python greeter_client.py

build:
	python -m grpc_tools.protoc -I$(protodir) --python_out=. --grpc_python_out=. $(protodir)/hello.proto