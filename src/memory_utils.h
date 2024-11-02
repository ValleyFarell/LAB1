#ifndef MEMORY_UTILS_H
#define MEMORY_UTILS_H

template<typename T>
class SharedPtr {
private:
    class Counter {
        private:
            unsigned long long counter_ = 0;
        public:
            Counter (unsigned long long value) : counter_(value) {}
            void operator ++(int) { counter_++; }
            void operator --(int) { counter_--; }
            unsigned long long count () const { return counter_; }
            operator bool() const {
                return counter_ != 0;
            }
    };
    T * data_ = nullptr;
    Counter * ptr_counter_ = nullptr;
    void reset() {
        data_ = nullptr;
        ptr_counter_ = nullptr;
    }
public:
    SharedPtr(T* ptr) {
        data_ = ptr;
        ptr_counter_ = new Counter(1);
    }
    SharedPtr() {
        data_ = nullptr;
        ptr_counter_ = nullptr;
    }
    SharedPtr(const SharedPtr<T> & other) {
        data_ = other.data_;
        if (ptr_counter_ && *ptr_counter_) (*ptr_counter_)--;
        ptr_counter_ = other.ptr_counter_;
        if (*ptr_counter_)
            (*ptr_counter_)++;
    }
    SharedPtr(SharedPtr<T> && other) {
        data_ = other.data_;
        if (ptr_counter_ && *ptr_counter_) (*ptr_counter_)--;
        ptr_counter_ = other.ptr_counter_;
        other.reset();
    }
    SharedPtr& operator = (const SharedPtr<T> & other) {
        data_ = other.data_;
        if (ptr_counter_ && *ptr_counter_) (*ptr_counter_)--;
        ptr_counter_ = other.ptr_counter_;
        if (*ptr_counter_)
            (*ptr_counter_)++;
        return *this;
    }
    SharedPtr& operator = (SharedPtr<T> && other) {
        data_ = other.data_;
        if (ptr_counter_ && *ptr_counter_) (*ptr_counter_)--;
        ptr_counter_ = other.ptr_counter_;
        other.reset();
        return *this;
    }
    unsigned long long ref_count() const { return ptr_counter_->count(); }
    T& operator*() const {
        return *data_;
    }
    void swap(SharedPtr<T>&& other) {
        T* tmp_data = other.data_;
        Counter* tmp_counter = other.ptr_counter_;
        other.data_ = data_;
        other.ptr_counter_ = ptr_counter_;
        data_ = tmp_data;
        ptr_counter_ = tmp_counter;
    }
    T* get_pointer() const {
        return data_;
    }
    ~SharedPtr() {
        if (ptr_counter_ && (*ptr_counter_)) {
            (*ptr_counter_) --;
            if (!(*ptr_counter_)) {
                delete ptr_counter_;
                delete data_;
            }
        }
    }
};

template<typename T>
class UniquePtr {
private:
    T* data_;
    void reset() {
        data_ = nullptr;
    }
public:
    UniquePtr(T* ptr) {
        data_ = ptr;
    }
    UniquePtr() {
        data_ = nullptr;
    }
    UniquePtr(UniquePtr<T> && other) {
        data_ = other.data_;
        other.reset();
    }
    UniquePtr& operator = (UniquePtr<T> && other) {
        data_ = other.data_;
        other.reset();
        return *this;
    }
    T& operator*() const {
        return *data_;
    }
    T* get_pointer() const {
        return data_;
    }
    ~UniquePtr() {
        delete data_;
    }
};
#endif