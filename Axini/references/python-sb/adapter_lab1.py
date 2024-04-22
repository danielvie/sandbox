import websockets
import asyncio
import announcement_pb2
import label_pb2
import message_pb2
import configuration_pb2

# depencencies: 
#   > make b

async def listen():
    # url = "ws://my-websocket-server-echo.glitch.me"
    # url = "wss://course02.axini.com:443/adapters"
    url = "ws://localhost:3001"
    
    async with websockets.connect(url) as ws:
        message = CreateMessage()
        print('send:', message)

        await ws.send('RESET')
        while True:
            ret = await ws.recv()
            print(ret)
            
def CreateMessage():
    # lab1 create a message of the announcement with the labels
    label = label_pb2.Label()
    label.type = label.LabelType.STIMULUS
    label.label = 'open'
    
    configuration = configuration_pb2.Configuration()
    item = configuration.Item()
    item.key = 'my-item'
    item.string = 'test'
    configuration.items.append(item) 

    # message = message_pb2.Message(label = label)
    message = message_pb2.Message(label = label)
    
    return message

if __name__ == "__main__":
    
    message = CreateMessage()
    # message.label = label

    # print(label)
    # print(configuration)
    # print(message)

    # run this function async and wait until everything is complete
    asyncio.get_event_loop().run_until_complete(listen())
    

    # asyncio.get_event_loop().run_until_complete(listen())