import message_pb2
import announcement_pb2
import configuration_pb2
from enum import Enum

class URL(Enum):
    AXINI = 0
    SMARTDOOR = 1

def GetAnnouncementMessage(name = 'my-adapter (daniel)'):
    # configuration = configuration_pb2.Configuration()
    # item = configuration_pb2.Configuration.Item()
    # item.key = "url"
    # item.description = "WebSocket URL"
    # item.string = "dfasdf"

    announcement = announcement_pb2.Announcement(name = name)
    
    message = message_pb2.Message(announcement = announcement)
    
    return message.SerializeToString()

def GetToken():
    token = 'eyJ0eXAiOiJKV1QiLCJhbGciOiJIUzI1NiJ9.eyJleHAiOjE2ODI2ODQ5NjUsInN1YiI6ImRhbmllbC52aWVpcmFAaWN0Lm5sIiwiaXNzIjoidm1wdWJsaWNwcm9kMDEiLCJzY29wZSI6ImFkYXB0ZXIifQ.2YdsV6QZCR0nfdmA1s2UCamqx8rpscxdON5qk_JNTHs'
    return token
    
def GetUrlAxini():
    url = "wss://course02.axini.com:443/adapters"
    return url

def GetUrl(url:URL):
    if url == URL.AXINI:
        return GetUrlAxini()
    if url == URL.SMARTDOOR:
        return GetUrlSmartDoor()

def GetUrlSmartDoor():
    url = "ws://localhost:3001"
    return url
    
def GetHeaders():
    headers = {
        "Authorization" : "Bearer " + GetToken()
    }    
    return headers