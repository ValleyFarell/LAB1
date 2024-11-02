#include<iostream>
#include<chrono>
#include<cassert>
#include<memory>

#include"../src/memory_utils.h"

class LogDuration {
public:
    LogDuration(std::string id);

    ~LogDuration();

private:
    const std::string id_;
    const std::chrono::steady_clock::time_point start_time_ = std::chrono::steady_clock::now();
};

void copy_shared_test();
void move_shared_test();
void counter_shared_test();
void move_unique_test();
void std_shared_test();
void std_unique_test();
