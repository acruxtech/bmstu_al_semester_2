#include "../include/string.hpp"
#include <cstring>
#include <algorithm>


String::~String() {
    delete[] Data;
}


String::String() : Data(new char[1]) {
    Data[0] = '\0';
}


String::String(const String& rhs) : Data(new char[rhs.Size() + 1]) {
    std::copy(rhs.Data, rhs.Data + rhs.Size() + 1, Data);
}


String::String(const char* data) {
    if (data) {
        size_t length = strlen(data);
        Data = new char[length + 1];
        std::copy(data, data + length + 1, Data);
    } else {
        Data = new char[1];
        Data[0] = '\0';
    }
}


String& String::operator=(const String& rhs) {
    if (this != &rhs) {
        char* new_data = new char[rhs.Size() + 1];
        std::copy(rhs.Data, rhs.Data + rhs.Size() + 1, new_data);
        delete[] Data;
        Data = new_data;
    }
    return *this;
}


String& String::operator+=(const String& rhs) {
    size_t new_size = Size() + rhs.Size();
    char* new_data = new char[new_size + 1];
    std::copy(Data, Data + Size(), new_data);
    std::copy(rhs.Data, rhs.Data + rhs.Size() + 1, new_data + Size());
    delete[] Data;
    Data = new_data;
    return *this;
}


String& String::operator*=(unsigned int m) {
    if (m == 0) {
        delete[] Data;
        Data = new char[1];
        Data[0] = '\0';
        return *this;
    }
    
    size_t old_size = Size();
    size_t new_size = old_size * m;
    char* new_data = new char[new_size + 1];
    
    for (unsigned int i = 0; i < m; ++i) {
        std::copy(Data, Data + old_size, new_data + i * old_size);
    }
    new_data[new_size] = '\0';
    
    delete[] Data;
    Data = new_data;
    return *this;
}


bool String::operator==(const String& rhs) const {
    if (Size() != rhs.Size()) return false;
    return std::equal(Data, Data + Size(), rhs.Data);
}


bool String::operator<(const String& rhs) const {
    return std::lexicographical_compare(
        Data, 
        Data + Size(), 
        rhs.Data, 
        rhs.Data + rhs.Size()
    );
}


size_t String::Find(const String& substr) const {
    if (substr.Empty() || substr.Size() > Size()) return -1;
    
    for (size_t i = 0; i <= Size() - substr.Size(); ++i) {
        bool found = true;
        for (size_t j = 0; j < substr.Size(); ++j) {
            if (Data[i + j] != substr.Data[j]) {
                found = false;
                break;
            }
        }
        if (found) return i;
    }
    return -1;
}


void String::Replace(char oldSymbol, char newSymbol) {
    for (size_t i = 0; i < Size(); ++i) {
        if (Data[i] == oldSymbol) {
            Data[i] = newSymbol;
        }
    }
}


size_t String::Size() const {
    return strlen(Data);
}


bool String::Empty() const {
    return Size() == 0;
}


char String::operator[](size_t index) const {
    return Data[index];
}


char& String::operator[](size_t index) {
    return Data[index];
}


void String::RTrim(char symbol) {
    size_t new_size = Size();
    while (new_size > 0 && Data[new_size - 1] == symbol) {
        --new_size;
    }
    
    if (new_size != Size()) {
        char* new_data = new char[new_size + 1];
        std::copy(Data, Data + new_size, new_data);
        new_data[new_size] = '\0';
        delete[] Data;
        Data = new_data;
    }
}


void String::LTrim(char symbol) {
    size_t start = 0;
    while (start < Size() && Data[start] == symbol) {
        ++start;
    }
    
    if (start > 0) {
        size_t new_size = Size() - start;
        char* new_data = new char[new_size + 1];
        std::copy(Data + start, Data + Size(), new_data);
        new_data[new_size] = '\0';
        delete[] Data;
        Data = new_data;
    }
}


void String::swap(String& oth) {
    std::swap(Data, oth.Data);
}


String operator+(const String& a, const String& b) {
    String result(a);
    result += b;
    return result;
}


String operator*(const String& a, unsigned int b) {
    String result;
    for (unsigned int i = 0; i < b; ++i) {
        result += a;
    }
    return result;
}


bool operator!=(const String& a, const String& b) {
    return !(a == b);
}


bool operator>(const String& a, const String& b) {
    return a < b;
}


std::ostream& operator<<(std::ostream& out, const String& str) {
    out << str.Data;
    return out;
}
