#include <cstddef>


template <typename T>
class MyShared {
    T* ptr = nullptr;
    size_t* ref_count = nullptr;

    void cleanup() {
        if (ref_count) {
            (*ref_count)--;
            if (*ref_count == 0) {
                delete ptr;
                delete ref_count;
            }
        }
    }

public:
    MyShared(T* p = nullptr) : ptr(p), ref_count(p ? new size_t(1) : nullptr) {}

    MyShared(const MyShared& other) : ptr(other.ptr), ref_count(other.ref_count) {
        if (ref_count) (*ref_count)++;
    }

    MyShared(MyShared&& other) noexcept : ptr(other.ptr), ref_count(other.ref_count) {
        other.ptr = nullptr;
        other.ref_count = nullptr;
    }

    ~MyShared() {
        cleanup();
    }

    MyShared& operator=(const MyShared& other) {
        if (this != &other) {
            cleanup();
            ptr = other.ptr;
            ref_count = other.ref_count;
            if (ref_count) (*ref_count)++;
        }
        return *this;
    }

    MyShared& operator=(MyShared&& other) noexcept {
        if (this != &other) {
            cleanup();
            ptr = other.ptr;
            ref_count = other.ref_count;
            other.ptr = nullptr;
            other.ref_count = nullptr;
        }
        return *this;
    }

    T* get() const { return ptr; }
    T& operator*() const { return *ptr; }
    T* operator->() const { return ptr; }

    size_t use_count() const { return ref_count ? *ref_count : 0; }
};


template <typename T, typename... Args>
MyShared<T> Make_MyShared(Args&&... args) {
    return MyShared<T>(new T(args...));
}
