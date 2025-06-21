#include <iostream>


class TestObject {
public:
    int value;

    TestObject(int val) : value(val) {
        std::cout << "TestObject constructed: " << value << "\n";
    }

    ~TestObject() {
        std::cout << "TestObject destroyed: " << value << "\n";
    }

    void print() const {
        std::cout << "TestObject value: " << value << "\n";
    }
};