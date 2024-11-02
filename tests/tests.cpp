#include<cassert>
#include<memory>

#include"tests.h"

LogDuration::LogDuration(std::string id) : id_(std::move(id)) {}

LogDuration::~LogDuration() {
    const auto end_time = std::chrono::steady_clock::now();
    const auto dur = end_time - start_time_;
    std::cout << id_ << ": ";
    std::cout << "operation time"
              << ": " << std::chrono::duration_cast<std::chrono::milliseconds>(dur).count()
              << " ms" << std::endl;
}

void copy_shared_test() {
    LogDuration t("\ncopy_shared_test пройден");
        for (size_t i = 0; i != 1e6; ++i) {
        SharedPtr<int> a(new int(5));
        SharedPtr<int> b(a);
        assert(a.get_pointer() == b.get_pointer());
    }
}

void move_shared_test() {
    LogDuration t("move_shared_test пройден");
    for (size_t i = 0; i != 1e6; ++i) {
        SharedPtr<int> a(new int(5));
        SharedPtr<int> b(std::move(a));
        assert(*b == 5);
        assert(a.get_pointer() == nullptr);
    }
}

void counter_shared_test() {
    std::cout << "\ncounter_shared_test пройден\n";
    SharedPtr<int> a(new int(5));
    {
        SharedPtr<int> b(a);
        assert(a.ref_count() == 2);
    }
    assert(a.ref_count() == 1);
}

void move_unique_test() {
    LogDuration t("\nПродолжительность move_unique_test");
    for (size_t i = 0; i != 1e6; ++i) {
        UniquePtr<int> a(new int(5));
        UniquePtr<int> b(std::move(a));
        assert(*b == 5);
        assert(a.get_pointer() == nullptr);
    }
}

void std_shared_test() {
    {
        LogDuration t("\nПродолжительность копирования 10^6 SharedPtr");
        SharedPtr<int> a(new int(5));
        for (int i = 0; i < 10e6; ++i)
            SharedPtr<int> b(a);
    }
    {
        LogDuration t("Продолжительность копирования 10^6 std::shared_ptr");
        std::shared_ptr<int> a(new int(5));
        for (int i = 0; i < 10e6; ++i)
            std::shared_ptr<int> b(a);
    }
}

void std_unique_test() {
    {
        LogDuration t("\nПродолжительность создания 10^6 UniquePtr");
        for (int i = 0; i < 10e6; ++i)
            UniquePtr<int> b(new int(5));
    }
    {
        LogDuration t("Продолжительность создания 10^6 std::unique_ptr");
        for (int i = 0; i < 10000000; ++i)
            std::unique_ptr<int> b(new int(5));
    }
}
