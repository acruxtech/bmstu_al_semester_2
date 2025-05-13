#include <iostream>
#include <utility>


template<class T>
class MyUnique {
    T* p = nullptr;

    public:
        explicit MyUnique(T* ptr) : p(ptr) {}
        
        ~MyUnique() {
            delete p;
        }
        
        MyUnique(const MyUnique&) = delete;

        MyUnique& operator=(const MyUnique&) = delete;
        
        MyUnique(MyUnique&& other) noexcept : p(other.p) {
            other.p = nullptr;
        }
        
        MyUnique& operator=(MyUnique&& other) noexcept {
            if (this != &other) {
                delete p;
                p = other.p;
                other.p = nullptr;
            }
            return *this;
        }
        
        T* get() const {
            return p;
        }
        
        T& operator*() {
            return *p;
        }
        
        T* operator->() {
            return p;
        }
};


template<typename T, typename... Args>
MyUnique<T> Make_MyUnique(Args&&... args) {
    return MyUnique<T>(new T(std::forward<Args>(args)...));
}


class MyPoint {
    double x, y;

    public:
        MyPoint(double x, double y) : x(x), y(y) {}

        void print() const {
            std::cout << "Point(" << x << ", " << y << ")\n";
        }
};


int main() {
    auto p1 = Make_MyUnique<MyPoint>(1.5, 2.5);
    p1->print();
    
    auto p2 = std::move(p1);
    if (!p1.get()) {
        std::cout << "p1 is now empty (moved)\n";
    }
    p2->print();
        
    return 0;
}
