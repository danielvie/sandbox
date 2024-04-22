import websockets
import asyncio

async def listen():
    # url = "ws://my-websocket-server-echo.glitch.me"
    url = "ws://localhost:7890"
    
    async with websockets.connect(url) as ws:
        await ws.send("Hello server!")
        while True:
            msg = await ws.recv()
            print(msg)

if __name__ == "__main__":
    
    # run this function async and wait until everything is complete
    # asyncio.get_event_loop().run_until_complete(listen())
    asyncio.get_event_loop().run_until_complete(listen())