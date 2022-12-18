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
"""The Python implementation of the GRPC hello.Greeter server."""

from concurrent import futures
import logging

import grpc
import hello_pb2
import hello_pb2_grpc

class Greeter(hello_pb2_grpc.GreeterServicer):

    def SayHello(self, request, context):
        print('recebi mensagem:', request.name)
        return hello_pb2.HelloReply(message='Hello from python server, your message is: `%s`!' % request.name)

    def SayHelloNro(self, request, context):
        msg = f'Hello, {request.name}, {request.nro}!'
        print(msg)
        return hello_pb2.HelloReply(message=msg)
    
    def SayBogus(self, request, context):
        
        msg = 'error, nao sei que tipo eh isso'
        
        if request.string:
            msg = f"isso foi uma string, value: `{request.string}`"
        elif request.integer:
            msg = f"isso foi um integer, value: `{request.integer}`"
        elif request.decimal:
            msg = f"isso foi um decimal, value: `{request.decimal}`"
        elif request.boolean:
            msg = f"isso foi um boolean, value: `{request.boolean}`"

        print('request:')
        print(request)
        print('end request:')
        return hello_pb2.BogusReply(message=msg)

def serve():
    server = grpc.server(futures.ThreadPoolExecutor(max_workers=10))
    hello_pb2_grpc.add_GreeterServicer_to_server(Greeter(), server)
    server.add_insecure_port('[::]:50051')
    server.start()
    server.wait_for_termination()


if __name__ == '__main__':
    logging.basicConfig()
    serve()