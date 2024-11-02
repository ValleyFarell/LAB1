#include"tests.h"

LogDuration::LogDuration(std::string id) : id_(std::move(id)) {}

LogDuration::~LogDuration() {
    const auto end_time = std::chrono::steady_clock::now();
    const auto dur = end_time - start_time_;
    std::cout << id_ << ": ";
    std::cout << "operation time"
              << ": " << std::chrono::duration_cast<std::chrono::nanoseconds>(dur).count()
              << " ns" << std::endl;
}

void copy_shared_test() {
    LogDuration t("Продолжительность copy_shared_test");
    SharedPtr<int> a(new int(5));
    SharedPtr<int> b(a);
    assert(a.get_pointer() == b.get_pointer());
}

void move_shared_test() {
    LogDuration t("Продолжительность move_shared_test");
    SharedPtr<int> a(new int(5));
    SharedPtr<int> b(std::move(a));
    assert(*b == 5);
    assert(a.get_pointer() == nullptr);
}

void counter_shared_test() {
    LogDuration t("Продолжительность counter_shared_test");
    SharedPtr<int> a(new int(5));
    {
        SharedPtr<int> b(a);
        assert(a.ref_count() == 2);
    }
    assert(a.ref_count() == 1);
}

void move_unique_test() {
    LogDuration t("Продолжительность move_unique_test");
    UniquePtr<int> a(new int(5));
    UniquePtr<int> b(std::move(a));
    assert(*b == 5);
    assert(a.get_pointer() == nullptr);
}

void std_shared_test() {
    {
        LogDuration t("Продолжительность SharedPtr");
        SharedPtr<int> a(new int(5));
        for (int i = 0; i < 10000000; ++i)
            SharedPtr<int> b(a);
    }
    {
        LogDuration t("Продолжительность std::shared_ptr");
        std::shared_ptr<int> a(new int(5));
        for (int i = 0; i < 10000000; ++i)
            std::shared_ptr<int> b(a);
    }
}

void std_unique_test() {
    {
        LogDuration t("Продолжительность UniquePtr");
        for (int i = 0; i < 10000000; ++i)
            UniquePtr<int> b(new int(5));
    }
    {
        LogDuration t("Продолжительность std::unique_ptr");
        for (int i = 0; i < 10000000; ++i)
            std::unique_ptr<int> b(new int(5));
    }
}