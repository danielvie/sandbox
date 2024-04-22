from AxiniCommon.Handler import Handler
from configuration_pb2 import Configuration
from Logger import Logger
from SmartDoorConnection import SmartDoorConnection

class SmartDoorHandler(Handler):
    
    def __init__(self) -> None:
        self.logger = Logger('SmartDoorHandler')
        self.RESET = "RESET"
        self.RESET_PERFORMED = "RESET_PERFORMED"

        self.SMARTDOOR_URL = "ws://localhost:3001"
        self.SMARTDOOR_MANUFACTORY = "Axini"

        # websocket connection to the SUT
        self.connection:SmartDoorConnection = None
        
        self.adapterCore = None
        self.configuration:Configuration = self.defaultConfiguration()

        self.logger.info('entrei em smartdoorhandler')
        
    def defaultConfiguration(self) -> Configuration:
        ''' the default configuration for this plugin adapter '''        
        self.logger.info('entrei em `defaultConfiguration`')
        return []
        
    def start(self) -> None:
        ''' prepare to start testing '''
        self.logger.info('entrei em `start`')
        
    def stop(self) -> None:
        ''' stop testing '''
        self.logger.info('entrei em `stop`')
        
    def reset(self) -> None:
        ''' prepare for the next test case '''
        self.logger.info('entrei em `reset`')
        
    def stimulate(self):
        ''' stimulate the system under test and return the physical label '''
        self.logger.info('entrei em `stimulate`')
        
    def getSupportedLabels(self):
        ''' the labels supported by the plugin adapter '''
        self.logger.info('entrei em `getSupportedLabels`')
        return None
        
    
