#ifndef UNIQUE_PTR_H
#define UNIQUE_PTR_H

template<typename T>
class UniquePtr {
private:
    T* data;
    void Reset();
public:
    UniquePtr(T value);
    UniquePtr(T* value);
    UniquePtr();
    UniquePtr(UniquePtr<T> && other);
    UniquePtr(UniquePtr<T> & other);
    UniquePtr operator = (UniquePtr<T> & other);
    UniquePtr *operator = (UniquePtr<T> && other);
    void ChangeValue(T newValue);
    T getValue() const;
    T* getPtr() const;
    ~UniquePtr();
};

#include"UniquePtr.cpp"

#endif