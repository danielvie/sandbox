from abc import ABC, abstractmethod
from configuration_pb2 import Configuration

class Handler(ABC):
    
    # constructor
    def __init__(self) -> None:
        # self.logger = None
        self.adapterCore = None
        self.configuration:Configuration = self.defaultConfiguration()

    def sendReadyToAmp(self):
        self.adapterCore.sendReady()
        
    def registerAdapterCore(self, adapterCore):
        self.adapterCore = adapterCore
        
    def setConfiguration(self, configuration:Configuration):
        self.configuration = configuration
        
    def getConfiguration(self):
        return self.configuration

    @abstractmethod
    def defaultConfiguration() -> Configuration:
        ''' the default configuration for this plugin adapter '''
        
    @abstractmethod
    def start() -> None:
        ''' prepare to start testing '''
        
    @abstractmethod
    def stop() -> None:
        ''' stop testing '''
        
    @abstractmethod
    def reset() -> None:
        ''' prepare for the next test case '''
        
    @abstractmethod
    def stimulate():
        ''' stimulate the system under test and return the physical label '''
        
    @abstractmethod
    def getSupportedLabels():
        ''' the labels supported by the plugin adapter '''
        
    
