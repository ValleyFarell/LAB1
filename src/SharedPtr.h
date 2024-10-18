#ifndef SHARED_PTR_H
#define SHARED_PTR_H

template<typename T>
class SharedPtr {
private:
    using valueCounterT = unsigned long long;
    class Counter {
        private:
            valueCounterT counter;
        public:
            Counter (valueCounterT value);
            Counter ();
            Counter operator ++(int);
            Counter operator --(int);
            valueCounterT GetValue () const;
            operator bool() const;
    };
    
    T * data;
    Counter * prtCounter;
    
    void Reset();
public:
    SharedPtr(T value);
    SharedPtr(T* value);
    SharedPtr();
    SharedPtr(const SharedPtr<T> & other);
    SharedPtr(SharedPtr<T> && other);
    SharedPtr operator = (const SharedPtr<T> & other);
    SharedPtr operator = (SharedPtr<T> && other);
    void ChangeValue(T newValue);
    valueCounterT getCounterValue() const;
    T getValue() const;
    T* getPtr() const;
    ~SharedPtr();
};

#include"SharedPtr.cpp"

#endif