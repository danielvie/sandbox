import websockets
import asyncio

PORT = 7890

async def echo(websocket, path):
    print("a client just connected")

    try:
        async for message in websocket:
            print(f"received message from `{message}`")
            await websocket.send(f"back `{message}`")

    except websockets.exceptions.ConnectionClosed:
        print(f"a client just disconnected")

if __name__ == "__main__":
    print(f"started the server @PORT: {PORT}")
    
    start_server = websockets.serve(echo, "localhost", PORT)

    asyncio.get_event_loop().run_until_complete(start_server)
    asyncio.get_event_loop().run_forever()