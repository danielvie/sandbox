import websockets
import asyncio
import announcement_pb2
import label_pb2
import message_pb2
import configuration_pb2
from pathlib import Path

# LAB 3: implement components of adapter with axini design


# connect to AMP: method connect
# • implement callback methods: onOpen, onClose, onError, onMessage

TOKEN = 'eyJ0eXAiOiJKV1QiLCJhbGciOiJIUzI1NiJ9.eyJleHAiOjE2ODI2ODQ5NjUsInN1YiI6ImRhbmllbC52aWVpcmFAaWN0Lm5sIiwiaXNzIjoidm1wdWJsaWNwcm9kMDEiLCJzY29wZSI6ImFkYXB0ZXIifQ.2YdsV6QZCR0nfdmA1s2UCamqx8rpscxdON5qk_JNTHs'

async def listen():
    
    headers = {
        "Authorization" : "Bearer "+TOKEN
    }
    url = "wss://course02.axini.com:443/adapters"
    url = "ws://localhost:3001"

    async with websockets.connect(url, extra_headers=headers) as ws:
        try:
            # event handler for onConnect
            print("connected to server")

            # event handler for onOpen
            await ws.send("RESET")
            
            # event handler for onMessage
            response = await ws.recv()
            print(response)
            
            while True:
                response = await ws.recv()
                print("received new message")
                print(response)

        except websockets.exceptions.ConnectionClosedError:
            # event handler for onError
            print("connection closed")

    

def CreateMessage():
    announcement = CreateAnnouncement()
    message = message_pb2.Message(announcement = announcement)
    
    return message.SerializeToString()

def CreateAnnouncement():
    announcement = announcement_pb2.Announcement()
    announcement.name = 'my-adapter (daniel)'
    
    return announcement
    
if __name__ == "__main__":
    
    # message = CreateMessage()
    # message.label = label

    # print(label)
    # print(configuration)
    # print(message)

    asyncio.get_event_loop().run_until_complete(listen())
    
    
    print('lab3')
    

    # asyncio.get_event_loop().run_until_complete(listen())