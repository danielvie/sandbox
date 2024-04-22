import websocket
import asyncio
import threading
import time
import rel
import getters
from getters import URL
import message_pb2

class AxiniHandler():
    def __init__(self):
        self.ws = []

    def on_message(self, ws, msg):
        def run(*args):
            message = message_pb2.Message()
            message.ParseFromString(msg)
            print(message)

        threading.Thread(target=run).start()

    def on_error(self, ws, error):
        print(error)

    def on_close(self, ws, close_status_code, close_msg):
        print("### closed ###")

    def on_open(self, ws):
        print('opened connection axini')

        message = getters.GetAnnouncementMessage(name = 'MadoScientisto')
        ws.send(message, websocket.ABNF.OPCODE_BINARY)

    def start(self):
        # websocket.enableTrace(True)
        url = getters.GetUrl(URL.AXINI)
        headers = getters.GetHeaders()
        # url = "ws://localhost:3001"

        ws = websocket.WebSocketApp(url)
        ws.header = headers
        ws.on_open = self.on_open
        ws.on_error = self.on_error
        ws.on_message = self.on_message
        ws.on_close = self.on_close

        ws.run_forever(dispatcher=rel)
        self.ws = ws


class SutHandler():
    
    def __init__(self):
        self.ws = []

    def on_message(self, ws, msg):
        def run(*args):
            print(msg)

        threading.Thread(target=run).start()

    def on_error(self, ws, error):
        print(error)

    def on_close(self, ws, close_status_code, close_msg):
        print("### closed ###")

    def on_open(self, ws):
        print('opened connection axini')

        # ws.send("RESET", websocket.ABNF.OPCODE_TEXT)

    def start(self):
        # websocket.enableTrace(True)
        url = getters.GetUrl(URL.SMARTDOOR)
        # headers = getters.GetHeaders()
        # url = "ws://localhost:3001"

        ws = websocket.WebSocketApp(url)
        ws.on_open = self.on_open
        ws.on_error = self.on_error
        ws.on_message = self.on_message
        ws.on_close = self.on_close

        ws.run_forever(dispatcher=rel)

        self.ws = ws
        

class Adapter():

    def on_message(self, ws, msg):
        def run(*args):
            message = message_pb2.Message()
            message.ParseFromString(msg)

            # ws.send("RESET", websocket.ABNF.OPCODE_TEXT)
            self.sutHandler.ws.send("RESET", websocket.ABNF.OPCODE_TEXT)

            print(message)

        threading.Thread(target=run).start()

    def __init__(self, axiniHandler, sutHandler) -> None:
        self.axiniHandler = axiniHandler
        self.axiniHandler.on_message = self.on_message

        self.sutHandler = sutHandler
        
    def start(self):
        self.axiniHandler.start()
        self.sutHandler.start()

if __name__ == "__main__":
    
    # axiniHandler = AxiniHandler()
    # sutHandler = SutHandler()

    # adapter = Adapter(axiniHandler, sutHandler)
    # adapter.start()

    # rel.signal(2, rel.abort)
    # rel.dispatch()

    # print("after adapter start")

    from Handler import Handler
    
    handler = Handler()
    
    handler.start()
    
    
    
