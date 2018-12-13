#pragma once

template<class T>
class Vector {
    size_t _capacity, _size;
    T* _data;
public:
    Vector() : _data(new T[_capacity]),
        _capacity(4),
        _size(0) {
        //fungerar denna initiering?? (den är inte lämplig men fungerar den?)
    }
    ~Vector() {
        delete[] _data;
    }
    T& operator[](size_t i) {
        return _data[i];
    }
};

template<class T>
class Vector<T*> {
    size_t _capacity, _size;
    T** _data;
public:
    Vector() : _capacity(4), _size(0), _data(new T*[_capacity]) {
        //nullpointers?
    }
    ~Vector() {
        for (size_t i = 0; i < _capacity; ++i)
            delete _data[i];
        delete[] _data;
    }
    T*& operator[](size_t i) {
        return _data[i];
    }

};


class Proxy {
    friend class Vector<bool>;
    char* _ptr;
    char _bit;
    Proxy(char* begin, size_t i) {
        _ptr = begin + i / 8;
        _bit = i % 8;
    }
public:
    Proxy& operator=(bool rhs) {
        int byte = *_ptr;
        byte = (byte >> (_bit + 1)) * 2 + rhs;
        int rest = *_ptr << (8 - _bit);
        byte = (byte * 256 + rest) >> (8 - _bit);
        *_ptr = byte;
        return *this;
    }
    operator bool() {
        return (*_ptr >> _bit) & 1;
    }
};
template<>
class Vector<bool> {
    size_t _capacity, _size;
    char* _data;
public:
    using value_type = bool;
    using reference = Proxy;
    //using pointer = Proxy2;
    Vector() : _capacity(4), _size(0), _data(new char[(_capacity - 1) / 8 + 1]()) {
        //nullpointers?
    }
    ~Vector() {
        delete[] _data;
    }
    Proxy operator[](size_t i) {
        return Proxy(_data, i);
    }

};

void VectorTest();
