#ifndef SHARED_PTR_SRC
#define SHARED_PTR_SRC
#include"SharedPtr.h"

using valueCounterT = unsigned long long;

template<typename T>
void SharedPtr<T>::Reset() {
        data = nullptr;
        prtCounter = nullptr;
}

template<typename T>
SharedPtr<T>::SharedPtr(T value) : data(new T(value)), prtCounter(new Counter(1)) {}

template<typename T>
SharedPtr<T>::SharedPtr(T* value) : data(value), prtCounter(new Counter(1)) {}

template<typename T>
SharedPtr<T>::SharedPtr() : data(nullptr), prtCounter(new Counter()) {}

template<typename T>
SharedPtr<T>::SharedPtr(const SharedPtr<T> & other) {
    data = other.data;
    prtCounter = other.prtCounter;
    if (data)
        (*prtCounter)++;
}

template<typename T>
SharedPtr<T>::SharedPtr(SharedPtr<T> && other) {
    data = other.data;
    prtCounter = other.prtCounter;
    other.Reset();
}

template<typename T>
SharedPtr<T> SharedPtr<T>::operator = (const SharedPtr<T> & other) {
    data = other->data;
    prtCounter = other->prtCounter;
    if (data)
        prtCounter++;
    return *this;
} 

template<typename T>
SharedPtr<T> SharedPtr<T>::operator = (SharedPtr<T> && other) {
    data = other.data;
    prtCounter = other.prtCounter;
    other.Reset();
    return *this;
} 

template<typename T>
void SharedPtr<T>::ChangeValue(T newValue) {
    *data = newValue;
}

template<typename T>
valueCounterT SharedPtr<T>::getCounterValue() const {
    return prtCounter->GetValue();
} 

template<typename T>
T SharedPtr<T>::getValue() const {
    return *data;
}

template<typename T>
T* SharedPtr<T>::getPtr() const {
    return data;
}

template<typename T>
SharedPtr<T>::~SharedPtr() {
    if (!(*prtCounter)) {
        delete data;
        delete prtCounter;
    }else {
        (*prtCounter)--;
        data = nullptr;
        prtCounter = nullptr;
    }
}

template<typename T>

SharedPtr<T>::Counter::Counter (valueCounterT value) : counter(value) {}

template<typename T>
SharedPtr<T>::Counter::Counter () : counter(0) {}

template<typename T>
typename SharedPtr<T>::Counter SharedPtr<T>::Counter::operator ++(int) {
    counter += 1;
    return *this;
}

template<typename T>
typename SharedPtr<T>::Counter SharedPtr<T>::Counter::operator --(int) {
    counter -= 1;
    return *this;
}

template<typename T>
valueCounterT SharedPtr<T>::Counter::GetValue () const {
    return counter;
}

template<typename T>
SharedPtr<T>::Counter::operator bool() const {
    return counter != 0;
}

#endif