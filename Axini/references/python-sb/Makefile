protodir = ./Protos
protodir_test = ./Protos_grpc_test

python = python

all: python-lab3-wsclient

# help instruction
h: help

b: build-proto

help:
	$(python) z_help.py

# python script lab1
python-lab1:
	$(python) adapter_lab1.py

# python script lab2
python-lab2:
	$(python) adapter_lab2.py

# python script lab3
python-lab3:
	$(python) adapter_lab3.py

# python script lab3 using websocket-client
python-lab3-wsclient:
	$(python) adapter_lab3_wsclient.py

# build protobuf axini example
build-proto:
	$(python) -m grpc_tools.protoc -I$(protodir) --python_out=. $(protodir)/announcement.proto
	$(python) -m grpc_tools.protoc -I$(protodir) --python_out=. $(protodir)/announcements.proto
	$(python) -m grpc_tools.protoc -I$(protodir) --python_out=. $(protodir)/configuration.proto
	$(python) -m grpc_tools.protoc -I$(protodir) --python_out=. $(protodir)/label.proto
	$(python) -m grpc_tools.protoc -I$(protodir) --python_out=. $(protodir)/message.proto

# clean protobuf files
clean:
	fd -d 1 -u _pb2(_grpc)?\.py -x rm {}
	