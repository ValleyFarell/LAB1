#include<iostream>
#include<memory>
#include"../src/UniquePtr.h"

class Object : public std::enable_shared_from_this<Object> {
protected:
    Object() = default;
private:
    Object(const Object&) = delete;
    Object& operator = (const Object&) = delete;  
public:
    virtual ~Object() = default;
};

class Int : public Object {
private:
    int64_t data_;
    explicit Int(int64_t data) : data_(data) {}
public:
    static std::unique_ptr<Int> create(int64_t data) {
        return std::unique_ptr<Int> (new Int(data));
    }
    int64_t value() {
        return data_;
    }
    virtual ~Int() override = default;
};

class Str : public Object {
private:
    std::string data_;
    explicit Str(std::string data) : data_(data) {}
public:
    static std::unique_ptr<Str> create(std::string data) {
        return std::unique_ptr<Str> (new Str(data));
    }
    std::string& value() {
        return data_;
    }
    virtual ~Str() override = default;
};
