import websocket
import threading
import rel
import getters
from getters import URL
import message_pb2
from Logger import Logger
from AxiniCommon.AdapterCore import AdapterCore
from AxiniCommon.BrokerConnection import BrokerConnection
from SmartDoorHandler import SmartDoorHandler

# Adapter: starts the BrokerConnection and AdapterCore
class Adapter():
    def __init__(self):
        self.logger = Logger('Adapter')

    def run(self, name:str, url:str, token:str):
        # try:
            brokerConnection = BrokerConnection(url, token, enableTrace=False)
            handler = SmartDoorHandler()
            adapterCore = AdapterCore(name, brokerConnection, handler)
            # name:str, brokerConnection:BrokerConnection, handler:Handler
            
            brokerConnection.registerAdapterCore(adapterCore)
            handler.registerAdapterCore(adapterCore)
            adapterCore.start()

        # except:
        #     self.logger.error('Adapter', 'algo nao deu certo')
    

if __name__ == "__main__":

    token = getters.GetToken()
    url   = getters.GetUrl(URL.AXINI)
    name  = "mado scientisto"

    adapter = Adapter()
    adapter.run(name, url, token)

    rel.signal(2, rel.abort)
    rel.dispatch()
