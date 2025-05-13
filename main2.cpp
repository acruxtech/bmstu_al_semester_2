#include <iostream>
#include <utility>


template<class T>
class MyShared {
    T* p = nullptr;
    size_t* count = nullptr;
    
    void release() {
        if (count && --(*count) == 0) {
            delete p;
            delete count;
        }
        p = nullptr;
        count = nullptr;
    }
        
    public:
        explicit MyShared(T* ptr = nullptr) : p(ptr), count(ptr ? new size_t(1) : nullptr) {}
        
        ~MyShared() {
            release();
        }
        
        MyShared(const MyShared& other) : p(other.p), count(other.count) {
            if (count) {
                ++(*count);
            }
        }
        
        MyShared& operator=(const MyShared& other) {
            if (this != &other) {
                release();
                p = other.p;
                count = other.count;
                if (count) {
                    ++(*count);
                }
            }
            return *this;
        }
        
        MyShared(MyShared&& other) noexcept : p(other.p), count(other.count) {
            other.p = nullptr;
            other.count = nullptr;
        }
        
        MyShared& operator=(MyShared&& other) noexcept {
            if (this != &other) {
                release();
                p = other.p;
                count = other.count;
                other.p = nullptr;
                other.count = nullptr;
            }
            return *this;
        }
        
        T* get() const {
            return p;
        }
        
        size_t use_count() const {
            return count ? *count : 0;
        }
        
        T& operator*() {
            return *p;
        }
        
        T* operator->() {
            return p;
        }
};


template<typename T, typename... Args>
MyShared<T> Make_MyShared(Args&&... args) {
    return MyShared<T>(new T(std::forward<Args>(args)...));
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
    auto p1 = Make_MyShared<MyPoint>(3.0, 4.0);
    p1->print();
    std::cout << "Use count: " << p1.use_count() << "\n";
    
    auto p2 = p1;
    p2->print();
    std::cout << "Use count p1: " << p1.use_count() << "\n";
    std::cout << "Use count p2: " << p2.use_count() << "\n";
    
    auto p3 = std::move(p2);
    std::cout << "After move:\n";
    std::cout << "Use count p1: " << p1.use_count() << "\n";
    std::cout << "p2 is " << (p2.get() ? "not empty" : "empty") << "\n";
    std::cout << "Use count p3: " << p3.use_count() << "\n";
    
    return 0;
}