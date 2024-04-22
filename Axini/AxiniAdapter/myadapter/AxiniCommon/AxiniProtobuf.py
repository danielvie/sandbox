from Logger import Logger
from configuration_pb2 import Configuration
import announcement_pb2
import message_pb2

logger = Logger('AxiniProtobuf')

class AxiniProtobuf():

    @staticmethod
    def createMsgAnnouncement(name, supportedLabels, configuration:Configuration):
        logger.info('createMsgAnnouncement')
        announcement = announcement_pb2.Announcement(name = name)
        message      = message_pb2.Message(announcement = announcement)
        return message
        
    @staticmethod
    def timestamp():
        logger.info('entrei em `timestamp')