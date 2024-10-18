#ifndef UNIQUE_PTR_SRC
#define UNIQUE_PTR_SRC

#include"UniquePtr.h"

template<typename T>
void UniquePtr<T>::Reset() {
    data = nullptr;
}

template<typename T>
UniquePtr<T>::UniquePtr(T value) : data(new T(value)) {}

template<typename T>
UniquePtr<T>::UniquePtr(T* value) : data(value) {}

template<typename T>
UniquePtr<T>::UniquePtr() : data(nullptr) {}

template<typename T>
UniquePtr<T>::UniquePtr(UniquePtr<T> && other) {
    data = other.data;
    other.Reset();
}

template<typename T>
UniquePtr<T>::UniquePtr(UniquePtr<T> & other) = delete;

template<typename T>
UniquePtr<T> UniquePtr<T>::operator = (UniquePtr<T> & other) = delete;

template<typename T>
UniquePtr<T>* UniquePtr<T>::operator = (UniquePtr<T> && other) {
    data = other.data;
    other.Reset();
    return this;
} 

template<typename T>
void UniquePtr<T>::ChangeValue(T newValue) {
    *(data) = newValue;
}

template<typename T>
T UniquePtr<T>::getValue() const {
    return *(data);
}

template<typename T>
T* UniquePtr<T>::getPtr() const {
    return data;
}

template<typename T>
UniquePtr<T>::~UniquePtr() {
    data = nullptr;
}

#endif