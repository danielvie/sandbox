# Copyright 2015 gRPC authors.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
"""The Python implementation of the GRPC hello.Greeter client."""

from __future__ import print_function

import logging

import grpc
import hello_pb2
import hello_pb2_grpc

def run():

    with grpc.insecure_channel('localhost:50051') as channel:

        stub = hello_pb2_grpc.GreeterStub(channel)

        # response = stub.SayHello(hello_pb2.HelloRequest(name='you'))
        # print("Greeter client received: " + response.message)
        
        # response = stub.SayHelloNro(hello_pb2.HelloNroRequest(name='eu', nro=1))
        # print("Greeter client received: " + response.message)

        response = stub.SayBogus(hello_pb2.BogusRequest(string="mandei um texto"))
        print("Greeter client received: " + response.message)

        response = stub.SayBogus(hello_pb2.BogusRequest(integer=8))
        print("Greeter client received: " + response.message)

        response = stub.SayBogus(hello_pb2.BogusRequest(boolean=True))
        print("Greeter client received: " + response.message)

        response = stub.SayBogus(hello_pb2.BogusRequest(decimal=8.89))
        print("Greeter client received: " + response.message)

#   string string = 1;
#   int64 integer = 2;
#   bool boolean = 3;
#   float decimal = 4;

if __name__ == '__main__':
    logging.basicConfig()
    run()
