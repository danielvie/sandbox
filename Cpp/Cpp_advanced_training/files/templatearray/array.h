// file array.h

#ifndef ARRAY_H
#define ARRAY_H

#include <algorithm>
#include <iostream>
#include <stdexcept>

template<typename T>
class Array {
public:
    Array(int amount=0, T value=T());
    Array(const Array&);
    ~Array();
    Array& operator=(const Array&);
    T& operator[](int index);
    T operator[](int index) const;
private:
    void set(const Array&);
    T *data;
    int length;
};

template<typename T>
Array<T>::Array(int amount, T value) {
    length = amount;
    data = new int[amount];
    std::fill(data, data+length, value);
}

template<typename T>
Array<T>::Array(const Array& a) {
    set(a);
}

template<typename T>
Array<T>::~Array() {
    delete [] data;
}

template<typename T>
Array<T>& Array<T>::operator=(const Array& a) {
    if( this != &a ) {
        delete [] data;
        set(a);
    }
    return *this;
}

template<typename T>
void Array<T>::set(const Array& a) {
    length = a.length;
    data = new int[length];
    std::copy(a.data, a.data+length, data);
}

template<typename T>
T Array<T>::operator[](int index) const {
    if( index<0 || index>=length ) {
        throw std::range_error("invalid index");
    }
    return data[index];
}

template<typename T>
T& Array<T>::operator[](int index) {
    if( index<0 || index>=length ) {
        throw std::range_error("invalid index");
    }
    return data[index];
}
#endif
