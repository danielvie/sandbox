#if !defined(__ARRAY__)
#define __ARRAY__

#include <iostream>
#include <stdexcept>
#include <algorithm>

template <typename T>
class Array
{
public:
    Array(size_t amount = 0, T value = T());
    Array(const Array &);
    ~Array();
    Array &operator=(const Array &);
    T &operator[](size_t index);
    T operator[](size_t index) const;
    size_t size() const { return length; }
    size_t capacity() const { return reserved; }

private:
    void set(const Array &);
    T *data;
    size_t length;
    size_t reserved;
};

template <typename T>
Array<T>::Array(size_t amount, T value)
{
    length = amount;
    reserved = amount;
    data = new T[reserved];
    std::fill(data, data + length, value);
}

template <typename T>
Array<T>::Array(const Array<T> &a)
{
    set(a);
}

template <typename T>
Array<T>::~Array()
{
    delete[] data;
}

template <typename T>
Array<T> &Array<T>::operator=(const Array<T> &a)
{
    if (this != &a)
    {
        delete[] data;
        set(a);
    }
    return *this;
}

template <typename T>
void Array<T>::set(const Array<T> &a)
{
    length = a.length;
    reserved = a.reserved;
    data = new T[length];
    std::copy(a.data, a.data + length, data);
}

template <typename T>
T Array<T>::operator[](size_t index) const
{
    if (index < 0 || index >= length)
    {
        throw std::range_error("invalid index");
    }
    return data[index];
}

template <typename T>
T &Array<T>::operator[](size_t index)
{
    if (index < 0 || index >= length)
    {
        throw std::range_error("invalid index");
    }
    return data[index];
}

#endif // __ARRAY__