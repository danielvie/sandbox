# // WEBSOCKET STUFF
# const serverAddress    = "wss://my-websocket-server-echo.glitch.me/"
# const serverConnection = new WebSocket(serverAddress)

# serverConnection.onopen = () => {
#     console.log(`I just connected to the server on '${serverAddress}'`)
#     // serverConnection.send("hello server, from p5js")
# }

# serverConnection.onmessage = function(event) {
#   console.log(event.data)
  
#   let obj = JSON.parse(event.data)
  
#   obj.x *= width
#   obj.y *= height
  
#   target  = obj
# }

import asyncio
import websockets

async def hello():
    async with websockets.connect('wss://my-websocket-server-echo.glitch.me/') as websocket:
        name = 'bla'
        await websocket.send(name)
        print(f"> {name}")
        
        greeting = await websocket.recv()
        print("greeting >> ", greeting)
    

if __name__ == "__main__":
    
    asyncio.get_event_loop().run_until_complete(hello())