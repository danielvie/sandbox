from Logger import Logger
from enum import Enum, auto
from AxiniCommon.BrokerConnection import BrokerConnection
from AxiniCommon.Handler import Handler
from AxiniCommon.AxiniProtobuf import AxiniProtobuf
from configuration_pb2 import Configuration
from label_pb2 import Label
from message_pb2 import Message

class State(Enum):
    CONNECTED = auto()
    DISCONNECTED = auto()
    ANNOUNCED = auto()
    CONFIGURED = auto()
    READY = auto()
    ERROR = auto()

class AdapterCore():
    def __init__(self, name:str, brokerConnection:BrokerConnection, handler:Handler):
        self.logger = Logger('AdapterCore')
        self.name = name
        self.brokerConnection = brokerConnection
        self.handler = handler
        self.state = State.DISCONNECTED

        self.logger.info('entrei')
        
    # Start the AdapterCore.
    # * let the BrokerConnection connect to AMP.
    def start(self):
        if (self.state == State.DISCONNECTED):
            self.logger.info("Connecting to AMP's broker")
            self.brokerConnection.connect()
        else:
            message = "Adapter started while already connected"
            self.logger.info(message)
            self.sendError(message)

    # BrokerConnection: connection is opened.
    # * send announcement to AMP.
    def onOpen(self):
        if (self.state == State.DISCONNECTED):
            self.state = State.CONNECTED
            self.logger.info('Announcing.')
            
            supportedLabels = self.handler.getSupportedLabels()
            configuration = self.handler.getConfiguration()

            self.sendAnnouncement(self.name, supportedLabels, configuration)
            self.state = State.ANNOUNCED
        else:
            message = "Connection openend while already connected"
            self.logger.info(message)
            self.sendError(message)
            
    # BrokerConnection: connection is closed.
    # * stop the handler
    def onClose(self, code:int, reason:str, remote:bool):
        self.state = State.DISCONNECTED
        
        message = f'Connection closed with code {code} and reason {reason}.'
        if (code == 1006):
            message = f'{message} The server may not be reachable.'
            self.logger.info(message)
            
        self.handler.stop()
        self.start() # reconnect to AMP - keep the adapter alive

    # Configuration received from AMP.
    # * configure the handler,
    # * start the handler,
    # * send ready to AMP (should be done by handler).
    def onConfiguration(self, configuration:Configuration):
        if (self.state == State.ANNOUNCED):
            self.handler.setConfiguration(configuration)
            self.state = State.CONFIGURED
            
            self.logger.info('Connecting to the SUT')
            self.handler.start()

            # The handler should call sendReady() as it knows when it is ready.
        
        elif (self.state == State.CONNECTED):
            message = "Configuration received from AMP while not yet announced.";
            self.logger.info(message);
            self.sendError(message);

        else:
            message = "Configuration received from AMP while already configured.";
            self.logger.info(message);
            self.sendError(message);

    # Label (stimulus) received from AMP.
    # * make handler offer the stimulus to the SUT,
    # * acknowledge the actual stimulus to AMP.
    def onLabel(self, label:Label, correlationId:float):
        if (self.state == State.READY):
            # We do not check that the label is a stimulus
            physicalLabel = self.handler.stimulate(label)
            timestamp = AxiniProtobuf.timestamp()
            self.sendStimulus(label, physicalLabel, timestamp, correlationId)

        else:
            message = "Label received from AMP while not ready."
            self.logger.info(message)
            self.sendError(message)

    # Reset message received from AMP.
    # * reset the handler,
    # * send ready to AMP (should be done by handler).
    def onReset(self):
        if (self.state == State.READY):
            self.handler.reset()
            # The handler should call sendReady() as it knows when it is ready.

        else:
            message = "Reset received from AMP while not ready."
            self.logger.info(message)
            self.sendError(message)

    # Error message received from AMP.
    # * close the connection to AMP
    def onError(self, message:str):
        self.state = State.ERROR
        msg = "Error message received from AMP: " + message + "."
        self.logger.info(msg)

        self.brokerConnection.close(1000, message) # 1000 is normal closure...


    # Parse the ByteBuffer message from AMP to a Protobuf message and call
    # the appropriate method of this AdapterCore.
    def handleMessage(self, bytes):
        msg = None

        try:
            msg = Message.parseFrom(bytes.array())
        # except (InvalidProtocolBufferException ex):
        #     self.logger.error("InvalidProtocolBufferException: " + ex.getMessage())
        except:
            # TODO: implementar a excessao aqui direito
            self.logger.error('erro parse message')

        if (msg.hasConfiguration()):
            self.logger.info("Configuration received from AMP")
            configuration:Configuration = msg.getConfiguration()
            self.onConfiguration(configuration)

        elif (msg.hasLabel()):
            label = msg.getLabel()
            # two extra spaces to allign log with SmartDoorConnection
            self.logger.info("Label received from AMP: " + label.getLabel())
            correlation_id = label.getCorrelationId()
            self.onLabel(label, correlation_id)

        elif (msg.hasError()):
            error_msg = msg.getError().getMessage()
            self.logger.info("Error received from AMP: " + error_msg)
            self.onError(error_msg)

        elif (msg.hasReset()):
            self.logger.info("Reset received from AMP")
            self.onReset()

        elif (msg.hasAnnouncement()):
            self.logger.error("Message type 'Announcement' not supported")

        elif (msg.hasReady()):
            self.logger.error("Message type 'Ready' not supported")

        else:
            self.logger.error("Unknown message type")


    # Send response to AMP (callback for Handler).
    # We do not check whether the label is actual a response.
    # def sendResponse(self, label:Label, ByteString physicalLabel, long timestamp):
    def sendResponse(self, label:Label, physicalLabel, timestamp:float):
        self.logger.info("Sending response to AMP: " + label.getLabel())
        new_label:Label = AxiniProtobuf.createLabel(label, physicalLabel, timestamp)
        self.sendLabel(new_label)

    # Send ready message to AMP.
    def sendReady(self):
        self.logger.info("Sending Ready to AMP.")
        self.sendMessage(AxiniProtobuf.createMsgReady())
        self.state = State.READY


    # Error message received from AMP.
    # * close the connection to AMP
    def sendError(self, errorMessage:str):
        # TODO: implementar `sendError`
        self.logger.error('Sending Error to AMP and closing the connection')
        message:Message = AxiniProtobuf.createMsgError(errorMessage)
        self.sendMessage(message)
        self.brokerConnection.close(1000, errorMessage) # 1000 is normal closure
        
    # Send stimulus to AMP.
    # We do not check that the label is a stimulus.
    def sendStimulus(self, label:Label, physicalLabel, timestamp:float, correlationId:float):
        self.logger.info("Sending stimulus (back) to AMP: " + label.getLabel())
        new_label:Label = AxiniProtobuf.createLabel(label, physicalLabel, timestamp, correlationId)
        self.sendLabel(new_label)
        
    def sendLabel(self, label:Label):
        self.logger.info("Sending label to AMP: " + label.getLabel())
        message:Message = AxiniProtobuf.createMsgLabel(label)
        self.sendMessage(message)

    # Send announcement to AMP.
    def sendAnnouncement(self, name:str, supportedLabels:list[Label], configuration:Configuration):
        message:Message = AxiniProtobuf.createMsgAnnouncement(name, supportedLabels, configuration)
        self.sendMessage(message)

    # Send a Protobuf Message as a byte[] to AMP.
    def sendMessage(self, message:Message):
        bytes = message.SerializeToString()
        self.brokerConnection.send(bytes)