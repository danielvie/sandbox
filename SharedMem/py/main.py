import multiprocessing.shared_memory
import struct

# Define the size of the shared memory block
SHARED_MEMORY_SIZE = 1024

# Define the name to use for the shared memory block
SHARED_MEMORY_NAME = "/my_shared_memory"

# Define the structure of the data to be shared
MESSAGE_FORMAT = "30s"
MESSAGE_SIZE = struct.calcsize(MESSAGE_FORMAT)

# Create a shared memory block
shared_memory = multiprocessing.shared_memory.SharedMemory(name=SHARED_MEMORY_NAME, create=True, size=SHARED_MEMORY_SIZE)

# Convert the shared memory block into a memory view object
memory_view = memoryview(shared_memory.buf)

# Create a function to write a message to the shared memory
def send_message_to_shared_memory(message):
    message_bytes = message.encode('utf-8')
    packed_message = struct.pack(MESSAGE_FORMAT, message_bytes)
    memory_view[:MESSAGE_SIZE] = packed_message

# Example usage:
if __name__ == '__main__':
    # Send a message to the shared memory
    message_to_send = "Hello from Python!"
    send_message_to_shared_memory(message_to_send)
