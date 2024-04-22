import websockets
import asyncio
import hello_pb2
import announcement_pb2

PORT = 7890
connected = set()

async def echo(websocket, path):
    print("a client just connected")
    connected.add(websocket)

    try:
        async for message_ in websocket:
            # print(dir(message_))
            # message = hello_pb2.HelloReply().FromString(message_)
            message = announcement_pb2.Announcement().FromString(message_)
            
            print('message received:')
            print(message)
            print(' ')
            for conn in connected:
                if conn != websocket:
                    await conn.send(f"someone said: {message_}")

    except websockets.exceptions.ConnectionClosed:
        print(f"a client just disconnected")
        
    finally:
        connected.remove(websocket)

if __name__ == "__main__":
    print(f"started the server @PORT: {PORT}")
    
    start_server = websockets.serve(echo, "localhost", PORT)

    asyncio.get_event_loop().run_until_complete(start_server)
    asyncio.get_event_loop().run_forever()