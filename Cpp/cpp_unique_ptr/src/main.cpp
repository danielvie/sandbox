#include <iostream>
#include <memory>
#include <thread>

class MyObject {
public:
    explicit MyObject(const std::string& name) : name_(name) {}
    
    const std::string& getName() const { return name_; }
    
private:
    std::string name_;
};

void process1(std::shared_ptr<MyObject> ptr) {
    std::cout << "My name is " << ptr->getName() << std::endl;
}

void process2(std::shared_ptr<MyObject> ptr) {
    std::this_thread::sleep_for(std::chrono::milliseconds(500));  // Wait for a while
    std::cout << "My name is not " << ptr->getName() << std::endl;
}

void process3(std::shared_ptr<MyObject> ptr) {
    std::cout << "Process3 has started.\n";
    std::this_thread::sleep_for(std::chrono::seconds(3));  // Wait for a while
    std::cout << "In process3, my name is " << ptr->getName() << std::endl;
}

int main() {
    std::shared_ptr<MyObject> ptr = std::make_shared<MyObject>("Bob");
    process1(ptr);

    std::thread t(process3, ptr);  // start process3 in a new thread

    process2(ptr);

    t.join();  // wait for process3 to finish

    return 0;
}