#include <iostream>
#include <fstream>
#include <cstring>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>

using namespace std;

// Define the size of the shared memory block
const int SHARED_MEMORY_SIZE = 1024;

// Define the structure of the data to be shared
struct Message {
    char message[30];
};

// Create a function to read a message from the shared memory
Message read_message_from_shared_memory(char* shared_memory) {
    Message message;
    memcpy(message.message, shared_memory, 30);
    return message;
}

int main() {
    // Open the shared memory object
    int fd = shm_open("/my_shared_memory", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        perror("shm_open failed");
        exit(1);
    }

    // Set the size of the shared memory object
    if (ftruncate(fd, SHARED_MEMORY_SIZE) == -1) {
        perror("ftruncate failed");
        exit(1);
    }

    // Map the shared memory object into the address space of this process
    char* shared_memory = (char*) mmap(NULL, SHARED_MEMORY_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (shared_memory == MAP_FAILED) {
        perror("mmap failed");
        exit(1);
    }

    // Close the shared memory object file descriptor (we don't need it anymore)
    close(fd);
    
    printf("entrei aqui\n");

    // Read a message from the shared memory
    Message message_read = read_message_from_shared_memory(shared_memory);
    cout << message_read.message << endl;

    // Unmap the shared memory from the address space of this process
    munmap(shared_memory, SHARED_MEMORY_SIZE);

    // Remove the shared memory object
    shm_unlink("/my_shared_memory");
}
