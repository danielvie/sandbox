
# Pre-requisites

#### (optional) create a virtual environment
```bash
# creating a virtual environment
>> virtualenv venv

# activating the virtual environment
>> .\venv\Scripts\activate
```

#### install python requirements:
```bash
# install 
pip install -r requirements.txt
```

#### build protobuf files

```bash
make build-proto
```

# Makefile commands

    default : (help)

    make help.................: help instruction
    make python-lab1..........: python script lab1
    make python-lab2..........: python script lab2
    make python-lab3..........: python script lab3
    make python-lab3-wsclient.: python script lab3 using websocket-client
    make build-proto..........: build protobuf axini example
    make clean................: clean protobuf files

# Description of files

#### python-lab1.py

connects with the java `SmartDoorSut.java` example provided for the training 

```bash
make python-lab1
```

#### python-lab2.py

connects with the axini and announces the name of the adapter

```bash
make python-lab2
```

#### python-lab3.py

tryied to implement the `BrokerConnection` and the `Handler`
maybe the `websockets` library is not a perfect match to implement the same design.
decided to try another library to first create a design that is closer to the axini implementation

```bash
make python-lab3
```

#### python-lab3-wsclient.py

decided to try `websocket-client` that has the event listeners `on_open` `on_message`, ...

```bash
make python-lab3-wsclient
```

