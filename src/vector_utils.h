#ifndef VECTOR_UTILS_H
#define VECTOR_UTILS_H

template<typename T>
class Vector {
private:
    T* data_ = nullptr;
    size_t size_ = 0;
    size_t capacity_ = 1;
public:
    Vector() : data_(nullptr), size_(0), capacity_(1) {}
    Vector(size_t size, const T& item){
        data_ = new T[size];
        size_ = size;
        capacity_ = size * 2;
        for (size_t i = 0; i != size; ++i) {
            data_[i] = item;
        }
    }
    Vector(const Vector<T>& other) {
        data_ = new T[other.capacity_];
        capacity_ = other.capacity_;
        size_ = other.size_;
        for (size_t i = 0; i != size_; ++i) {
            data_[i] = other.data_[i];
        }
    }
    Vector(Vector<T>&& other) {
        data_ = new T[other.capacity_];
        capacity_ = other.capacity_;
        size_ = other.size_;
        for (size_t i = 0; i != size_; ++i) {
            data_[i] = other.data_[i];
        }
    }
    template<typename InputIt>
    Vector(InputIt first, InputIt last);
    const T& operator [] (size_t index) const {
        return data_[index];
    }
    T& operator [] (size_t index) {
        return data_[index];
    }
    const T& at(size_t index) const {
        if (index >= size_) {
            return data_[index];
        }
        throw "Wrong index! Index must be in range from 0 to size of vector. ";
    }
    T& at(size_t index) {
        if (index >= size_) {
            return data_[index];
        }
        throw "Wrong index! Index must be in range from 0 to size of vector. ";
    }
    bool empty() const {
        return size_ == 0;
    }
    size_t size() const {
        return size_;
    }
    size_t capacity() const {
        return capacity_;
    }
    void reserve(size_t new_capacity) {
        T* temp = new T[size_];
        for (size_t i = 0; i != size_; ++i) {
            temp[i] = std::move(data_[i]);
        }
        data_ = new T[new_capacity];
        for (size_t i = 0; i != size_; ++i) {
            data_[i] = std::move(temp[i]);
        }
        delete[] temp;
    }
    void clear() {
        for (size_t i = 0; i != size_; ++i) {
            data_[i] = T();
        }
        size_ = 0;
    }
    void push_back(const T& value) {
        this->resize(size_ + 1);
        data_[size_ - 1] = value;
    }
    void push_back(T&& value) {
        this->resize(size_ + 1);
        data_[size_ - 1] = std::move(value);
    }
    void insert(const T& value, size_t index) {
        this->resize(size_ + 1);
        for (size_t i = size_ - 1; i > index; --i) {
            data_[i] = std::move(data_[i - 1]);
        }
        data_[index] = value;
    }
    void insert(T&& value, size_t index) {
        this->resize(size_ + 1);
        for (size_t i = size_ - 1; i > index; --i) {
            data_[i] = std::move(data_[i - 1]);
        }
        data_[index] = std::move(value);
    }
    void pop_back() {
        data_[size_ - 1] = T();
        this->resize(size_ - 1);
    }
    size_t erase(size_t index) {
        for (size_t i = index; i < size_ - 1; ++i) {
            data_[i] = std::move(data_[i + 1]);
        }
        this->pop_back();
        return index;
    }
    void resize(size_t new_size) {
        if (new_size >= capacity_) {
            this->reserve(capacity_ * 2);
            capacity_ *= 2;
            size_ = new_size;
        } else {
            size_ = new_size;
        }
    }
    void resize(size_t new_size, const T& value) {
        if (new_size >= capacity_) {
            this->reserve(capacity_ * 2);
            for (size_t i = size_; i != new_size; ++i) {
                data_[i] = value;
            }
            size_ = new_size;
        } else {
            size_ = new_size;
        }
    }
};

#endif