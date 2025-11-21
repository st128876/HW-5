#include <iostream>
#include <cstring>
#include <stdexcept>

class String;

class SubstringProxy {
    String const& parent;
    size_t begin;

public:
    SubstringProxy(String const& p, size_t b)
        : parent(p), begin(b) {}

    String operator[](size_t end) const; 
};

class String {
    char* data_;
    size_t size_;

public:
    String() : data_(nullptr), size_(0) {}

    String(char const* s) {
        size_ = std::strlen(s);
        data_ = new char[size_ + 1];
        std::memcpy(data_, s, size_ + 1);
    }

    String(char const* s, size_t len) {
        size_ = len;
        data_ = new char[len + 1];
        std::memcpy(data_, s, len);
        data_[len] = '\0';
    }

    String(String const& other) {
        size_ = other.size_;
        data_ = new char[size_ + 1];
        std::memcpy(data_, other.data_, size_ + 1);
    }

    String& operator=(String const& other) {
        if (this != &other) {
            delete[] data_;
            size_ = other.size_;
            data_ = new char[size_ + 1];
            std::memcpy(data_, other.data_, size_ + 1);
        }
        return *this;
    }

    ~String() {
        delete[] data_;
    }

    char const* data() const { return data_; }
    size_t size() const { return size_; }

    SubstringProxy operator[](size_t i) const {
        return SubstringProxy(*this, i);
    }

    friend std::ostream& operator<<(std::ostream& os, String const& s) {
        if (s.data_) os << s.data_;
        return os;
    }
};


String SubstringProxy::operator[](size_t end) const {
    if (end < begin || end > parent.size()) {
        throw std::out_of_range("invalid substring indices");
    }
    size_t len = end - begin;
    return String(parent.data() + begin, len);
}




int main() {
    String const hello("hello");

    String hell = hello[0][4]; 
    String ell  = hello[1][4]; 
    String empty = hello[2][2];

    std::cout << "hello[0][4] = " << hell  << std::endl;
    std::cout << "hello[1][4] = " << ell   << std::endl;
    std::cout << "hello[2][2] = '" << empty << std::endl;

    return 0;
}

