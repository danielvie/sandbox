#include <iostream>
#include <concepts>

void print(std::integral auto value) {
    std::cout << "Printing integral value: " << value << "\n";
}



class Bla
{
private:
    /* data */
public:
    // Bla() {
    //     std::cout << "CONSTRUCTOR\n";
    // }
    // ~Bla() {
    //     std::cout << "DESTRUCTOR\n";
    // }
    void speak() {
        std::cout << "i am speaking\n";
    }
};





int main() {
    Bla b = Bla();
    print(10);
    return 0;
}
