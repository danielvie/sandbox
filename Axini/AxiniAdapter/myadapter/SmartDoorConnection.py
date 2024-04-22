from Logger import Logger

class SmartDoorConnection():
    
    def __init__(self) -> None:
        self.logger:Logger = Logger()
        self.logger.info('SmartDoorConnection', 'entrei aqui')