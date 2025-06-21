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


template<class T, class... Args>
MyUnique<T> Make_MyUnique(Args... args) {
    return MyUnique<T>(new T(args...));
}
