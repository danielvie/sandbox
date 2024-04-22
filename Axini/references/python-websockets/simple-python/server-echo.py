import websockets
import asyncio

PORT = 7890
connected = set()

async def echo(websocket, path):
    print("a client just connected")
    connected.add(websocket)

    try:
        async for message in websocket:
            print(f"received message from `{message}`")
            for conn in connected:
                if conn != websocket:
                    await conn.send(f"someone said: {message}")

    except websockets.exceptions.ConnectionClosed:
        print(f"a client just disconnected")
        
    finally:
        connected.remove(websocket)

if __name__ == "__main__":
    print(f"started the server @PORT: {PORT}")
    
    start_server = websockets.serve(echo, "localhost", PORT)

    asyncio.get_event_loop().run_until_complete(start_server)
    asyncio.get_event_loop().run_forever()