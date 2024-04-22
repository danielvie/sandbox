import websockets
import asyncio
import announcement_pb2
import label_pb2
import message_pb2
import configuration_pb2
import getters

# LAB 2: connect to Axini


async def listen():
    
    headers = {
        "Authorization" : "Bearer "+getters.GetToken()
    }
    url = "wss://course02.axini.com:443/adapters"

    async with websockets.connect(url, extra_headers=headers) as ws:

        message = CreateMessage()

        await ws.send(message.SerializeToString())
        while True:
            ret = await ws.recv()
            print(ret)
            
def CreateMessage():
    # lab1 create a message of the announcement with the labels
    # label = label_pb2.Label()
    # label.type = label.LabelType.STIMULUS
    # label.label = 'open'
    
    # configuration = configuration_pb2.Configuration()
    # item = configuration.Item()
    # item.key = 'my-item'
    # item.string = 'test'
    # configuration.items.append(item) 

    # message = message_pb2.Message(label = label)
    announcement = CreateAnnouncement()
    message = message_pb2.Message(announcement = announcement)
    
    return message

def CreateAnnouncement():
    announcement = announcement_pb2.Announcement()
    announcement.name = 'my-adapter (daniel)'
    
    return announcement

if __name__ == "__main__":
    
    message = CreateMessage()
    # message.label = label

    # print(label)
    # print(configuration)
    # print(message)

    # run this function async and wait until everything is complete
    asyncio.get_event_loop().run_until_complete(listen())
    

    # asyncio.get_event_loop().run_until_complete(listen())