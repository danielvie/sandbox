from abc import ABC, abstractmethod
from AdapterCore import AdapterCore
from configuration_pb2 import Configuration
# from typing import Optional

class Handler(ABC):
    
    def __init__(self) -> None:
        # logger
        self.adapterCore:AdapterCore = None
        self.configuration:Configuration = self.defaultConfiguration()

    def sendReadyToAmp(self):
        self.adapterCore.sendReady()

    def registerAdapterCore(self, adapterCore:AdapterCore):
        self.adapterCore = adapterCore

    def getConfiguration(self):
        return self.configuration 

    @abstractmethod
    def defaultConfiguration(self):
        ''' prepare to start testing '''

    @abstractmethod
    def start(self):
        ''' prepare to start testing '''

    @abstractmethod
    def stop(self):
        ''' stop testing '''

    @abstractmethod
    def reset(self):
        ''' prepare for the next test case '''

    @abstractmethod
    def stimulate(self):
        ''' stimulate the system under test and return the physical label '''

    @abstractmethod
    def getSupportedLabels(self):
        ''' the labels supported by the plugin adapter '''