import asyncio
import websockets

msg = '213'

async def hello():
    async with websockets.connect('wss://my-websocket-server-echo.glitch.me/') as websocket:
        name = 'bla'
        await websocket.send(name)
        print(f"> {name}")
        
        greeting = await websocket.recv()
        print("greeting >> ", greeting)
    

if __name__ == "__main__":
    print('my name is: ', name)
    asyncio.get_event_loop().run_until_complete(hello())