from Logger import Logger
import websocket
import getters
import rel
import time

class BrokerConnection():
    def __init__(self, url:str, token:str, enableTrace = False) -> None:
        self.logger = Logger('BrokerConnection')
        self.adapterCore = None
        self.connection = None
        self.serverUri = url
        self.token = token
        self.enableTrace = enableTrace

        self.logger.info('entrei em `BrokerConnection`')
        
    def close(self, code:int, message:str):
        self.logger.info('entrei em `close`')
        self.connection.close()

    def send(self, bytes):
        self.logger.info('entrei em `send`')
        self.connection.send(bytes, websocket.ABNF.OPCODE_BINARY)

    def on_open(self, ws):
        self.logger.info(f'Connected to AMP: {self.serverUri}') 
        self.adapterCore.onOpen()
        
    def on_error(self, ws, error):
        # TODO: implement on_error
        self.logger.error(error) 
        
    def on_message(self, bytes):
        self.adapterCore.handleMessage(bytes)
        
    def on_close(self, code:int, reason:str, remote:bool):
        self.logger.info(f'Disconnected from AMP: {self.serverUri}; code: {code} {reason}') 
        self.adapterCore.onClose(code, reason, remote)

    def connect(self):
        websocket.enableTrace(self.enableTrace)
        # use a separate connection for each test run
        self.logger.info('entrei em `connect`')

        headers = getters.GetHeaders()

        connection = websocket.WebSocketApp(self.serverUri)
        connection.header = headers
        connection.on_open = self.on_open
        connection.on_error = self.on_error
        connection.on_message = self.on_message
        connection.on_close = self.on_close
        
        self.connection = connection
        self.connection.run_forever(dispatcher=rel)
        # self.connection.run_forever()

    def registerAdapterCore(self, adapterCore):
        self.logger.info('entrei em `registerAdapterCore`')
        self.adapterCore = adapterCore
    