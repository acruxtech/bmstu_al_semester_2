#include "../source/Unique.cpp"
#include "../source/Shared.cpp"
#include "../source/TestObject.cpp"
#include <iostream>


int main() {
    std::cout << "=== Unique ===" << "\n";

    std::cout << "basic usage" << "\n";
    {
        auto ptr = Make_MyUnique<TestObject>(42);
        ptr->print();
        (*ptr).print();
    }

    std::cout << "move" << "\n";
    {
        auto ptr1 = Make_MyUnique<TestObject>(100);
        auto ptr2 = std::move(ptr1);

        if (!ptr1.get()) {
            std::cout << "ptr1 empty\n";
        }

        ptr2->print();
    }

    std::cout << "get method" << "\n";
    {
        auto ptr = Make_MyUnique<TestObject>(300);
        TestObject* raw = ptr.get();
        raw->print();
    }

    std::cout << "\n=== Shared ===" << "\n";


    std::cout << "basic usage" << "\n";
    {
        auto ptr1 = Make_MyShared<TestObject>(10);
        ptr1->print();
        std::cout << "Use count: " << ptr1.use_count() << "\n"; // 1

        {
            auto ptr2 = ptr1;
            ptr2->print();
            std::cout << "Use count: " << ptr1.use_count() << "\n"; // 2
        }

        std::cout << "Use count: " << ptr1.use_count() << "\n"; // 1
    }

    std::cout << "\n=== Move semantics ===" << "\n";
    {
        auto ptr1 = Make_MyShared<TestObject>(20);
        auto ptr2 = std::move(ptr1);

        if (!ptr1.get()) {
            std::cout << "ptr1 empty\n";
        }

        ptr2->print();
        std::cout << "Use count: " << ptr2.use_count() << "\n"; // 1
    }

    std::cout << "\nassignment" << "\n";
    {
        MyShared<TestObject> ptr3;
        {
            auto temp = Make_MyShared<TestObject>(30);
            ptr3 = temp; 
            std::cout << "Use count: " << temp.use_count() << "\n"; // 2
        }

        ptr3->print();
    }

    return 0;
}
